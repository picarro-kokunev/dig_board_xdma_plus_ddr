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
module adc_ctrl #(parameter DATA_W = 16, ADC_DATA_W = DATA_W-2, ADC_ID_A = 0, ADC_ID_B = 1)
(
    // system clock
    input clk,
    // module reset
    input reset_n,
    
    // input to ADC chip
    output adc_clk,
    // output data from ADC chip, DDR
    input [ADC_DATA_W-1:0] adc_data_a,
    // overflow/underflow
    input              adc_ofa_a,
    // output overflow/under flow from ADC chip, DDR relative to adc_clk 

    // ADC output for channel 0,1 SDR relative to clk
    // ADC channel 0 = ADC A
    // ADC channel 1 = ADC B 
    // data = { ADC_ID, adc_ofa, adc_data }
    output [DATA_W-1:0] data
);

    reg [DATA_W-1:0] data_reg;
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

    assign data = data_reg;
    // convert DDR stream to 2 SDR streams
    // ADC is updating data_a after (posedge adc_clk) + adc_ad_ltc22xx.CLK_TO_DATA_DELAY
    // ADC is updating data_b after (negedge adc_clk) + adc_ad_ltc22xx.CLK_TO_DATA_DELAY

    // if( adc_clk_reg == 1'b1 ) then data from adc_a otherwise adc_b          
    wire adc_id =  !adc_clk_reg;    
    
    // update data_a in the middle of adc_clk-is-high
    // update data_b in the middle of adc_clk-is-low   
    always @(negedge clk or negedge reset_n)
    begin
        if (!reset_n) 
            begin
                data_reg <= 0;
            end 
        else
            begin
                data_reg <= { adc_id, adc_ofa_a, adc_data_a};            
            end
    end
endmodule
