#
#  pins_to_xdc
#
import re

def putXdcRecord(netName : str, pin : str):
    print("set_property PACKAGE_PIN {} [get_ports {{{}}}]".format(pin, netName))
    print("set_property IOSTANDARD LVCMOS33 [get_ports {{{}}}]".format(netName))


#
# ADC_DA06, N19
# ADC_DA05, N20
def pin_to_xdc(filename : str = "pins.txt", prefix : str = "adc_data_a_0"):
    with open(filename) as f:
        for line in f.readlines():
            # skip comments
            if line.strip()[0] == "#":
                continue
            [netName, pin] = line.strip().split(",")          
            # ADC_DA12 -> <ADC_DA,12> -> adc_data_a_0[12]
            idx = int(netName.replace("ADC_DA", ""))
            putXdcRecord( prefix + "[{}]".format(idx), pin )


if __name__ == "__main__":
    pin_to_xdc()
