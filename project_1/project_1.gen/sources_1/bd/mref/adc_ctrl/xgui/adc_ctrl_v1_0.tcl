# Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
  ipgui::add_param $IPINST -name "Component_Name"
  #Adding Page
  set Page_0 [ipgui::add_page $IPINST -name "Page 0"]
  ipgui::add_param $IPINST -name "ADC_DATA_W" -parent ${Page_0}
  ipgui::add_param $IPINST -name "ADC_ID_A" -parent ${Page_0}
  ipgui::add_param $IPINST -name "ADC_ID_B" -parent ${Page_0}
  ipgui::add_param $IPINST -name "DATA_W" -parent ${Page_0}


}

proc update_PARAM_VALUE.ADC_DATA_W { PARAM_VALUE.ADC_DATA_W } {
	# Procedure called to update ADC_DATA_W when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.ADC_DATA_W { PARAM_VALUE.ADC_DATA_W } {
	# Procedure called to validate ADC_DATA_W
	return true
}

proc update_PARAM_VALUE.ADC_ID_A { PARAM_VALUE.ADC_ID_A } {
	# Procedure called to update ADC_ID_A when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.ADC_ID_A { PARAM_VALUE.ADC_ID_A } {
	# Procedure called to validate ADC_ID_A
	return true
}

proc update_PARAM_VALUE.ADC_ID_B { PARAM_VALUE.ADC_ID_B } {
	# Procedure called to update ADC_ID_B when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.ADC_ID_B { PARAM_VALUE.ADC_ID_B } {
	# Procedure called to validate ADC_ID_B
	return true
}

proc update_PARAM_VALUE.DATA_W { PARAM_VALUE.DATA_W } {
	# Procedure called to update DATA_W when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.DATA_W { PARAM_VALUE.DATA_W } {
	# Procedure called to validate DATA_W
	return true
}


proc update_MODELPARAM_VALUE.DATA_W { MODELPARAM_VALUE.DATA_W PARAM_VALUE.DATA_W } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.DATA_W}] ${MODELPARAM_VALUE.DATA_W}
}

proc update_MODELPARAM_VALUE.ADC_DATA_W { MODELPARAM_VALUE.ADC_DATA_W PARAM_VALUE.ADC_DATA_W } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.ADC_DATA_W}] ${MODELPARAM_VALUE.ADC_DATA_W}
}

proc update_MODELPARAM_VALUE.ADC_ID_A { MODELPARAM_VALUE.ADC_ID_A PARAM_VALUE.ADC_ID_A } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.ADC_ID_A}] ${MODELPARAM_VALUE.ADC_ID_A}
}

proc update_MODELPARAM_VALUE.ADC_ID_B { MODELPARAM_VALUE.ADC_ID_B PARAM_VALUE.ADC_ID_B } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.ADC_ID_B}] ${MODELPARAM_VALUE.ADC_ID_B}
}

