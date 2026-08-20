// (c) Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// (c) Copyright 2022-2026 Advanced Micro Devices, Inc. All rights reserved.
// 
// This file contains confidential and proprietary information
// of AMD and is protected under U.S. and international copyright
// and other intellectual property laws.
// 
// DISCLAIMER
// This disclaimer is not a license and does not grant any
// rights to the materials distributed herewith. Except as
// otherwise provided in a valid license issued to you by
// AMD, and to the maximum extent permitted by applicable
// law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
// WITH ALL FAULTS, AND AMD HEREBY DISCLAIMS ALL WARRANTIES
// AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
// BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
// INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
// (2) AMD shall not be liable (whether in contract or tort,
// including negligence, or under any other theory of
// liability) for any loss or damage of any kind or nature
// related to, arising under or in connection with these
// materials, including for any direct, or any indirect,
// special, incidental, or consequential loss or damage
// (including loss of data, profits, goodwill, or any type of
// loss or damage suffered as a result of any action brought
// by a third party) even if such damage or loss was
// reasonably foreseeable or AMD had been advised of the
// possibility of the same.
// 
// CRITICAL APPLICATIONS
// AMD products are not designed or intended to be fail-
// safe, or for use in any application requiring fail-safe
// performance, such as life-support or safety devices or
// systems, Class III medical devices, nuclear facilities,
// applications related to the deployment of airbags, or any
// other applications that could lead to death, personal
// injury, or severe property or environmental damage
// (individually and collectively, "Critical
// Applications"). Customer assumes the sole risk and
// liability of any use of AMD products in Critical
// Applications, subject only to applicable laws and
// regulations governing limitations on product liability.
// 
// THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
// PART OF THIS FILE AT ALL TIMES.
// 
// DO NOT MODIFY THIS FILE.


// IP VLNV: xilinx.com:ip:system_ila:1.1
// IP Revision: 22

`timescale 1ns/1ps

(* DowngradeIPIdentifiedWarnings = "yes" *)
module design_1_system_ila_0_0 (
  clk,
  SLOT_0_PCIE_DEBUG_cfg_negotiated_width,
  SLOT_0_PCIE_DEBUG_cfg_current_speed,
  SLOT_0_PCIE_DEBUG_cfg_err_cor,
  SLOT_0_PCIE_DEBUG_cfg_err_fatal,
  SLOT_0_PCIE_DEBUG_cfg_err_nonfatal,
  SLOT_0_PCIE_DEBUG_cfg_local_error,
  SLOT_0_PCIE_DEBUG_cfg_local_error_valid,
  SLOT_0_PCIE_DEBUG_cfg_ltssm_state
);

(* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 CLK.clk CLK" *)
(* X_INTERFACE_MODE = "slave" *)
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME CLK.clk, FREQ_HZ 125000000, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN design_1_xdma_0_0_axi_aclk, ASSOCIATED_BUSIF SLOT_0_AXI, ASSOCIATED_RESET resetn, INSERT_VIP 0" *)
input wire clk;
(* X_INTERFACE_INFO = "xilinx.com:display_xdma:pcie_debug:1.0 SLOT_0_PCIE_DEBUG cfg_negotiated_width" *)
(* X_INTERFACE_MODE = "monitor slave" *)
input wire [3 : 0] SLOT_0_PCIE_DEBUG_cfg_negotiated_width;
(* X_INTERFACE_INFO = "xilinx.com:display_xdma:pcie_debug:1.0 SLOT_0_PCIE_DEBUG cfg_current_speed" *)
input wire [2 : 0] SLOT_0_PCIE_DEBUG_cfg_current_speed;
(* X_INTERFACE_INFO = "xilinx.com:display_xdma:pcie_debug:1.0 SLOT_0_PCIE_DEBUG cfg_err_cor" *)
input wire SLOT_0_PCIE_DEBUG_cfg_err_cor;
(* X_INTERFACE_INFO = "xilinx.com:display_xdma:pcie_debug:1.0 SLOT_0_PCIE_DEBUG cfg_err_fatal" *)
input wire SLOT_0_PCIE_DEBUG_cfg_err_fatal;
(* X_INTERFACE_INFO = "xilinx.com:display_xdma:pcie_debug:1.0 SLOT_0_PCIE_DEBUG cfg_err_nonfatal" *)
input wire SLOT_0_PCIE_DEBUG_cfg_err_nonfatal;
(* X_INTERFACE_INFO = "xilinx.com:display_xdma:pcie_debug:1.0 SLOT_0_PCIE_DEBUG cfg_local_error" *)
input wire [4 : 0] SLOT_0_PCIE_DEBUG_cfg_local_error;
(* X_INTERFACE_INFO = "xilinx.com:display_xdma:pcie_debug:1.0 SLOT_0_PCIE_DEBUG cfg_local_error_valid" *)
input wire SLOT_0_PCIE_DEBUG_cfg_local_error_valid;
(* X_INTERFACE_INFO = "xilinx.com:display_xdma:pcie_debug:1.0 SLOT_0_PCIE_DEBUG cfg_ltssm_state" *)
input wire [5 : 0] SLOT_0_PCIE_DEBUG_cfg_ltssm_state;

  bd_f60c inst (
    .clk(clk),
    .SLOT_0_PCIE_DEBUG_cfg_negotiated_width(SLOT_0_PCIE_DEBUG_cfg_negotiated_width),
    .SLOT_0_PCIE_DEBUG_cfg_current_speed(SLOT_0_PCIE_DEBUG_cfg_current_speed),
    .SLOT_0_PCIE_DEBUG_cfg_err_cor(SLOT_0_PCIE_DEBUG_cfg_err_cor),
    .SLOT_0_PCIE_DEBUG_cfg_err_fatal(SLOT_0_PCIE_DEBUG_cfg_err_fatal),
    .SLOT_0_PCIE_DEBUG_cfg_err_nonfatal(SLOT_0_PCIE_DEBUG_cfg_err_nonfatal),
    .SLOT_0_PCIE_DEBUG_cfg_local_error(SLOT_0_PCIE_DEBUG_cfg_local_error),
    .SLOT_0_PCIE_DEBUG_cfg_local_error_valid(SLOT_0_PCIE_DEBUG_cfg_local_error_valid),
    .SLOT_0_PCIE_DEBUG_cfg_ltssm_state(SLOT_0_PCIE_DEBUG_cfg_ltssm_state)
  );
endmodule
