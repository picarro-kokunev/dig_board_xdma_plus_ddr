# pcie ref clock  100 Mhz
create_clock -period 10.000 -name pcie_clk -waveform {0.000 5.000} [get_ports pcie_clk_clk_p]

# connection to PCIE connector REFCLK_P pin
set_property PACKAGE_PIN F6 [get_ports {pcie_clk_clk_p[0]}]

# Leds
set_property PACKAGE_PIN A21 [get_ports {led_green_0[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {led_green_0[0]}]
set_property PACKAGE_PIN A20 [get_ports {led_red_0[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {led_red_0[0]}]

# Unused pin
#set_property PACKAGE_PIN A16 [get_ports {unused_0[0]}]
#set_property IOSTANDARD LVCMOS33 [get_ports {unused_0[0]}]


set_property PACKAGE_PIN N17 [get_ports pcie_reset_n]
set_property IOSTANDARD LVCMOS33 [get_ports pcie_reset_n]
set_property PULLTYPE PULLUP [get_ports pcie_reset_n]
set_false_path -from [get_ports pcie_reset_n]


# 200 system clk MHz
set_property PACKAGE_PIN V4 [get_ports sys_clk_clk_p]
set_property PACKAGE_PIN W4 [get_ports sys_clk_clk_n]
set_property IOSTANDARD LVDS_25 [get_ports sys_clk_clk_p]

# ADC
set_property PACKAGE_PIN J22 [get_ports adc_clk_0]
set_property IOSTANDARD LVCMOS33 [get_ports adc_clk_0]
set_property PACKAGE_PIN L14 [get_ports adc_ofa_a_0]
set_property IOSTANDARD LVCMOS33 [get_ports adc_ofa_a_0]


set_property PACKAGE_PIN N19 [get_ports {adc_data_a_0[6]}]
set_property IOSTANDARD LVCMOS33 [get_ports {adc_data_a_0[6]}]
set_property PACKAGE_PIN N20 [get_ports {adc_data_a_0[5]}]
set_property IOSTANDARD LVCMOS33 [get_ports {adc_data_a_0[5]}]
set_property PACKAGE_PIN N18 [get_ports {adc_data_a_0[7]}]
set_property IOSTANDARD LVCMOS33 [get_ports {adc_data_a_0[7]}]
set_property PACKAGE_PIN L15 [get_ports {adc_data_a_0[13]}]
set_property IOSTANDARD LVCMOS33 [get_ports {adc_data_a_0[13]}]
set_property PACKAGE_PIN L16 [get_ports {adc_data_a_0[12]}]
set_property IOSTANDARD LVCMOS33 [get_ports {adc_data_a_0[12]}]
set_property PACKAGE_PIN L21 [get_ports {adc_data_a_0[8]}]
set_property IOSTANDARD LVCMOS33 [get_ports {adc_data_a_0[8]}]
set_property PACKAGE_PIN L20 [get_ports {adc_data_a_0[9]}]
set_property IOSTANDARD LVCMOS33 [get_ports {adc_data_a_0[9]}]
set_property PACKAGE_PIN K22 [get_ports {adc_data_a_0[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {adc_data_a_0[0]}]
set_property PACKAGE_PIN M20 [get_ports {adc_data_a_0[4]}]
set_property IOSTANDARD LVCMOS33 [get_ports {adc_data_a_0[4]}]
set_property PACKAGE_PIN M21 [get_ports {adc_data_a_0[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {adc_data_a_0[3]}]
set_property PACKAGE_PIN N22 [get_ports {adc_data_a_0[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {adc_data_a_0[2]}]
set_property PACKAGE_PIN M22 [get_ports {adc_data_a_0[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {adc_data_a_0[1]}]
set_property PACKAGE_PIN L19 [get_ports {adc_data_a_0[10]}]
set_property IOSTANDARD LVCMOS33 [get_ports {adc_data_a_0[10]}]
set_property PACKAGE_PIN M18 [get_ports {adc_data_a_0[11]}]
set_property IOSTANDARD LVCMOS33 [get_ports {adc_data_a_0[11]}]



# Serial flash

# Set configuration voltage and voltage-related pins
set_property CFGBVS VCCO [current_design]
set_property CONFIG_VOLTAGE 3.3 [current_design]

# Enable QSPI x4 width and maximize clock speed
set_property BITSTREAM.CONFIG.SPI_BUSWIDTH 4 [current_design]
set_property BITSTREAM.CONFIG.CONFIGRATE 50 [current_design]

# Compress bitstream to minimize flash footprint (Optional)
set_property BITSTREAM.GENERAL.COMPRESS TRUE [current_design]

set_property PACKAGE_PIN B8 [get_ports {pcie_mgt_0_rxp[0]}]
set_property PACKAGE_PIN D11 [get_ports {pcie_mgt_0_rxp[1]}]
#set_property PACKAGE_PIN B10 [get_ports {pcie_mgt_0_rxp[2]}]
#set_property PACKAGE_PIN D9 [get_ports {pcie_mgt_0_rxp[3]}]

# SSTL15 with VCCO = 1.5 V  ->  VREF = 0.75 V since no pin in bank34, bank35 is connected to VTT reference voltage
set_property INTERNAL_VREF 0.75 [get_iobanks 34]
set_property INTERNAL_VREF 0.75 [get_iobanks 35]

# I2C connection to the EEPROM M24M01
# SMCLK
set_property PACKAGE_PIN R14 [get_ports iic_rtl_0_scl_io]
set_property IOSTANDARD LVCMOS33 [get_ports iic_rtl_0_scl_io]
# SMDATA
set_property PACKAGE_PIN N13 [get_ports iic_rtl_0_sda_io]
set_property IOSTANDARD LVCMOS33 [get_ports iic_rtl_0_sda_io]


set_false_path -from [get_pins design_1_i/pcie_reset_block_0/self_pcie_reset_0/inst/pcie_reset_reg_reg/C]

set_property C_CLK_INPUT_FREQ_HZ 300000000 [get_debug_cores dbg_hub]
set_property C_ENABLE_CLK_DIVIDER false [get_debug_cores dbg_hub]
set_property C_USER_SCAN_CHAIN 1 [get_debug_cores dbg_hub]
connect_debug_port dbg_hub/clk [get_nets clk]
