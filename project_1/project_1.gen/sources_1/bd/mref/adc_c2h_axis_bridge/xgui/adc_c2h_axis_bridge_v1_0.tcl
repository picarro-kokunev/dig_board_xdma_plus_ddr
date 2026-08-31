# Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
  ipgui::add_param $IPINST -name "Component_Name"
  #Adding Page
  set Page_0 [ipgui::add_page $IPINST -name "Page 0"]
  ipgui::add_param $IPINST -name "AXIS_DATA_W" -parent ${Page_0}
  ipgui::add_param $IPINST -name "PKT_BEATS" -parent ${Page_0}
  ipgui::add_param $IPINST -name "SAMPLES_PER_BEAT" -parent ${Page_0}
  ipgui::add_param $IPINST -name "SAMPLE_W" -parent ${Page_0}
  ipgui::add_param $IPINST -name "TKEEP_W" -parent ${Page_0}


}

proc update_PARAM_VALUE.AXIS_DATA_W { PARAM_VALUE.AXIS_DATA_W } {
	# Procedure called to update AXIS_DATA_W when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.AXIS_DATA_W { PARAM_VALUE.AXIS_DATA_W } {
	# Procedure called to validate AXIS_DATA_W
	return true
}

proc update_PARAM_VALUE.PKT_BEATS { PARAM_VALUE.PKT_BEATS } {
	# Procedure called to update PKT_BEATS when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.PKT_BEATS { PARAM_VALUE.PKT_BEATS } {
	# Procedure called to validate PKT_BEATS
	return true
}

proc update_PARAM_VALUE.SAMPLES_PER_BEAT { PARAM_VALUE.SAMPLES_PER_BEAT } {
	# Procedure called to update SAMPLES_PER_BEAT when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.SAMPLES_PER_BEAT { PARAM_VALUE.SAMPLES_PER_BEAT } {
	# Procedure called to validate SAMPLES_PER_BEAT
	return true
}

proc update_PARAM_VALUE.SAMPLE_W { PARAM_VALUE.SAMPLE_W } {
	# Procedure called to update SAMPLE_W when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.SAMPLE_W { PARAM_VALUE.SAMPLE_W } {
	# Procedure called to validate SAMPLE_W
	return true
}

proc update_PARAM_VALUE.TKEEP_W { PARAM_VALUE.TKEEP_W } {
	# Procedure called to update TKEEP_W when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.TKEEP_W { PARAM_VALUE.TKEEP_W } {
	# Procedure called to validate TKEEP_W
	return true
}


proc update_MODELPARAM_VALUE.SAMPLE_W { MODELPARAM_VALUE.SAMPLE_W PARAM_VALUE.SAMPLE_W } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.SAMPLE_W}] ${MODELPARAM_VALUE.SAMPLE_W}
}

proc update_MODELPARAM_VALUE.AXIS_DATA_W { MODELPARAM_VALUE.AXIS_DATA_W PARAM_VALUE.AXIS_DATA_W } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.AXIS_DATA_W}] ${MODELPARAM_VALUE.AXIS_DATA_W}
}

proc update_MODELPARAM_VALUE.SAMPLES_PER_BEAT { MODELPARAM_VALUE.SAMPLES_PER_BEAT PARAM_VALUE.SAMPLES_PER_BEAT } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.SAMPLES_PER_BEAT}] ${MODELPARAM_VALUE.SAMPLES_PER_BEAT}
}

proc update_MODELPARAM_VALUE.PKT_BEATS { MODELPARAM_VALUE.PKT_BEATS PARAM_VALUE.PKT_BEATS } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.PKT_BEATS}] ${MODELPARAM_VALUE.PKT_BEATS}
}

proc update_MODELPARAM_VALUE.TKEEP_W { MODELPARAM_VALUE.TKEEP_W PARAM_VALUE.TKEEP_W } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.TKEEP_W}] ${MODELPARAM_VALUE.TKEEP_W}
}

