`timescale 1ns / 1ps
// Bridges adc_ctrl_0/data (16-bit tagged sample, produced every sample_clk
// cycle @ clk_wiz_0/clk_out1 = 50 MHz) to xdma_0 S_AXIS_C2H_1, a 128-bit
// AXI4-Stream slave clocked by xdma_0/axi_aclk = 125 MHz.
//
// Sample format (from adc_ctrl.v):
//   data[15]    = adc_id   (0 = channel A, 1 = channel B)
//   data[14]    = adc_ofa  (overflow/underflow flag)
//   data[13:0]  = ADC sample
//
// Samples are packed 8-per-beat (128/16), raw and interleaved in arrival
// order (no A/B re-pairing) so the host recovers ordering/tagging from the
// in-band adc_id bit of each 16-bit word. TLAST marks a fixed-size DMA
// packet boundary every PKT_BEATS beats.
module adc_c2h_axis_bridge #(
    parameter SAMPLE_W         = 16,
    parameter AXIS_DATA_W      = 128,
    parameter SAMPLES_PER_BEAT = 8,
    parameter PKT_BEATS        = 512,
    parameter TKEEP_W          = 16
) (
    // --- ADC / sample domain: clk_wiz_0/clk_out1 + adc_ctrl_0/data ---
    (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 sample_clk CLK" *)
    (* X_INTERFACE_PARAMETER = "ASSOCIATED_RESET sample_rst_n, FREQ_HZ 50000000" *)
    input  sample_clk,

    (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 sample_rst_n RST" *)
    (* X_INTERFACE_PARAMETER = "POLARITY ACTIVE_LOW" *)
    input  sample_rst_n,

    input  [SAMPLE_W-1:0] sample_data,
    input  sample_valid,

    // --- XDMA AXI4-Stream master -> xdma_0/S_AXIS_C2H_1 ---
    (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 m_axis_aclk CLK" *)
    (* X_INTERFACE_PARAMETER = "ASSOCIATED_BUSIF m_axis, ASSOCIATED_RESET m_axis_aresetn, FREQ_HZ 125000000" *)
    input  m_axis_aclk,

    (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 m_axis_aresetn RST" *)
    (* X_INTERFACE_PARAMETER = "POLARITY ACTIVE_LOW" *)
    input  m_axis_aresetn,

    (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 m_axis TDATA" *)
    (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME m_axis, TDATA_NUM_BYTES 16, TDEST_WIDTH 0, TID_WIDTH 0, TUSER_WIDTH 0, HAS_TKEEP 1, HAS_TLAST 1" *)
    output [AXIS_DATA_W-1:0] m_axis_tdata,

    (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 m_axis TKEEP" *)
    output [TKEEP_W-1:0] m_axis_tkeep,

    (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 m_axis TLAST" *)
    output m_axis_tlast,

    (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 m_axis TVALID" *)
    output m_axis_tvalid,

    (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 m_axis TREADY" *)
    input  m_axis_tready
);

    localparam PACK_CNT_W = 3;
    localparam BEAT_CNT_W   = 9;

    // ------------------------------------------------------------------
    // 1) CDC: FIFO Generator (Independent Clocks, Native, FWFT, 2048x16)
    // ------------------------------------------------------------------
    wire fifo_full;
    wire fifo_wr_en;
    wire fifo_rd_en;
    wire [SAMPLE_W-1:0] fifo_dout;
    wire fifo_empty;
    wire fifo_rst;
    wire fifo_wr_rst_busy;
    wire fifo_rd_rst_busy;

  // Hold the FIFO in reset while either clock domain is in reset.
    assign fifo_rst = ~(sample_rst_n & m_axis_aresetn);

  // Exposed for simulation scoreboarding (one stored sample per accepted wr_en).
    assign fifo_wr_en = sample_valid && !fifo_full && !fifo_wr_rst_busy;

    adc_sample_fifo u_adc_sample_fifo (
        .rst         (fifo_rst),
        .wr_clk      (sample_clk),
        .rd_clk      (m_axis_aclk),
        .din         (sample_data),
        .wr_en       (fifo_wr_en),
        .rd_en       (fifo_rd_en),
        .dout        (fifo_dout),
        .full        (fifo_full),
        .empty       (fifo_empty),
        .wr_rst_busy (fifo_wr_rst_busy),
        .rd_rst_busy (fifo_rd_rst_busy)
    );

    // ------------------------------------------------------------------
    // 2) axi_aclk domain: pack SAMPLES_PER_BEAT samples into one AXIS beat
    // ------------------------------------------------------------------
    reg [PACK_CNT_W-1:0] pack_cnt;
    reg [AXIS_DATA_W-1:0] pack_reg;
    reg beat_valid;

    wire beat_consumed = m_axis_tvalid && m_axis_tready;

    assign fifo_rd_en = !fifo_empty && !fifo_rd_rst_busy &&
                        (!beat_valid || beat_consumed);

    always @(posedge m_axis_aclk) begin
        if (!m_axis_aresetn) begin
            pack_cnt   <= {PACK_CNT_W{1'b0}};
            pack_reg   <= {AXIS_DATA_W{1'b0}};
            beat_valid <= 1'b0;
        end else begin
            if (beat_consumed)
                beat_valid <= 1'b0;

            if (fifo_rd_en) begin
                pack_reg[SAMPLE_W*pack_cnt +: SAMPLE_W] <= fifo_dout;
                if (pack_cnt == SAMPLES_PER_BEAT-1) begin
                    pack_cnt   <= {PACK_CNT_W{1'b0}};
                    beat_valid <= 1'b1;
                end else begin
                    pack_cnt <= pack_cnt + 1'b1;
                end
            end
        end
    end

    // ------------------------------------------------------------------
    // 3) TLAST every PKT_BEATS accepted beats -> DMA packet boundary
    // ------------------------------------------------------------------
    reg [BEAT_CNT_W-1:0] pkt_beat_cnt;

    always @(posedge m_axis_aclk) begin
        if (!m_axis_aresetn)
            pkt_beat_cnt <= {BEAT_CNT_W{1'b0}};
        else if (beat_consumed)
            pkt_beat_cnt <= (pkt_beat_cnt == PKT_BEATS-1) ?
                            {BEAT_CNT_W{1'b0}} :
                            pkt_beat_cnt + 1'b1;
    end

    assign m_axis_tdata  = pack_reg;
    assign m_axis_tkeep  = {TKEEP_W{1'b1}};
    assign m_axis_tvalid = beat_valid;
    assign m_axis_tlast  = beat_valid && (pkt_beat_cnt == PKT_BEATS-1);

endmodule
