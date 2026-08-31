# Generate FIFO Generator (Independent Clocks, Native) for adc_c2h_axis_bridge.
# Run from project_1/: vivado -mode batch -source project_1.srcs/sources_1/ip/create_adc_sample_fifo.tcl

set proj_dir [file normalize [file join [file dirname [info script]] ../../..]]
open_project [file join $proj_dir project_1.xpr]

set script_dir [file dirname [file normalize [info script]]]
set ip_dir     $script_dir/adc_sample_fifo

file mkdir $ip_dir

create_ip -name fifo_generator -vendor xilinx.com -library ip -version 13.2 \
    -module_name adc_sample_fifo -dir $ip_dir

set_property -dict [list \
    CONFIG.Fifo_Implementation              {Independent_Clocks_Block_RAM} \
    CONFIG.Performance_Options              {First_Word_Fall_Through} \
    CONFIG.Input_Data_Width                 {16} \
    CONFIG.Input_Depth                      {2048} \
    CONFIG.Output_Data_Width                {16} \
    CONFIG.Output_Depth                     {2048} \
    CONFIG.Use_Embedded_Registers           {true} \
    CONFIG.Reset_Type                       {Asynchronous_Reset} \
    CONFIG.Reset_Pin                        {true} \
    CONFIG.Full_Flags_Reset_Value           {1} \
    CONFIG.Use_Dout_Reset                   {true} \
    CONFIG.Valid_Flag                       {false} \
    CONFIG.Almost_Full_Flag                 {false} \
    CONFIG.Almost_Empty_Flag                {false} \
    CONFIG.Underflow_Flag                   {false} \
    CONFIG.Overflow_Flag                    {false} \
    CONFIG.Write_Acknowledge_Flag           {false} \
    CONFIG.Data_Count                       {false} \
    CONFIG.Write_Data_Count                 {false} \
    CONFIG.Read_Data_Count                  {false} \
    CONFIG.Disable_Timing_Violations        {false} \
    CONFIG.synchronization_stages         {2} \
] [get_ips adc_sample_fifo]

generate_target all [get_ips adc_sample_fifo]
generate_target all [get_ips adc_sample_fifo]
export_ip_user_files -of_objects [get_ips adc_sample_fifo] -no_script -sync -force -quiet

# Add generated IP to the Vivado project fileset.
add_files -quiet [file join $ip_dir adc_sample_fifo.xci]
set_property generate_synth_checkpoint false [get_files adc_sample_fifo.xci]

puts "INFO: adc_sample_fifo IP generated in $ip_dir"
