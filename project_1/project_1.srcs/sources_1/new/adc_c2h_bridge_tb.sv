`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////
// Testbench: end-to-end data flow from adc_ctrl (ADC digitizer front-end)
// through adc_c2h_axis_bridge, checked at an AXI4-Stream slave BFM that
// mimics xdma_0's S_AXIS_C2H_1 port.
//
// Verifies:
//   - sample values/order are preserved through the CDC (50 MHz -> 125 MHz,
//     unrelated/unaligned clocks) and 16b -> 128b packing logic
//   - TKEEP is fully asserted on every beat
//   - TLAST asserts exactly on the last beat of every PKT_BEATS-beat packet
//   - the bridge behaves correctly under randomized AXI-side backpressure
//   - reset behavior: output stays quiescent while sample_rst_n is low
//////////////////////////////////////////////////////////////////////////////
module adc_c2h_bridge_tb;

    localparam DATA_W           = 16;
    localparam ADC_DATA_W       = DATA_W-2;
    localparam AXIS_DATA_W      = 128;
    localparam SAMPLES_PER_BEAT = AXIS_DATA_W/DATA_W;  // 8
    localparam PKT_BEATS        = 8;                    // small on purpose, for fast sim

    // Number of adc_ctrl output samples we require to reach the BFM and be
    // checked before declaring success (must be a multiple of SAMPLES_PER_BEAT
    // so the packer fully drains without a stuck partial beat).
    localparam NUM_SAMPLES_CHECK = 512;
    // Per-channel ADC model queue depth. Must cover the whole simulation
    // (adc_clk free-runs regardless of reset_n) with margin for reset-time
    // consumption and post-check drain.
    localparam QUEUE_LEN_PER_CH  = 400;

    // ---------------- Sample-domain clock/reset ----------------
    logic sample_clk = 0;
    logic sample_rst_n = 0;
    always #10 sample_clk = ~sample_clk;  // 50 MHz

    // ---------------- AXI-domain clock/reset (independent, 125 MHz) ------
    logic m_axis_aclk = 0;
    logic m_axis_aresetn = 0;
    always #4 m_axis_aclk = ~m_axis_aclk;  // 125 MHz, phase-unaligned to sample_clk

    // ---------------- ADC model + adc_ctrl DUT -----------------
    logic adc_clk_int;
    logic [ADC_DATA_W-1:0] adc_data_a;
    logic adc_ofa_a;
    logic [DATA_W-1:0] adc_data;

    adc_ad_ltc22xx #(.DATA_W(ADC_DATA_W)) u_adc_model (
        .clk       (adc_clk_int),
        .adc_data_a(adc_data_a),
        .adc_ofa_a (adc_ofa_a)
    );

    adc_ctrl #(.DATA_W(DATA_W)) u_adc_ctrl (
        .clk       (sample_clk),
        .reset_n   (sample_rst_n),
        .adc_clk   (adc_clk_int),
        .adc_data_a(adc_data_a),
        .adc_ofa_a (adc_ofa_a),
        .data      (adc_data)
    );

    // ---------------- Bridge DUT --------------------------------
    logic [AXIS_DATA_W-1:0]   m_axis_tdata;
    logic [AXIS_DATA_W/8-1:0] m_axis_tkeep;
    logic                     m_axis_tvalid;
    logic                     m_axis_tready;
    logic                     m_axis_tlast;

    adc_c2h_axis_bridge #(
        .SAMPLE_W   (DATA_W),
        .AXIS_DATA_W(AXIS_DATA_W),
        .PKT_BEATS  (PKT_BEATS)
    ) u_bridge (
        .sample_clk    (sample_clk),
        .sample_rst_n  (sample_rst_n),
        .sample_data   (adc_data),
        .sample_valid  (1'b1),

        .m_axis_aclk   (m_axis_aclk),
        .m_axis_aresetn(m_axis_aresetn),
        .m_axis_tdata  (m_axis_tdata),
        .m_axis_tkeep  (m_axis_tkeep),
        .m_axis_tvalid (m_axis_tvalid),
        .m_axis_tready (m_axis_tready),
        .m_axis_tlast  (m_axis_tlast)
    );

    int error_count = 0;

    // ---------------- Reset-quiescence check ---------------------------
    always @(posedge m_axis_aclk) begin
        if (!m_axis_aresetn && m_axis_tvalid) begin
            error_count++;
            $error("%0t : m_axis_tvalid asserted while m_axis_aresetn is low", $time);
        end
    end

    // ---------------- Golden reference queue --------------------
    // Capture exactly the samples the FIFO actually stores as distinct
    // entries, in order. While either domain reset is active the FIFO is
    // held in reset (see adc_c2h_axis_bridge fifo_rst). Gate on fifo_wr_en
    // to match one stored entry per accepted write.
    logic [DATA_W-1:0] golden_q[$];

    always @(posedge sample_clk) begin
        if (u_bridge.fifo_wr_en)
            golden_q.push_back(adc_data);
    end

    // ---------------- AXI4-Stream slave BFM (mimics xdma S_AXIS_C2H_1) ---
    int samples_checked = 0;
    int beat_count = 0;
    int expected_beat_in_pkt = 0;

    // Randomized backpressure: ready ~70% of cycles once out of reset.
    always @(posedge m_axis_aclk) begin
        if (!m_axis_aresetn)
            m_axis_tready <= 1'b0;
        else
            m_axis_tready <= ($urandom_range(99,0) < 70);
    end

    always @(posedge m_axis_aclk) begin
        if (m_axis_aresetn && m_axis_tvalid && m_axis_tready) begin
            beat_count++;

            if (m_axis_tkeep !== {(AXIS_DATA_W/8){1'b1}}) begin
                error_count++;
                $error("%0t : TKEEP not fully asserted: %h", $time, m_axis_tkeep);
            end

            if (m_axis_tlast !== (expected_beat_in_pkt == PKT_BEATS-1)) begin
                error_count++;
                $error("%0t : TLAST mismatch on beat %0d of packet (expected %0b got %0b)",
                        $time, expected_beat_in_pkt, (expected_beat_in_pkt == PKT_BEATS-1), m_axis_tlast);
            end
            expected_beat_in_pkt = (expected_beat_in_pkt == PKT_BEATS-1) ? 0 : expected_beat_in_pkt+1;

            for (int i = 0; i < SAMPLES_PER_BEAT; i++) begin
                logic [DATA_W-1:0] got;
                logic [DATA_W-1:0] exp;
                got = m_axis_tdata[i*DATA_W +: DATA_W];
                if (golden_q.size() == 0) begin
                    error_count++;
                    $error("%0t : golden queue underflow while checking word %0d of beat %0d",
                            $time, i, beat_count);
                end else begin
                    exp = golden_q.pop_front();
                    if (got !== exp) begin
                        error_count++;
                        $error("%0t : sample mismatch (beat %0d, word %0d): expected %h got %h",
                                $time, beat_count, i, exp, got);
                    end
                end
                samples_checked++;
            end
        end
    end

    // ---------------- Stimulus: fill ADC queues, release resets --------
    initial begin
        for (int i = 0; i < QUEUE_LEN_PER_CH; i++) begin
            int val_a, val_b, ofa_a_v, ofa_b_v;
            val_a   = $urandom_range(2**ADC_DATA_W-1, 0);
            val_b   = $urandom_range(2**ADC_DATA_W-1, 0);
            ofa_a_v = $urandom_range(1,0);
            ofa_b_v = $urandom_range(1,0);
            u_adc_model.adc_a.push_back(val_a);
            u_adc_model.adc_b.push_back(val_b);
            u_adc_model.ofa_a.push_back(ofa_a_v);
            u_adc_model.ofa_b.push_back(ofa_b_v);
        end

        // Staggered, independent reset releases to exercise the CDC paths
        // (sample domain and AXI domain come out of reset at different times).
        #25  sample_rst_n   = 1;
        #17  m_axis_aresetn = 1;
    end

    // ---------------- Reset behavior check ------------------------------
    // While sample_rst_n is low, adc_ctrl's data output (and hence the
    // stream entering the bridge) must be zero.
    always @(posedge sample_clk) begin
        if (!sample_rst_n && adc_data !== '0) begin
            error_count++;
            $error("%0t : adc_data non-zero (%h) while sample_rst_n is low", $time, adc_data);
        end
    end

    // ---------------- Scoreboard / completion watchdog -------------------
    int timeout_cycles;
    initial begin
        timeout_cycles = 0;
        wait (sample_rst_n === 1'b1);
        while (samples_checked < NUM_SAMPLES_CHECK && timeout_cycles < 200000) begin
            @(posedge m_axis_aclk);
            timeout_cycles++;
        end

        if (samples_checked < NUM_SAMPLES_CHECK) begin
            error_count++;
            $error("Timeout: only checked %0d/%0d samples", samples_checked, NUM_SAMPLES_CHECK);
        end

        if (error_count == 0) begin
            $display("Test complete: PASS (%0d samples, %0d beats checked)", samples_checked, beat_count);
        end else begin
            $display("Test complete: FAIL (%0d errors)", error_count);
            $fatal(1);
        end
        $finish;
    end

endmodule
