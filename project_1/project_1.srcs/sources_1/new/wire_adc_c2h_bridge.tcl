# wire_adc_c2h_bridge.tcl
#
# Adds adc_c2h_axis_bridge (+ adc_sample_fifo FIFO Generator IP) into design_1.bd
# between adc_ctrl_0/data and xdma_0/S_AXIS_C2H_1 via AXI4-Stream bus
# interfaces (not pin-by-pin), replacing any H2C_1->C2H_1 loopback stub.
#
# Usage (Vivado Tcl console, project open):
#   source /path/to/wire_adc_c2h_bridge.tcl

set XDMA_CH 1
set BRIDGE_CELL adc_c2h_bridge_0
set BRIDGE_MODULE adc_c2h_axis_bridge

set script_dir [file dirname [file normalize [info script]]]
set bridge_v [file normalize [file join $script_dir adc_c2h_axis_bridge.v]]
set fifo_v   [file normalize [file join $script_dir async_fifo.v]]

proc tie_off_unused_h2c_channel {xdma_cell ch} {
    if {[llength [get_bd_cells -quiet c_h2c${ch}_tready_0]] == 0} {
        set const1 [create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 c_h2c${ch}_tready_0]
        set_property -dict [list CONFIG.CONST_WIDTH {1} CONFIG.CONST_VAL {1}] $const1
        connect_bd_net [get_bd_pins c_h2c${ch}_tready_0/dout] [get_bd_pins ${xdma_cell}/m_axis_h2c_tready_${ch}]
    }
}

proc remove_axis_channel_tieoffs {ch} {
    foreach cell_name [list \
        c_c2h${ch}_tvalid_0 c_c2h${ch}_tlast_0 c_c2h${ch}_tdata_0 c_c2h${ch}_tkeep_0 \
        c_h2c${ch}_tready_0 \
    ] {
        set cell [get_bd_cells -quiet $cell_name]
        if {$cell ne ""} {
            delete_bd_objs $cell
        }
    }
}

proc disconnect_xdma_axis_channel_pins {xdma_cell ch} {
    foreach pin [list \
        ${xdma_cell}/m_axis_h2c_tdata_${ch}  ${xdma_cell}/m_axis_h2c_tkeep_${ch} \
        ${xdma_cell}/m_axis_h2c_tlast_${ch}  ${xdma_cell}/m_axis_h2c_tvalid_${ch} \
        ${xdma_cell}/m_axis_h2c_tready_${ch} \
        ${xdma_cell}/s_axis_c2h_tdata_${ch}  ${xdma_cell}/s_axis_c2h_tkeep_${ch} \
        ${xdma_cell}/s_axis_c2h_tlast_${ch}  ${xdma_cell}/s_axis_c2h_tvalid_${ch} \
        ${xdma_cell}/s_axis_c2h_tready_${ch} \
    ] {
        foreach net [get_bd_nets -quiet -of_objects [get_bd_pins $pin]] {
            delete_bd_objs $net
        }
    }

    foreach intf_pin [list \
        ${xdma_cell}/M_AXIS_H2C_${ch} \
        ${xdma_cell}/S_AXIS_C2H_${ch} \
    ] {
        set intf_net [get_bd_intf_nets -quiet -of_objects [get_bd_intf_pins $intf_pin]]
        if {$intf_net ne ""} {
            delete_bd_objs $intf_net
        }
    }
}

proc connect_h2c_c2h_loopback_intf {xdma_cell ch} {
    remove_axis_channel_tieoffs $ch
    disconnect_xdma_axis_channel_pins $xdma_cell $ch
    connect_bd_intf_net \
        [get_bd_intf_pins ${xdma_cell}/M_AXIS_H2C_${ch}] \
        [get_bd_intf_pins ${xdma_cell}/S_AXIS_C2H_${ch}]
}

proc disconnect_axis_channel_pins {bridge_cell xdma_cell ch} {
    foreach pin [list \
        ${bridge_cell}/m_axis_tdata  ${bridge_cell}/m_axis_tkeep \
        ${bridge_cell}/m_axis_tlast  ${bridge_cell}/m_axis_tvalid \
        ${bridge_cell}/m_axis_tready \
    ] {
        foreach net [get_bd_nets -quiet -of_objects [get_bd_pins $pin]] {
            delete_bd_objs $net
        }
    }

    set intf_net [get_bd_intf_nets -quiet -of_objects [get_bd_intf_pins ${bridge_cell}/m_axis]]
    if {$intf_net ne ""} {
        delete_bd_objs $intf_net
    }

    disconnect_xdma_axis_channel_pins $xdma_cell $ch
}

proc connect_bridge_to_c2h_intf {bridge_cell xdma_cell ch} {
    disconnect_axis_channel_pins $bridge_cell $xdma_cell $ch
    connect_bd_intf_net \
        [get_bd_intf_pins ${bridge_cell}/m_axis] \
        [get_bd_intf_pins ${xdma_cell}/S_AXIS_C2H_${ch}]
}

