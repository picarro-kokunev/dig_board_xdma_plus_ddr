//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2025.2 (lin64) Build 6299465 Fri Nov 14 12:34:56 MST 2025
//Date        : Mon Aug 31 11:51:01 2026
//Host        : emerald running 64-bit Ubuntu 26.04 LTS
//Command     : generate_target design_1.bd
//Design      : design_1
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CORE_GENERATION_INFO = "design_1,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=design_1,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=13,numReposBlks=12,numNonXlnxBlks=0,numHierBlks=1,maxHierDepth=1,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=3,numPkgbdBlks=0,bdsource=USER,da_axi4_cnt=5,da_clkrst_cnt=1,synth_mode=None}" *) (* HW_HANDOFF = "design_1.hwdef" *) 
module design_1
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
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 CLK.ADC_CLK_0 CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME CLK.ADC_CLK_0, CLK_DOMAIN design_1_adc_ctrl_0_2_adc_clk, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, INSERT_VIP 0, PHASE 0.0" *) output adc_clk_0;
  input [13:0]adc_data_a_0;
  input adc_ofa_a_0;
  output [0:0]led_green_0;
  output [0:0]led_red_0;
  (* X_INTERFACE_INFO = "xilinx.com:interface:diff_clock:1.0 pcie_clk CLK_N" *) (* X_INTERFACE_MODE = "Slave" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME pcie_clk, CAN_DEBUG false, FREQ_HZ 100000000" *) input [0:0]pcie_clk_clk_n;
  (* X_INTERFACE_INFO = "xilinx.com:interface:diff_clock:1.0 pcie_clk CLK_P" *) input [0:0]pcie_clk_clk_p;
  (* X_INTERFACE_INFO = "xilinx.com:interface:pcie_7x_mgt:1.0 pcie_mgt_0 rxn" *) (* X_INTERFACE_MODE = "Master" *) input [3:0]pcie_mgt_0_rxn;
  (* X_INTERFACE_INFO = "xilinx.com:interface:pcie_7x_mgt:1.0 pcie_mgt_0 rxp" *) input [3:0]pcie_mgt_0_rxp;
  (* X_INTERFACE_INFO = "xilinx.com:interface:pcie_7x_mgt:1.0 pcie_mgt_0 txn" *) output [3:0]pcie_mgt_0_txn;
  (* X_INTERFACE_INFO = "xilinx.com:interface:pcie_7x_mgt:1.0 pcie_mgt_0 txp" *) output [3:0]pcie_mgt_0_txp;
  (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 RST.PCIE_RESET_N RST" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME RST.PCIE_RESET_N, INSERT_VIP 0, POLARITY ACTIVE_LOW" *) input pcie_reset_n;
  (* X_INTERFACE_INFO = "xilinx.com:interface:diff_clock:1.0 sys_clk CLK_N" *) (* X_INTERFACE_MODE = "Slave" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME sys_clk, CAN_DEBUG false, FREQ_HZ 200000000" *) input sys_clk_clk_n;
  (* X_INTERFACE_INFO = "xilinx.com:interface:diff_clock:1.0 sys_clk CLK_P" *) input sys_clk_clk_p;

  wire [127:0]adc_c2h_bridge_0_m_axis_TDATA;
  wire [15:0]adc_c2h_bridge_0_m_axis_TKEEP;
  wire adc_c2h_bridge_0_m_axis_TLAST;
  wire adc_c2h_bridge_0_m_axis_TREADY;
  wire adc_c2h_bridge_0_m_axis_TVALID;
  wire adc_clk_0;
  wire [15:0]adc_ctrl_0_data;
  wire [13:0]adc_data_a_0;
  wire adc_ofa_a_0;
  wire [8:0]axi_smc_M00_AXI_ARADDR;
  wire axi_smc_M00_AXI_ARREADY;
  wire axi_smc_M00_AXI_ARVALID;
  wire [8:0]axi_smc_M00_AXI_AWADDR;
  wire axi_smc_M00_AXI_AWREADY;
  wire axi_smc_M00_AXI_AWVALID;
  wire axi_smc_M00_AXI_BREADY;
  wire [1:0]axi_smc_M00_AXI_BRESP;
  wire axi_smc_M00_AXI_BVALID;
  wire [31:0]axi_smc_M00_AXI_RDATA;
  wire axi_smc_M00_AXI_RREADY;
  wire [1:0]axi_smc_M00_AXI_RRESP;
  wire axi_smc_M00_AXI_RVALID;
  wire [31:0]axi_smc_M00_AXI_WDATA;
  wire axi_smc_M00_AXI_WREADY;
  wire [3:0]axi_smc_M00_AXI_WSTRB;
  wire axi_smc_M00_AXI_WVALID;
  wire [0:0]c_sample_valid_1_dout;
  wire clk_wiz_0_clk_out1;
  wire clk_wiz_0_locked;
  wire ilvector_logic_0_Res;
  wire [0:0]ilvector_logic_0_Res1;
  wire [0:0]led_green_0;
  wire [0:0]led_red_0;
  wire [0:0]pcie_clk_clk_n;
  wire [0:0]pcie_clk_clk_p;
  wire [3:0]pcie_mgt_0_rxn;
  wire [3:0]pcie_mgt_0_rxp;
  wire [3:0]pcie_mgt_0_txn;
  wire [3:0]pcie_mgt_0_txp;
  wire pcie_reset_n;
  wire sys_clk_clk_n;
  wire sys_clk_clk_p;
  wire [0:0]util_ds_buf_0_IBUF_OUT;
  wire [127:0]xdma_0_M_AXIS_H2C_0_TDATA;
  wire [15:0]xdma_0_M_AXIS_H2C_0_TKEEP;
  wire xdma_0_M_AXIS_H2C_0_TLAST;
  wire xdma_0_M_AXIS_H2C_0_TREADY;
  wire xdma_0_M_AXIS_H2C_0_TVALID;
  wire [31:0]xdma_0_M_AXI_LITE_ARADDR;
  wire [2:0]xdma_0_M_AXI_LITE_ARPROT;
  wire xdma_0_M_AXI_LITE_ARREADY;
  wire xdma_0_M_AXI_LITE_ARVALID;
  wire [31:0]xdma_0_M_AXI_LITE_AWADDR;
  wire [2:0]xdma_0_M_AXI_LITE_AWPROT;
  wire xdma_0_M_AXI_LITE_AWREADY;
  wire xdma_0_M_AXI_LITE_AWVALID;
  wire xdma_0_M_AXI_LITE_BREADY;
  wire [1:0]xdma_0_M_AXI_LITE_BRESP;
  wire xdma_0_M_AXI_LITE_BVALID;
  wire [31:0]xdma_0_M_AXI_LITE_RDATA;
  wire xdma_0_M_AXI_LITE_RREADY;
  wire [1:0]xdma_0_M_AXI_LITE_RRESP;
  wire xdma_0_M_AXI_LITE_RVALID;
  wire [31:0]xdma_0_M_AXI_LITE_WDATA;
  wire xdma_0_M_AXI_LITE_WREADY;
  wire [3:0]xdma_0_M_AXI_LITE_WSTRB;
  wire xdma_0_M_AXI_LITE_WVALID;
  wire xdma_0_axi_aclk;
  wire xdma_0_user_lnk_up;

  design_1_adc_c2h_bridge_0_1 adc_c2h_bridge_0
       (.m_axis_aclk(xdma_0_axi_aclk),
        .m_axis_aresetn(ilvector_logic_0_Res),
        .m_axis_tdata(adc_c2h_bridge_0_m_axis_TDATA),
        .m_axis_tkeep(adc_c2h_bridge_0_m_axis_TKEEP),
        .m_axis_tlast(adc_c2h_bridge_0_m_axis_TLAST),
        .m_axis_tready(adc_c2h_bridge_0_m_axis_TREADY),
        .m_axis_tvalid(adc_c2h_bridge_0_m_axis_TVALID),
        .sample_clk(clk_wiz_0_clk_out1),
        .sample_data(adc_ctrl_0_data),
        .sample_rst_n(clk_wiz_0_locked),
        .sample_valid(c_sample_valid_1_dout));
  design_1_adc_ctrl_0_2 adc_ctrl_0
       (.adc_clk(adc_clk_0),
        .adc_data_a(adc_data_a_0),
        .adc_ofa_a(adc_ofa_a_0),
        .clk(clk_wiz_0_clk_out1),
        .data(adc_ctrl_0_data),
        .reset_n(clk_wiz_0_locked));
  design_1_axi_gpio_0_0 axi_gpio_0
       (.gpio_io_o(led_red_0),
        .s_axi_aclk(xdma_0_axi_aclk),
        .s_axi_araddr(axi_smc_M00_AXI_ARADDR),
        .s_axi_aresetn(ilvector_logic_0_Res),
        .s_axi_arready(axi_smc_M00_AXI_ARREADY),
        .s_axi_arvalid(axi_smc_M00_AXI_ARVALID),
        .s_axi_awaddr(axi_smc_M00_AXI_AWADDR),
        .s_axi_awready(axi_smc_M00_AXI_AWREADY),
        .s_axi_awvalid(axi_smc_M00_AXI_AWVALID),
        .s_axi_bready(axi_smc_M00_AXI_BREADY),
        .s_axi_bresp(axi_smc_M00_AXI_BRESP),
        .s_axi_bvalid(axi_smc_M00_AXI_BVALID),
        .s_axi_rdata(axi_smc_M00_AXI_RDATA),
        .s_axi_rready(axi_smc_M00_AXI_RREADY),
        .s_axi_rresp(axi_smc_M00_AXI_RRESP),
        .s_axi_rvalid(axi_smc_M00_AXI_RVALID),
        .s_axi_wdata(axi_smc_M00_AXI_WDATA),
        .s_axi_wready(axi_smc_M00_AXI_WREADY),
        .s_axi_wstrb(axi_smc_M00_AXI_WSTRB),
        .s_axi_wvalid(axi_smc_M00_AXI_WVALID));
  design_1_axi_smc_0 axi_smc
       (.M00_AXI_araddr(axi_smc_M00_AXI_ARADDR),
        .M00_AXI_arready(axi_smc_M00_AXI_ARREADY),
        .M00_AXI_arvalid(axi_smc_M00_AXI_ARVALID),
        .M00_AXI_awaddr(axi_smc_M00_AXI_AWADDR),
        .M00_AXI_awready(axi_smc_M00_AXI_AWREADY),
        .M00_AXI_awvalid(axi_smc_M00_AXI_AWVALID),
        .M00_AXI_bready(axi_smc_M00_AXI_BREADY),
        .M00_AXI_bresp(axi_smc_M00_AXI_BRESP),
        .M00_AXI_bvalid(axi_smc_M00_AXI_BVALID),
        .M00_AXI_rdata(axi_smc_M00_AXI_RDATA),
        .M00_AXI_rready(axi_smc_M00_AXI_RREADY),
        .M00_AXI_rresp(axi_smc_M00_AXI_RRESP),
        .M00_AXI_rvalid(axi_smc_M00_AXI_RVALID),
        .M00_AXI_wdata(axi_smc_M00_AXI_WDATA),
        .M00_AXI_wready(axi_smc_M00_AXI_WREADY),
        .M00_AXI_wstrb(axi_smc_M00_AXI_WSTRB),
        .M00_AXI_wvalid(axi_smc_M00_AXI_WVALID),
        .S00_AXI_araddr(xdma_0_M_AXI_LITE_ARADDR),
        .S00_AXI_arprot(xdma_0_M_AXI_LITE_ARPROT),
        .S00_AXI_arready(xdma_0_M_AXI_LITE_ARREADY),
        .S00_AXI_arvalid(xdma_0_M_AXI_LITE_ARVALID),
        .S00_AXI_awaddr(xdma_0_M_AXI_LITE_AWADDR),
        .S00_AXI_awprot(xdma_0_M_AXI_LITE_AWPROT),
        .S00_AXI_awready(xdma_0_M_AXI_LITE_AWREADY),
        .S00_AXI_awvalid(xdma_0_M_AXI_LITE_AWVALID),
        .S00_AXI_bready(xdma_0_M_AXI_LITE_BREADY),
        .S00_AXI_bresp(xdma_0_M_AXI_LITE_BRESP),
        .S00_AXI_bvalid(xdma_0_M_AXI_LITE_BVALID),
        .S00_AXI_rdata(xdma_0_M_AXI_LITE_RDATA),
        .S00_AXI_rready(xdma_0_M_AXI_LITE_RREADY),
        .S00_AXI_rresp(xdma_0_M_AXI_LITE_RRESP),
        .S00_AXI_rvalid(xdma_0_M_AXI_LITE_RVALID),
        .S00_AXI_wdata(xdma_0_M_AXI_LITE_WDATA),
        .S00_AXI_wready(xdma_0_M_AXI_LITE_WREADY),
        .S00_AXI_wstrb(xdma_0_M_AXI_LITE_WSTRB),
        .S00_AXI_wvalid(xdma_0_M_AXI_LITE_WVALID),
        .aclk(xdma_0_axi_aclk),
        .aresetn(ilvector_logic_0_Res));
  design_1_c_sample_valid_1_0 c_sample_valid_1
       (.dout(c_sample_valid_1_dout));
  design_1_clk_wiz_0_1 clk_wiz_0
       (.clk_in1_n(sys_clk_clk_n),
        .clk_in1_p(sys_clk_clk_p),
        .clk_out1(clk_wiz_0_clk_out1),
        .locked(clk_wiz_0_locked),
        .resetn(pcie_reset_n));
  assign led_green_0 = ~ xdma_0_user_lnk_up;
  pcie_reset_block_0_imp_1DUQC89 pcie_reset_block_0
       (.BUFG_I(util_ds_buf_0_IBUF_OUT),
        .Res(ilvector_logic_0_Res1),
        .pcie_reset_n(pcie_reset_n));
  design_1_util_ds_buf_0_0 util_ds_buf_0
       (.IBUF_DS_N(pcie_clk_clk_n),
        .IBUF_DS_P(pcie_clk_clk_p),
        .IBUF_OUT(util_ds_buf_0_IBUF_OUT));
  design_1_xdma_0_0 xdma_0
       (.axi_aclk(xdma_0_axi_aclk),
        .axi_aresetn(ilvector_logic_0_Res),
        .cfg_mgmt_addr({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .cfg_mgmt_byte_enable({1'b0,1'b0,1'b0,1'b0}),
        .cfg_mgmt_read(1'b0),
        .cfg_mgmt_type1_cfg_reg_access(1'b0),
        .cfg_mgmt_write(1'b0),
        .cfg_mgmt_write_data({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .m_axil_araddr(xdma_0_M_AXI_LITE_ARADDR),
        .m_axil_arprot(xdma_0_M_AXI_LITE_ARPROT),
        .m_axil_arready(xdma_0_M_AXI_LITE_ARREADY),
        .m_axil_arvalid(xdma_0_M_AXI_LITE_ARVALID),
        .m_axil_awaddr(xdma_0_M_AXI_LITE_AWADDR),
        .m_axil_awprot(xdma_0_M_AXI_LITE_AWPROT),
        .m_axil_awready(xdma_0_M_AXI_LITE_AWREADY),
        .m_axil_awvalid(xdma_0_M_AXI_LITE_AWVALID),
        .m_axil_bready(xdma_0_M_AXI_LITE_BREADY),
        .m_axil_bresp(xdma_0_M_AXI_LITE_BRESP),
        .m_axil_bvalid(xdma_0_M_AXI_LITE_BVALID),
        .m_axil_rdata(xdma_0_M_AXI_LITE_RDATA),
        .m_axil_rready(xdma_0_M_AXI_LITE_RREADY),
        .m_axil_rresp(xdma_0_M_AXI_LITE_RRESP),
        .m_axil_rvalid(xdma_0_M_AXI_LITE_RVALID),
        .m_axil_wdata(xdma_0_M_AXI_LITE_WDATA),
        .m_axil_wready(xdma_0_M_AXI_LITE_WREADY),
        .m_axil_wstrb(xdma_0_M_AXI_LITE_WSTRB),
        .m_axil_wvalid(xdma_0_M_AXI_LITE_WVALID),
        .m_axis_h2c_tdata_0(xdma_0_M_AXIS_H2C_0_TDATA),
        .m_axis_h2c_tkeep_0(xdma_0_M_AXIS_H2C_0_TKEEP),
        .m_axis_h2c_tlast_0(xdma_0_M_AXIS_H2C_0_TLAST),
        .m_axis_h2c_tready_0(xdma_0_M_AXIS_H2C_0_TREADY),
        .m_axis_h2c_tready_1(1'b1),
        .m_axis_h2c_tvalid_0(xdma_0_M_AXIS_H2C_0_TVALID),
        .pci_exp_rxn(pcie_mgt_0_rxn),
        .pci_exp_rxp(pcie_mgt_0_rxp),
        .pci_exp_txn(pcie_mgt_0_txn),
        .pci_exp_txp(pcie_mgt_0_txp),
        .s_axis_c2h_tdata_0(xdma_0_M_AXIS_H2C_0_TDATA),
        .s_axis_c2h_tdata_1(adc_c2h_bridge_0_m_axis_TDATA),
        .s_axis_c2h_tkeep_0(xdma_0_M_AXIS_H2C_0_TKEEP),
        .s_axis_c2h_tkeep_1(adc_c2h_bridge_0_m_axis_TKEEP),
        .s_axis_c2h_tlast_0(xdma_0_M_AXIS_H2C_0_TLAST),
        .s_axis_c2h_tlast_1(adc_c2h_bridge_0_m_axis_TLAST),
        .s_axis_c2h_tready_0(xdma_0_M_AXIS_H2C_0_TREADY),
        .s_axis_c2h_tready_1(adc_c2h_bridge_0_m_axis_TREADY),
        .s_axis_c2h_tvalid_0(xdma_0_M_AXIS_H2C_0_TVALID),
        .s_axis_c2h_tvalid_1(adc_c2h_bridge_0_m_axis_TVALID),
        .sys_clk(util_ds_buf_0_IBUF_OUT),
        .sys_rst_n(ilvector_logic_0_Res1),
        .user_lnk_up(xdma_0_user_lnk_up),
        .usr_irq_req(1'b0));
endmodule

module pcie_reset_block_0_imp_1DUQC89
   (BUFG_I,
    Res,
    pcie_reset_n);
  input [0:0]BUFG_I;
  output [0:0]Res;
  input [0:0]pcie_reset_n;

  wire [0:0]BUFG_I;
  wire [0:0]Res;
  wire [0:0]pcie_reset_n;
  wire self_pcie_reset_0_pcie_reset_n;
  wire [0:0]util_ds_buf_1_BUFG_O;

  assign Res = self_pcie_reset_0_pcie_reset_n & pcie_reset_n;
  design_1_self_pcie_reset_0_0 self_pcie_reset_0
       (.clk(util_ds_buf_1_BUFG_O),
        .pcie_reset_n(self_pcie_reset_0_pcie_reset_n));
  design_1_util_ds_buf_1_0 util_ds_buf_1
       (.BUFG_I(BUFG_I),
        .BUFG_O(util_ds_buf_1_BUFG_O));
endmodule
