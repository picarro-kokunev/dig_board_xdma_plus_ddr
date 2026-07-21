//
// Simulation of ad_ltc22xx in multiplexed mode
// 
module adc_ad_ltc22xx #(parameter DATA_W = 14)
(
    // 
    input clk,
    // data[0] == ADC channel A
    // data[1] == ADC channel B
    output reg [DATA_W-1:0] adc_data_a,
    output reg [DATA_W-1:0] adc_data_b
);
// on rising edge adc_data_A = { sample_a } adc_data_B = { sample_b }
// on falling edge adc_data_A = { sample_b } adc_data_B = { sample_a }

// fill adc_a and adc_b externally
logic [DATA_W-1:0] adc_a[$], adc_b[$];


always@(posedge clk or negedge clk) 
begin
    if(adc_a.size() > 0 )
        // posedge
        if( clk )
            adc_data_a = adc_a.pop_front();
        else
            adc_data_a = adc_b.pop_front();
    else
        begin
            adc_data_a = 'x;
            $display("adc_ad_ltc22xx error : adc_a is empty");
        end
    if(adc_b.size() > 0 )
        // posedge
        if( clk )
            adc_data_b = adc_b.pop_front();
        else
            adc_data_b = adc_a.pop_front();
    else
        begin
            adc_data_b = 'x;
            $display("adc_ad_ltc22xx error : adc_b is empty");
        end
end    

endmodule