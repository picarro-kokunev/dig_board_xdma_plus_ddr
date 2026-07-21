`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Testbench for adc_ctrl and adc_ad_ltc22xx
//
// This testbench instantiates the ADC model and the control block, connects
// the DDR ADC outputs to the controller input, and generates a system clock
// and reset.
//////////////////////////////////////////////////////////////////////////////////

module adc_ctrl_tb;
    parameter DATA_W = 14;

    // system signals
    logic clk;
    logic reset_n;

    // ADC chip interface
    logic adc_clk;
    logic [DATA_W-1:0] adc_data_a;
    logic [DATA_W-1:0] adc_data_b;

    // Controller output
    logic [1:0][DATA_W-1:0] data;

    // Instantiate the ADC model
    adc_ad_ltc22xx #(.DATA_W(DATA_W)) adc_ad_ltc22xx_inst (
        .clk(adc_clk),
        .adc_data_a(adc_data_a),
        .adc_data_b(adc_data_b)
    );

    // Instantiate the controller under test
    adc_ctrl #(.DATA_W(DATA_W)) adc_ctrl_inst (
        .clk(clk),
        .reset_n(reset_n),
        .adc_clk(adc_clk),
        .adc_data_a(adc_data_a),
        .adc_data_b(adc_data_b),        
        .data_a(data[0]),
        .data_b(data[1])
    );

    // System clock generation
    initial begin
        clk = 0;
        forever #10 clk = ~clk;  // 50 MHz clock
    end

    // set input data and verify the output
    logic [1:0][DATA_W-1:0] data_last = '0;
    initial begin
        integer i;
        // fill the queues
        for( i = 0; i < 1000; i = i + 1)
        begin
            adc_ad_ltc22xx_inst.adc_a.push_back( i );            
            adc_ad_ltc22xx_inst.adc_b.push_back( i + 'h100);            
        end
    end

    // set input data and verify the output    
    integer j = 0;
    always@(posedge clk)
    begin
        if(reset_n)
        begin                
            // check that adc_data is incrementing
            for( j = 0; j < 2; j = j + 1 )  
            begin
                if( data_last[j] != 0 )
                begin
                    if( data_last[j] + 1 != data[j] )
                        $error("%0t : wrong data : expected %h got %h", $time, data_last[j] + 1, data[j] );
                end               
            end
            // update  
            data_last = data;  
        end 
    end
    // Reset sequence
    initial begin
	@(posedge clk);
        reset_n = 0;
        #20;
	@(posedge clk);
        reset_n = 1;
    end

    // Run simulation
    initial 
    begin
        //
        #1000;
        $display("Test complete.");
        $stop;
    end

endmodule
