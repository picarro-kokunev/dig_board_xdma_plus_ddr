`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Testbench for adc_ctrl and adc_ad_ltc22xx
//
// This testbench instantiates the ADC model and the control block, connects
// the DDR ADC outputs to the controller input, and generates a system clock
// and reset.
//////////////////////////////////////////////////////////////////////////////////

module adc_ctrl_tb;
    parameter DATA_W = 16;
    parameter ADC_DATA_W = DATA_W-2;

    // system signals
    logic clk;
    logic reset_n;

    // ADC chip interface
    logic adc_clk;
    logic adc_ofa_a;
    logic [ADC_DATA_W-1:0] adc_data_a;

    // Controller output: 
    // bit DATA_W - channel number
    // bit DATA_W-2 is OFA, bits DATA_W-1:0 are sample data
    logic [DATA_W-1:0] data;

    // Instantiate the ADC model
    adc_ad_ltc22xx #(.DATA_W(ADC_DATA_W)) adc_ad_ltc22xx_inst (
        .clk(adc_clk),
        .adc_data_a(adc_data_a),
        .adc_ofa_a(adc_ofa_a)
    );

    // Instantiate the controller under test
    adc_ctrl #(.DATA_W(DATA_W)) adc_ctrl_inst (
        .clk(clk),
        .reset_n(reset_n),
        .adc_clk(adc_clk),
        .adc_data_a(adc_data_a),
        .adc_ofa_a(adc_ofa_a),
        .data(data)
    );

    // System clock generation
    initial begin
        clk = 0;
        forever #10 clk = ~clk;  // 50 MHz clock
    end

    // set input data and verify the output
    int error_count = 0;
    logic [ADC_DATA_W-1:0] adc_expected[1:0][$];
    logic ofa_expected[1:0][$];

    // inject ADC data
    initial 
    begin
        integer i;

        // simulate with sequential data
        for (i = 0; i < 100; i = i + 1) 
        begin
            automatic int val = i%2;
            adc_ad_ltc22xx_inst.ofa_a.push_back(val);
            adc_ad_ltc22xx_inst.ofa_b.push_back(val);
            ofa_expected[0].push_back(val);
            ofa_expected[1].push_back(val);
            //
            adc_ad_ltc22xx_inst.adc_a.push_back(i);
            adc_expected[0].push_back(i);
            adc_ad_ltc22xx_inst.adc_b.push_back(i + 'h100);
            adc_expected[1].push_back(i + 'h100);
        end
        // simulate with random data
        for (i = 0; i < 100; i = i + 1) 
        begin
            automatic int val = $urandom_range(1, 0);
            adc_ad_ltc22xx_inst.ofa_a.push_back(val);
            ofa_expected[0].push_back(val);
            val = $urandom_range(1, 0);
            adc_ad_ltc22xx_inst.ofa_b.push_back(val);
            ofa_expected[1].push_back(val);
            //
            val = $urandom_range(2**ADC_DATA_W-1, 0);
            adc_ad_ltc22xx_inst.adc_a.push_back(val);
            adc_expected[0].push_back(val);
            //
            val = $urandom_range(2**ADC_DATA_W-1, 0);
            adc_ad_ltc22xx_inst.adc_b.push_back(val);
            adc_expected[1].push_back(val);
        end
        reset_n = 1;
    end

    // check data outside of reset_n
    always @(posedge clk) 
    begin
        if (reset_n)
        begin
            automatic int j = adc_clk ? 0 : 1;
            automatic logic [ADC_DATA_W-1:0] expected = adc_expected[j].pop_front();
            automatic logic ofa_exp = ofa_expected[j].pop_front();
            automatic logic channel_exp = j;
            automatic logic [DATA_W-1:0] expected_packed = {channel_exp, ofa_exp, expected};

            if (data != expected_packed) 
            begin
                error_count++;
                $error("%0t : wrong data[%d] : expected %h got %h (ofa=%b sample=%h)",
                        $time, j, expected_packed, data, ofa_exp, expected);
            end
        end
    end

    task test_reset();
        // test reset_n drives 0
        @(posedge clk);
        // reset 
        reset_n = 0;
        // wait to data to propagate
        #10;
        // check for the output
        for( int k = 0; k < 20; k ++ )
        begin
            @(posedge clk);
            if(data != '0 )
            begin
                error_count++;
                $error("%0t : Non zero data %h during the reset",
                        $time, data);
            end
        end
    endtask

    // Run simulation
    initial begin
        #1500;
        test_reset();
        if (error_count == 0)
            $display("Test complete: PASS");
        else begin
            $display("Test complete: FAIL (%0d errors)", error_count);
            $fatal(1);
        end
        $stop;
    end

endmodule
