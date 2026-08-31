# Run adc_c2h_bridge_tb in Vivado XSim (FIFO Generator behavioral model).
# Usage (from project_1/):
#   vivado -mode batch -source project_1.srcs/sources_1/new/run_adc_c2h_bridge_tb.tcl

set proj_dir [file normalize [file join [file dirname [info script]] ../../..]]
open_project [file join $proj_dir project_1.xpr]

set src_dir [file normalize [file join [file dirname [info script]]]]
set ip_dir  [file normalize [file join $src_dir ../ip/adc_sample_fifo/adc_sample_fifo]]

# RTL under test
set rtl_files [list \
    [file join $src_dir adc_ctrl.v] \
    [file join $src_dir adc_ad_ltc22xx.sv] \
    [file join $src_dir adc_c2h_axis_bridge.v] \
    [file join $src_dir adc_c2h_bridge_tb.sv] \
]

# FIFO Generator simulation netlist (behavioral) for XSim
set fifo_files [list \
    [file join $src_dir adc_sample_fifo_sim.v] \
    [file join $ip_dir simulation fifo_generator_vlog_beh.v] \
]

foreach f [concat $rtl_files $fifo_files] {
    if {![file exists $f]} {
        error "Missing simulation source: $f"
    }
}

set_property top adc_c2h_bridge_tb [get_filesets sim_1]
set_property top_lib xil_defaultlib [get_filesets sim_1]

add_files -fileset sim_1 -norecurse $rtl_files
add_files -fileset sim_1 -norecurse $fifo_files

set_property -name {xsim.compile.xvlog.more_options} \
    -value {-L uvm} -objects [get_filesets sim_1]

update_compile_order -fileset sim_1

launch_simulation -simset sim_1 -mode behavioral
run 5ms

set err_lines [get_value -radix unsigned {/adc_c2h_bridge_tb/error_count}]
set samples   [get_value -radix unsigned {/adc_c2h_bridge_tb/samples_checked}]
puts "INFO: error_count=$err_lines samples_checked=$samples"

if {$err_lines != 0} {
    close_sim -force
    close_project
    error "adc_c2h_bridge_tb FAILED with $err_lines errors"
}

puts "INFO: adc_c2h_bridge_tb PASSED"
close_sim -force
close_project
