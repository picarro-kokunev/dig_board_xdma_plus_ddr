`timescale 1ns / 1ps
// Generic dual-clock (asynchronous) FIFO using gray-coded pointers for safe
// clock-domain crossing. DEPTH must be a power of two and equal to 2**ADDR_W.
module async_fifo #(
    parameter DATA_W = 16,
    parameter DEPTH  = 1024,
    parameter ADDR_W = 10
)
(
    input  wire                 wr_clk,
    input  wire                 wr_rst_n,
    input  wire [DATA_W-1:0]    din,
    input  wire                 wr_en,
    output wire                 full,

    input  wire                 rd_clk,
    input  wire                 rd_rst_n,
    output wire [DATA_W-1:0]    dout,
    input  wire                 rd_en,
    output wire                 empty
);

    reg [DATA_W-1:0] mem [0:DEPTH-1];

    // Binary write/read pointers plus one extra MSB used as a wrap bit,
    // so pointer comparisons can distinguish full from empty.
    reg  [ADDR_W:0] wr_ptr_bin, rd_ptr_bin;
    reg  [ADDR_W:0] wr_ptr_gray, rd_ptr_gray;

    // Speculative "one write ahead" pointer, computed unconditionally so the
    // full flag does not depend on itself (full gates whether the write
    // actually commits, computed separately below).
    wire [ADDR_W:0] wr_ptr_bin_plus1  = wr_ptr_bin + 1'b1;
    wire [ADDR_W:0] wr_ptr_gray_plus1 = wr_ptr_bin_plus1 ^ (wr_ptr_bin_plus1 >> 1);
    wire [ADDR_W:0] wr_ptr_bin_next   = (wr_en && !full) ? wr_ptr_bin_plus1  : wr_ptr_bin;
    wire [ADDR_W:0] wr_ptr_gray_next  = (wr_en && !full) ? wr_ptr_gray_plus1 : wr_ptr_gray;

    wire [ADDR_W:0] rd_ptr_bin_next  = rd_ptr_bin + (rd_en && !empty);
    wire [ADDR_W:0] rd_ptr_gray_next = rd_ptr_bin_next ^ (rd_ptr_bin_next >> 1);

    // Gray-coded pointers synchronized into the opposite clock domain.
    reg [ADDR_W:0] rd_ptr_gray_wclk_r1, rd_ptr_gray_wclk_r2;
    reg [ADDR_W:0] wr_ptr_gray_rclk_r1, wr_ptr_gray_rclk_r2;

    // ---------------- Write domain ----------------
    always @(posedge wr_clk or negedge wr_rst_n) begin
        if (!wr_rst_n) begin
            wr_ptr_bin  <= {(ADDR_W+1){1'b0}};
            wr_ptr_gray <= {(ADDR_W+1){1'b0}};
        end else begin
            wr_ptr_bin  <= wr_ptr_bin_next;
            wr_ptr_gray <= wr_ptr_gray_next;
        end
    end

    always @(posedge wr_clk or negedge wr_rst_n) begin
        if (!wr_rst_n) begin
            rd_ptr_gray_wclk_r1 <= {(ADDR_W+1){1'b0}};
            rd_ptr_gray_wclk_r2 <= {(ADDR_W+1){1'b0}};
        end else begin
            rd_ptr_gray_wclk_r1 <= rd_ptr_gray;
            rd_ptr_gray_wclk_r2 <= rd_ptr_gray_wclk_r1;
        end
    end

    always @(posedge wr_clk) begin
        if (wr_en && !full)
            mem[wr_ptr_bin[ADDR_W-1:0]] <= din;
    end

    // Full when the speculative "one write ahead" pointer (gray) equals the
    // read pointer (gray) with the wrap bit inverted, i.e. a write would
    // catch up to read from behind. Uses the unconditional +1 pointer so
    // this does not depend on 'full' itself.
    assign full = (wr_ptr_gray_plus1 == {~rd_ptr_gray_wclk_r2[ADDR_W:ADDR_W-1],
                                           rd_ptr_gray_wclk_r2[ADDR_W-2:0]});

    // ---------------- Read domain ----------------
    always @(posedge rd_clk or negedge rd_rst_n) begin
        if (!rd_rst_n) begin
            rd_ptr_bin  <= {(ADDR_W+1){1'b0}};
            rd_ptr_gray <= {(ADDR_W+1){1'b0}};
        end else begin
            rd_ptr_bin  <= rd_ptr_bin_next;
            rd_ptr_gray <= rd_ptr_gray_next;
        end
    end

    always @(posedge rd_clk or negedge rd_rst_n) begin
        if (!rd_rst_n) begin
            wr_ptr_gray_rclk_r1 <= {(ADDR_W+1){1'b0}};
            wr_ptr_gray_rclk_r2 <= {(ADDR_W+1){1'b0}};
        end else begin
            wr_ptr_gray_rclk_r1 <= wr_ptr_gray;
            wr_ptr_gray_rclk_r2 <= wr_ptr_gray_rclk_r1;
        end
    end

    assign empty = (rd_ptr_gray == wr_ptr_gray_rclk_r2);
    assign dout  = mem[rd_ptr_bin[ADDR_W-1:0]];

endmodule