proc register_bridge_sources {bridge_v fifo_v} {
    set proj_srcs [current_fileset]

    foreach rtl_file [list $bridge_v $fifo_v] {
        if {[llength [get_files -quiet -of_objects $proj_srcs $rtl_file]] == 0} {
            add_files -norecurse -fileset $proj_srcs $rtl_file
        }
    }
    update_compile_order -fileset $proj_srcs
}

# ---------------------------------------------------------------------
# 0) Ensure RTL is in the project
# ---------------------------------------------------------------------
register_bridge_sources $bridge_v $fifo_v

set bd_file [get_files design_1.bd]
if {$bd_file eq ""} {
    error "design_1.bd not found in the current project"
}
open_bd_design $bd_file

# ---------------------------------------------------------------------
# 1) Instantiate the bridge (remove stale instance first if present)
# ---------------------------------------------------------------------
set old_bridge [get_bd_cells -quiet $BRIDGE_CELL]
if {$old_bridge ne ""} {
    delete_bd_objs $old_bridge
}

set bridge [create_bd_cell -type module -reference $BRIDGE_MODULE $BRIDGE_CELL]

# Tie sample_valid high (adc_ctrl_0 emits one sample every sample_clk cycle).
if {[llength [get_bd_cells -quiet c_sample_valid_1]] == 0} {
    set const_valid [create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 c_sample_valid_1]
    set_property -dict [list CONFIG.CONST_WIDTH {1} CONFIG.CONST_VAL {1}] $const_valid
}
connect_bd_net [get_bd_pins c_sample_valid_1/dout] [get_bd_pins ${BRIDGE_CELL}/sample_valid]

# ---------------------------------------------------------------------
# 2) Clock / reset connections
# ---------------------------------------------------------------------
connect_bd_net [get_bd_pins clk_wiz_0/clk_out1]   [get_bd_pins ${BRIDGE_CELL}/sample_clk]
connect_bd_net [get_bd_ports pcie_reset_n]        [get_bd_pins ${BRIDGE_CELL}/sample_rst_n]
connect_bd_net [get_bd_pins xdma_0/axi_aclk]      [get_bd_pins ${BRIDGE_CELL}/m_axis_aclk]
connect_bd_net [get_bd_pins ilvector_logic_0/Res]  [get_bd_pins ${BRIDGE_CELL}/m_axis_aresetn]

# ---------------------------------------------------------------------
# 3) ADC sample data in
# ---------------------------------------------------------------------
connect_bd_net [get_bd_pins adc_ctrl_0/data] [get_bd_pins ${BRIDGE_CELL}/sample_data]

# ---------------------------------------------------------------------
# 4) Remove H2C->C2H loopback on channel $XDMA_CH; connect AXI stream buses
# ---------------------------------------------------------------------
set loop_intf [get_bd_intf_nets -quiet -of_objects [get_bd_intf_pins xdma_0/M_AXIS_H2C_${XDMA_CH}]]
if {$loop_intf ne ""} {
    delete_bd_objs $loop_intf
}

connect_bridge_to_c2h_intf $BRIDGE_CELL xdma_0 $XDMA_CH

# H2C on the active ADC channel is unused once C2H is fed by the bridge.
tie_off_unused_h2c_channel xdma_0 $XDMA_CH

# Channel 0: H2C_0 -> C2H_0 loopback via AXI-Stream bus interfaces (bring-up stub).
if {$XDMA_CH != 0} {
    connect_h2c_c2h_loopback_intf xdma_0 0
}

validate_bd_design
save_bd_design

set axis_net [get_bd_intf_nets -quiet -of_objects [get_bd_intf_pins ${BRIDGE_CELL}/m_axis]]
if {$axis_net eq ""} {
    error "AXIS interface net not created between ${BRIDGE_CELL}/m_axis and xdma_0/S_AXIS_C2H_${XDMA_CH}"
}

set loop0_net [get_bd_intf_nets -quiet -of_objects [get_bd_intf_pins xdma_0/M_AXIS_H2C_0]]
if {$XDMA_CH != 0 && $loop0_net eq ""} {
    error "AXIS loopback interface net not created between xdma_0/M_AXIS_H2C_0 and xdma_0/S_AXIS_C2H_0"
}

puts "SUCCESS: $BRIDGE_MODULE wired into design_1.bd on XDMA stream channel ${XDMA_CH}."
puts "ADC AXIS interface net: $axis_net"
if {$XDMA_CH != 0} {
    puts "H2C_0->C2H_0 loopback AXIS interface net: $loop0_net"
}
puts "Next steps:"
puts "  generate_target all \[get_files design_1.bd\]"
puts "  make_wrapper -files \[get_files design_1.bd\] -top -force"
puts "  launch_runs synth_1 -jobs 8"
