`timescale 1ns / 1ps
//
// Simulation of ad_ltc22xx in multiplexed mode
// 
module adc_ad_ltc22xx #(parameter DATA_W = 14, CLK_TO_DATA_DELAY = 2.7 )
(
    // 
    input clk,
    // data[0] == ADC channel A
    // data[1] == ADC channel B
    output reg [DATA_W-1:0] adc_data_a,
    // overflow/underflow
    output reg adc_ofa_a
);
// on rising edge adc_data_A = { sample_a } adc_data_B = { sample_b }
// on falling edge adc_data_A = { sample_b } adc_data_B = { sample_a }

// fill adc_a and adc_b externally
logic [DATA_W-1:0] adc_a[$], adc_b[$];
logic ofa_a[$], ofa_b[$];

// There is a clk-to-data delay
// ADC is updating data_a after (posedge adc_clk) + adc_ad_ltc22xx.CLK_TO_DATA_DELAY
// ADC is updating data_b after (negedge adc_clk) + adc_ad_ltc22xx.CLK_TO_DATA_DELAY
always@(posedge clk) 
begin
    if(  adc_a.size() > 0 )
    begin
        adc_data_a <= #(CLK_TO_DATA_DELAY) adc_a.pop_front();        
    end
    else
    begin
        adc_data_a <= #(CLK_TO_DATA_DELAY) 'x;
        $error("adc_ad_ltc22xx error : adc_a is empty");
    end           
    if(  ofa_a.size() > 0 )
    begin
        adc_ofa_a <= #(CLK_TO_DATA_DELAY) ofa_a.pop_front();        
    end
    else
    begin
        adc_ofa_a <= #(CLK_TO_DATA_DELAY) 'x;
        $error("adc_ad_ltc22xx error : ofa_a is empty");
    end           
end    
always@(negedge clk) 
begin
    if( adc_b.size() > 0 )
        adc_data_a <= #(CLK_TO_DATA_DELAY) adc_b.pop_front();
    else
    begin
        adc_data_a <= #(CLK_TO_DATA_DELAY) 'x;
        $error("adc_ad_ltc22xx error : adc_b is empty");
    end
    if(  ofa_b.size() > 0 )
    begin
        adc_ofa_a <= #(CLK_TO_DATA_DELAY) ofa_b.pop_front();        
    end
    else
    begin
        adc_ofa_a <= #(CLK_TO_DATA_DELAY) 'x;
        $error("adc_ad_ltc22xx error : ofa_b is empty");
    end           
end

endmodule