`timescale 1ns / 1ps
// Control block for the ADC 
//  - provides clock to AD ADC LTC22xx, 
//  - splits DDR data into 2 separate SDR data streams
//  
// Assume adc_ad_ltc22xx adc has 2 channels, each channel has 14 bits data width, and
// the data is output in DDR format relative to adc_clk.
// Generate adc_clk from clk, and convert the DDR data to SDR data for each channel.
// Convert DDR data from ADC chip to SDR data for each channel
//
module adc_ctrl #(parameter DATA_W = 14)
(
    // system clock
    input clk,
    // module reset
    input reset_n,
    
    // input to ADC chip
    output adc_clk,
    // output data from ADC chip, DDR
    input [DATA_W-1:0] adc_data_a,
    // overflow/underflow
    input              adc_ofa_a,
    // output overflow/under flow from ADC chip, DDR relative to adc_clk 

    // ADC output for channel 0,1 SDR relative to clk
    output reg [DATA_W-1:0] data_a,
    output reg ofa_a,
    output reg [DATA_W-1:0] data_b,
    output reg ofa_b,

    // debug
    output tie_all     
);
    // generate adc_clk from clk so period(adc_clk) == 2 *period(clk)
    reg adc_clk_reg;
    initial
    begin 
        adc_clk_reg = 0;
    end
    always @(posedge clk) 
    begin
        adc_clk_reg <= ~adc_clk_reg;
    end
    assign adc_clk = adc_clk_reg;    

    // to force no pruning
    assign tie_all = data_a | data_b | ofa_a | ofa_b;

    // convert DDR stream to 2 SDR streams
    // ADC is updating data_a after (posedge adc_clk) + adc_ad_ltc22xx.CLK_TO_DATA_DELAY
    // ADC is updating data_b after (negedge adc_clk) + adc_ad_ltc22xx.CLK_TO_DATA_DELAY

    // update data_a in the middle of adc_clk-is-high
    // update data_b in the middle of adc_clk-is-low    
    always @(negedge clk or negedge reset_n)
    begin
        if (!reset_n) 
            begin
                { ofa_a, data_a } <= 0;
                { ofa_b, data_b } <= 0;
            end 
        else
            begin
                // adc_clk is high
                if( adc_clk_reg == 1'b1 )
                begin
                    data_a <= adc_data_a;
                    ofa_a <= adc_ofa_a;
                end
                else
                begin
                    data_b <= adc_data_a;
                    ofa_b <= adc_ofa_a;                   
                end
            end
    end
endmodule
