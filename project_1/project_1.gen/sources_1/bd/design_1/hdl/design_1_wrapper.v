//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2025.2 (lin64) Build 6299465 Fri Nov 14 12:34:56 MST 2025
//Date        : Sat Sep  5 15:42:15 2026
//Host        : emerald running 64-bit Ubuntu 26.04.1 LTS
//Command     : generate_target design_1_wrapper.bd
//Design      : design_1_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module design_1_wrapper
   (iic_a_scl_io,
    iic_a_sda_io,
    iic_pcie_scl_io,
    iic_pcie_sda_io,
    led_green_0,
    led_red_0,
    sys_clk_clk_n,
    sys_clk_clk_p);
  inout iic_a_scl_io;
  inout iic_a_sda_io;
  inout iic_pcie_scl_io;
  inout iic_pcie_sda_io;
  output [0:0]led_green_0;
  output [0:0]led_red_0;
  input sys_clk_clk_n;
  input sys_clk_clk_p;

  wire iic_a_scl_i;
  wire iic_a_scl_io;
  wire iic_a_scl_o;
  wire iic_a_scl_t;
  wire iic_a_sda_i;
  wire iic_a_sda_io;
  wire iic_a_sda_o;
  wire iic_a_sda_t;
  wire iic_pcie_scl_i;
  wire iic_pcie_scl_io;
  wire iic_pcie_scl_o;
  wire iic_pcie_scl_t;
  wire iic_pcie_sda_i;
  wire iic_pcie_sda_io;
  wire iic_pcie_sda_o;
  wire iic_pcie_sda_t;
  wire [0:0]led_green_0;
  wire [0:0]led_red_0;
  wire sys_clk_clk_n;
  wire sys_clk_clk_p;

  design_1 design_1_i
       (.iic_a_scl_i(iic_a_scl_i),
        .iic_a_scl_o(iic_a_scl_o),
        .iic_a_scl_t(iic_a_scl_t),
        .iic_a_sda_i(iic_a_sda_i),
        .iic_a_sda_o(iic_a_sda_o),
        .iic_a_sda_t(iic_a_sda_t),
        .iic_pcie_scl_i(iic_pcie_scl_i),
        .iic_pcie_scl_o(iic_pcie_scl_o),
        .iic_pcie_scl_t(iic_pcie_scl_t),
        .iic_pcie_sda_i(iic_pcie_sda_i),
        .iic_pcie_sda_o(iic_pcie_sda_o),
        .iic_pcie_sda_t(iic_pcie_sda_t),
        .led_green_0(led_green_0),
        .led_red_0(led_red_0),
        .sys_clk_clk_n(sys_clk_clk_n),
        .sys_clk_clk_p(sys_clk_clk_p));
  IOBUF iic_a_scl_iobuf
       (.I(iic_a_scl_o),
        .IO(iic_a_scl_io),
        .O(iic_a_scl_i),
        .T(iic_a_scl_t));
  IOBUF iic_a_sda_iobuf
       (.I(iic_a_sda_o),
        .IO(iic_a_sda_io),
        .O(iic_a_sda_i),
        .T(iic_a_sda_t));
  IOBUF iic_pcie_scl_iobuf
       (.I(iic_pcie_scl_o),
        .IO(iic_pcie_scl_io),
        .O(iic_pcie_scl_i),
        .T(iic_pcie_scl_t));
  IOBUF iic_pcie_sda_iobuf
       (.I(iic_pcie_sda_o),
        .IO(iic_pcie_sda_io),
        .O(iic_pcie_sda_i),
        .T(iic_pcie_sda_t));
endmodule
