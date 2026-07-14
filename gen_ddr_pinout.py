# file gen_ddr_pinout.py
#
# Generate DDR3 pinout constraints for Vivado from a CSV file.
#
import re


def get_attributes(net_signal):
    # strip DDR3_
    net_signal = net_signal.replace("DDR3_", "")    
    # Match the pattern for DDR3 signals with optional index
    # print(net_signal)     
    match = re.match(r"^([A-Z_]+)([0-9]+)?([^0-9]+)?$", net_signal)
    if match:
        signal_type = match.group(1)
        index = match.group(2) if match.group(2) is not None else None
        suffix = match.group(3) if match.group(3) is not None else None
    else:
        print(f"net_signal={net_signal} does not match expected pattern")        
        return [None, None, None, None]
    match (signal_type):
        case "T"| "ACC" : # disconnected 
            return [None, None, None, None]   
        case "D": # data
            return ["ddr3_dq", index, "SSTL15", True]
        case "DM": # data mask
            return ["ddr3_dm", index, "SSTL15", False]
        case "DQS":
            match suffix:
                case "_P":
                    return ["ddr3_dqs_p", index, "DIFF_SSTL15", True]
                case "_N":
                    return ["ddr3_dqs_n", index, "DIFF_SSTL15", True]
        case "A": # address
            return ["ddr3_addr", index, "SSTL15", False]
        case "BA": # bank address
            return ["ddr3_ba", index, "SSTL15", False]
        case "CLK_P": # clock
            return ["ddr3_ck_p", 0, "DIFF_SSTL15", False]
        case "CLK_N": # clock  
            return ["ddr3_ck_n", 0, "DIFF_SSTL15", False]
        case "CKE":
            return ["ddr3_cke", index, "SSTL15", False]
        case "RAS":  
            return ["ddr3_ras_n", index, "SSTL15", False]
        case "CAS":  
            return ["ddr3_cas_n", index, "SSTL15", False]
        case "SO":  
            return ["ddr3_cs_n", 0, "SSTL15", False]
        case "WE":  
            return ["ddr3_we_n", index, "SSTL15", False]
        case "ODT":
            return ["ddr3_odt", 0, "SSTL15", False]
        case "RESET":  
            return ["ddr3_reset_n", index, "LVCMOS15", False]
        case _:
            print (f"Unknown signal type: {signal_type}")
            return [None, None,  None, None]
    
# "ddr3_pins.csv"
# DDR3_A0,U3
# DDR3_A1,W6
# DDR3_A2,V3
# ->
#set_property SLEW FAST [get_ports {ddr3_dq[0]}]
#set_property IOSTANDARD SSTL15 [get_ports {ddr3_dq[0]}]
#set_property PACKAGE_PIN K6 [get_ports {ddr3_dq[0]}]
def gen(in_csv_file="ddr3_pins.csv", out_xdc_file="ddr3_pinout.xdc"):
    with open(in_csv_file, "r") as f:   
        with open(out_xdc_file, "w") as out_f:
            for line in f.readlines():
                net_signal, package_pin = line.strip().split(",")
                port, index, standard, split = get_attributes(net_signal)
                #print(f"port: {port}, standard: {standard}, index: {index}, split: {split}")
                if(port is not None):
                    portname = f"{port}[{index}]" if index is not None else port
                    out_f.write(f"set_property SLEW FAST [get_ports {{{portname}}}]\n")
                    if split:
                        out_f.write(f"set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {{{portname}}}]\n")
                    out_f.write(f"set_property IOSTANDARD {standard} [get_ports {{{portname}}}]\n")
                    out_f.write(f"set_property PACKAGE_PIN {package_pin.strip()} [get_ports {{{portname}}}]\n\n")

if __name__ == "__main__":
    gen()
