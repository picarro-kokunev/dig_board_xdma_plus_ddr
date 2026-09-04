//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Command: generate_target bd_f60c.bd
//Design : bd_f60c
//Purpose: IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CORE_GENERATION_INFO = "bd_f60c,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=bd_f60c,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=1,numReposBlks=1,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=0,numPkgbdBlks=0,bdsource=SBD,synth_mode=None}" *) (* HW_HANDOFF = "design_1_system_ila_0_0.hwdef" *) 
module bd_f60c
   (SLOT_0_IIC_scl_i,
    SLOT_0_IIC_scl_o,
    SLOT_0_IIC_scl_t,
    SLOT_0_IIC_sda_i,
    SLOT_0_IIC_sda_o,
    SLOT_0_IIC_sda_t,
    clk);
  (* X_INTERFACE_INFO = "xilinx.com:interface:iic:1.0 SLOT_0_IIC SCL_I" *) (* X_INTERFACE_MODE = "Monitor SlaveType" *) input SLOT_0_IIC_scl_i;
  (* X_INTERFACE_INFO = "xilinx.com:interface:iic:1.0 SLOT_0_IIC SCL_O" *) input SLOT_0_IIC_scl_o;
  (* X_INTERFACE_INFO = "xilinx.com:interface:iic:1.0 SLOT_0_IIC SCL_T" *) input SLOT_0_IIC_scl_t;
  (* X_INTERFACE_INFO = "xilinx.com:interface:iic:1.0 SLOT_0_IIC SDA_I" *) input SLOT_0_IIC_sda_i;
  (* X_INTERFACE_INFO = "xilinx.com:interface:iic:1.0 SLOT_0_IIC SDA_O" *) input SLOT_0_IIC_sda_o;
  (* X_INTERFACE_INFO = "xilinx.com:interface:iic:1.0 SLOT_0_IIC SDA_T" *) input SLOT_0_IIC_sda_t;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 CLK.CLK CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME CLK.CLK, ASSOCIATED_BUSIF SLOT_0_AXI, ASSOCIATED_RESET resetn, CLK_DOMAIN design_1_clk_wiz_0_0_clk_out1, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, INSERT_VIP 0, PHASE 0.0" *) input clk;

  wire SLOT_0_IIC_scl_i;
  wire SLOT_0_IIC_scl_o;
  wire SLOT_0_IIC_scl_t;
  wire SLOT_0_IIC_sda_i;
  wire SLOT_0_IIC_sda_o;
  wire SLOT_0_IIC_sda_t;
  wire clk;

  bd_f60c_ila_lib_0 ila_lib
       (.clk(clk),
        .probe0(SLOT_0_IIC_scl_i),
        .probe1(SLOT_0_IIC_scl_o),
        .probe2(SLOT_0_IIC_scl_t),
        .probe3(SLOT_0_IIC_sda_i),
        .probe4(SLOT_0_IIC_sda_o),
        .probe5(SLOT_0_IIC_sda_t));
endmodule
