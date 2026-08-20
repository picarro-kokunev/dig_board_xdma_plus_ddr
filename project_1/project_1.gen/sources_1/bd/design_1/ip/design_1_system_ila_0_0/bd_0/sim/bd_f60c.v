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
   (SLOT_0_PCIE_DEBUG_cfg_current_speed,
    SLOT_0_PCIE_DEBUG_cfg_err_cor,
    SLOT_0_PCIE_DEBUG_cfg_err_fatal,
    SLOT_0_PCIE_DEBUG_cfg_err_nonfatal,
    SLOT_0_PCIE_DEBUG_cfg_local_error,
    SLOT_0_PCIE_DEBUG_cfg_local_error_valid,
    SLOT_0_PCIE_DEBUG_cfg_ltssm_state,
    SLOT_0_PCIE_DEBUG_cfg_negotiated_width,
    clk);
  (* X_INTERFACE_INFO = "xilinx.com:display_xdma:pcie_debug:1.0 SLOT_0_PCIE_DEBUG cfg_current_speed" *) (* X_INTERFACE_MODE = "Monitor SlaveType" *) input [2:0]SLOT_0_PCIE_DEBUG_cfg_current_speed;
  (* X_INTERFACE_INFO = "xilinx.com:display_xdma:pcie_debug:1.0 SLOT_0_PCIE_DEBUG cfg_err_cor" *) input SLOT_0_PCIE_DEBUG_cfg_err_cor;
  (* X_INTERFACE_INFO = "xilinx.com:display_xdma:pcie_debug:1.0 SLOT_0_PCIE_DEBUG cfg_err_fatal" *) input SLOT_0_PCIE_DEBUG_cfg_err_fatal;
  (* X_INTERFACE_INFO = "xilinx.com:display_xdma:pcie_debug:1.0 SLOT_0_PCIE_DEBUG cfg_err_nonfatal" *) input SLOT_0_PCIE_DEBUG_cfg_err_nonfatal;
  (* X_INTERFACE_INFO = "xilinx.com:display_xdma:pcie_debug:1.0 SLOT_0_PCIE_DEBUG cfg_local_error" *) input [4:0]SLOT_0_PCIE_DEBUG_cfg_local_error;
  (* X_INTERFACE_INFO = "xilinx.com:display_xdma:pcie_debug:1.0 SLOT_0_PCIE_DEBUG cfg_local_error_valid" *) input SLOT_0_PCIE_DEBUG_cfg_local_error_valid;
  (* X_INTERFACE_INFO = "xilinx.com:display_xdma:pcie_debug:1.0 SLOT_0_PCIE_DEBUG cfg_ltssm_state" *) input [5:0]SLOT_0_PCIE_DEBUG_cfg_ltssm_state;
  (* X_INTERFACE_INFO = "xilinx.com:display_xdma:pcie_debug:1.0 SLOT_0_PCIE_DEBUG cfg_negotiated_width" *) input [3:0]SLOT_0_PCIE_DEBUG_cfg_negotiated_width;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 CLK.CLK CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME CLK.CLK, ASSOCIATED_BUSIF SLOT_0_AXI, ASSOCIATED_RESET resetn, CLK_DOMAIN design_1_xdma_0_0_axi_aclk, FREQ_HZ 125000000, FREQ_TOLERANCE_HZ 0, INSERT_VIP 0, PHASE 0.0" *) input clk;

  wire [2:0]SLOT_0_PCIE_DEBUG_cfg_current_speed;
  wire SLOT_0_PCIE_DEBUG_cfg_err_cor;
  wire SLOT_0_PCIE_DEBUG_cfg_err_fatal;
  wire SLOT_0_PCIE_DEBUG_cfg_err_nonfatal;
  wire [4:0]SLOT_0_PCIE_DEBUG_cfg_local_error;
  wire SLOT_0_PCIE_DEBUG_cfg_local_error_valid;
  wire [5:0]SLOT_0_PCIE_DEBUG_cfg_ltssm_state;
  wire [3:0]SLOT_0_PCIE_DEBUG_cfg_negotiated_width;
  wire clk;

  bd_f60c_ila_lib_0 ila_lib
       (.clk(clk),
        .probe0(SLOT_0_PCIE_DEBUG_cfg_current_speed),
        .probe1(SLOT_0_PCIE_DEBUG_cfg_err_cor),
        .probe2(SLOT_0_PCIE_DEBUG_cfg_err_fatal),
        .probe3(SLOT_0_PCIE_DEBUG_cfg_err_nonfatal),
        .probe4(SLOT_0_PCIE_DEBUG_cfg_local_error),
        .probe5(SLOT_0_PCIE_DEBUG_cfg_local_error_valid),
        .probe6(SLOT_0_PCIE_DEBUG_cfg_ltssm_state),
        .probe7(SLOT_0_PCIE_DEBUG_cfg_negotiated_width));
endmodule
