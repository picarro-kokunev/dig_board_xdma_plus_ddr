# pcie ref clock  100 Mhz
create_clock -period 10.000 -name pcie_clk -waveform {0.000 5.000} [get_ports pcie_clk_clk_p]

# connection to PCIE connector REFCLK_P pin
set_property PACKAGE_PIN F6 [get_ports {pcie_clk_clk_p[0]}]

# Leds
set_property PACKAGE_PIN A21 [get_ports {led_green_0[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {led_green_0[0]}]

# Unused pin


set_property PACKAGE_PIN N17 [get_ports pcie_reset_n]
set_property IOSTANDARD LVCMOS33 [get_ports pcie_reset_n]
set_property PULLTYPE PULLUP [get_ports pcie_reset_n]
set_false_path -from [get_ports pcie_reset_n]
# self reset
set_false_path -from [get_pins design_1_i/self_pcie_reset_0/inst/pcie_reset_reg_reg/C]

# 125 MHz
#create_clock -period 8.000 -name sys_clk -waveform {0.000 4.000} [get_ports sys_clk_clk_p]
# 125 Mhz oscillator connection
# LVDS coupling onboard oscillator

# Serial flash

# Set configuration voltage and voltage-related pins
set_property CFGBVS VCCO [current_design]
set_property CONFIG_VOLTAGE 3.3 [current_design]

# Enable QSPI x4 width and maximize clock speed
set_property BITSTREAM.CONFIG.SPI_BUSWIDTH 4 [current_design]
set_property BITSTREAM.CONFIG.CONFIGRATE 50 [current_design]

# Compress bitstream to minimize flash footprint (Optional)
set_property BITSTREAM.GENERAL.COMPRESS TRUE [current_design]

# SSTL15 with VCCO = 1.5 V  ->  VREF = 0.75 V since no pin in bank34, bank35 is connected to VTT reference voltage
set_property INTERNAL_VREF 0.75 [get_iobanks 34]
set_property INTERNAL_VREF 0.75 [get_iobanks 35]

