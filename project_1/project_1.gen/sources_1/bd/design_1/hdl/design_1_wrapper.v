//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2025.2 (lin64) Build 6299465 Fri Nov 14 12:34:56 MST 2025
//Date        : Tue Jul 21 18:27:11 2026
//Host        : emerald running 64-bit Ubuntu 26.04 LTS
//Command     : generate_target design_1_wrapper.bd
//Design      : design_1_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module design_1_wrapper
   (adc_clk_0,
    adc_data_a_0,
    adc_ofa_a_0,
    led_green_0,
    led_red_0,
    pcie_clk_clk_n,
    pcie_clk_clk_p,
    pcie_mgt_0_rxn,
    pcie_mgt_0_rxp,
    pcie_mgt_0_txn,
    pcie_mgt_0_txp,
    pcie_reset_n,
    sys_clk_clk_n,
    sys_clk_clk_p);
  output adc_clk_0;
  input [13:0]adc_data_a_0;
  input adc_ofa_a_0;
  output [0:0]led_green_0;
  output [0:0]led_red_0;
  input [0:0]pcie_clk_clk_n;
  input [0:0]pcie_clk_clk_p;
  input [1:0]pcie_mgt_0_rxn;
  input [1:0]pcie_mgt_0_rxp;
  output [1:0]pcie_mgt_0_txn;
  output [1:0]pcie_mgt_0_txp;
  input pcie_reset_n;
  input sys_clk_clk_n;
  input sys_clk_clk_p;

  wire adc_clk_0;
  wire [13:0]adc_data_a_0;
  wire adc_ofa_a_0;
  wire [0:0]led_green_0;
  wire [0:0]led_red_0;
  wire [0:0]pcie_clk_clk_n;
  wire [0:0]pcie_clk_clk_p;
  wire [1:0]pcie_mgt_0_rxn;
  wire [1:0]pcie_mgt_0_rxp;
  wire [1:0]pcie_mgt_0_txn;
  wire [1:0]pcie_mgt_0_txp;
  wire pcie_reset_n;
  wire sys_clk_clk_n;
  wire sys_clk_clk_p;

  design_1 design_1_i
       (.adc_clk_0(adc_clk_0),
        .adc_data_a_0(adc_data_a_0),
        .adc_ofa_a_0(adc_ofa_a_0),
        .led_green_0(led_green_0),
        .led_red_0(led_red_0),
        .pcie_clk_clk_n(pcie_clk_clk_n),
        .pcie_clk_clk_p(pcie_clk_clk_p),
        .pcie_mgt_0_rxn(pcie_mgt_0_rxn),
        .pcie_mgt_0_rxp(pcie_mgt_0_rxp),
        .pcie_mgt_0_txn(pcie_mgt_0_txn),
        .pcie_mgt_0_txp(pcie_mgt_0_txp),
        .pcie_reset_n(pcie_reset_n),
        .sys_clk_clk_n(sys_clk_clk_n),
        .sys_clk_clk_p(sys_clk_clk_p));
endmodule
