`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 07/20/2026 12:32:50 PM
// Design Name: 
// Module Name: adc_ctrl
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

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
    // data[0] == ADC channel A
    // data[1] == ADC channel B
    input [1:0][DATA_W-1:0] adc_data,
    // output overflow/under flow from ADC chip, DDR relative to adc_clk 
    input [1:0] adc_ofa,
    // ADC output for channel 0,1 SDR relative to clk
    // data[0] == ADC channel A
    // data[1] == ADC channel B
    output reg [1:0][DATA_W-1:0] data
);
    // generate adc_clk from clk so period(adc_clk) == 2 *period(clk)
    logic adc_clk_reg ='0;
    always_ff @(posedge clk) 
    begin
        adc_clk_reg <= ~adc_clk_reg;
    end
    assign adc_clk = adc_clk_reg;    

    // convert DDR stream to 2 SDR streams
    always_ff @(posedge clk or negedge reset_n)
    begin
        if (!reset_n) 
            begin
                data <= '0;   
            end 
        else
            begin
                if(adc_clk_reg)  // rising edge
                    begin
                        data[0] <= adc_data[0];
                        data[1] <= adc_data[1];
                    end
                else
                    begin
                        data[0] <= adc_data[1];
                        data[1] <= adc_data[0];
                    end
            end
    end
endmodule
