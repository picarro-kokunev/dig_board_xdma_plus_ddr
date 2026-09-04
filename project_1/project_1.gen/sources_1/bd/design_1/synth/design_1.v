//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2025.2 (lin64) Build 6299465 Fri Nov 14 12:34:56 MST 2025
//Date        : Fri Sep  4 14:37:00 2026
//Host        : emerald running 64-bit Ubuntu 26.04.1 LTS
//Command     : generate_target design_1.bd
//Design      : design_1
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CORE_GENERATION_INFO = "design_1,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=design_1,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=9,numReposBlks=9,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=0,numPkgbdBlks=0,bdsource=USER,da_axi4_cnt=6,da_board_cnt=1,synth_mode=None}" *) (* HW_HANDOFF = "design_1.hwdef" *) 
module design_1
   (iic_rtl_0_scl_i,
    iic_rtl_0_scl_o,
    iic_rtl_0_scl_t,
    iic_rtl_0_sda_i,
    iic_rtl_0_sda_o,
    iic_rtl_0_sda_t,
    led_green_0,
    led_red_0,
    sys_clk_clk_n,
    sys_clk_clk_p);
  (* X_INTERFACE_INFO = "xilinx.com:interface:iic:1.0 iic_rtl_0 SCL_I" *) (* X_INTERFACE_MODE = "Master" *) input iic_rtl_0_scl_i;
  (* X_INTERFACE_INFO = "xilinx.com:interface:iic:1.0 iic_rtl_0 SCL_O" *) output iic_rtl_0_scl_o;
  (* X_INTERFACE_INFO = "xilinx.com:interface:iic:1.0 iic_rtl_0 SCL_T" *) output iic_rtl_0_scl_t;
  (* X_INTERFACE_INFO = "xilinx.com:interface:iic:1.0 iic_rtl_0 SDA_I" *) input iic_rtl_0_sda_i;
  (* X_INTERFACE_INFO = "xilinx.com:interface:iic:1.0 iic_rtl_0 SDA_O" *) output iic_rtl_0_sda_o;
  (* X_INTERFACE_INFO = "xilinx.com:interface:iic:1.0 iic_rtl_0 SDA_T" *) output iic_rtl_0_sda_t;
  output [0:0]led_green_0;
  output [0:0]led_red_0;
  (* X_INTERFACE_INFO = "xilinx.com:interface:diff_clock:1.0 sys_clk CLK_N" *) (* X_INTERFACE_MODE = "Slave" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME sys_clk, CAN_DEBUG false, FREQ_HZ 100000000" *) input sys_clk_clk_n;
  (* X_INTERFACE_INFO = "xilinx.com:interface:diff_clock:1.0 sys_clk CLK_P" *) input sys_clk_clk_p;

  (* CONN_BUS_INFO = "axi_iic_0_IIC xilinx.com:interface:iic:1.0 None SCL_I" *) (* DONT_TOUCH *) wire axi_iic_0_IIC_SCL_I;
  (* CONN_BUS_INFO = "axi_iic_0_IIC xilinx.com:interface:iic:1.0 None SCL_O" *) (* DONT_TOUCH *) wire axi_iic_0_IIC_SCL_O;
  (* CONN_BUS_INFO = "axi_iic_0_IIC xilinx.com:interface:iic:1.0 None SCL_T" *) (* DONT_TOUCH *) wire axi_iic_0_IIC_SCL_T;
  (* CONN_BUS_INFO = "axi_iic_0_IIC xilinx.com:interface:iic:1.0 None SDA_I" *) (* DONT_TOUCH *) wire axi_iic_0_IIC_SDA_I;
  (* CONN_BUS_INFO = "axi_iic_0_IIC xilinx.com:interface:iic:1.0 None SDA_O" *) (* DONT_TOUCH *) wire axi_iic_0_IIC_SDA_O;
  (* CONN_BUS_INFO = "axi_iic_0_IIC xilinx.com:interface:iic:1.0 None SDA_T" *) (* DONT_TOUCH *) wire axi_iic_0_IIC_SDA_T;
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
  wire [8:0]axi_smc_M01_AXI_ARADDR;
  wire axi_smc_M01_AXI_ARREADY;
  wire axi_smc_M01_AXI_ARVALID;
  wire [8:0]axi_smc_M01_AXI_AWADDR;
  wire axi_smc_M01_AXI_AWREADY;
  wire axi_smc_M01_AXI_AWVALID;
  wire axi_smc_M01_AXI_BREADY;
  wire [1:0]axi_smc_M01_AXI_BRESP;
  wire axi_smc_M01_AXI_BVALID;
  wire [31:0]axi_smc_M01_AXI_RDATA;
  wire axi_smc_M01_AXI_RREADY;
  wire [1:0]axi_smc_M01_AXI_RRESP;
  wire axi_smc_M01_AXI_RVALID;
  wire [31:0]axi_smc_M01_AXI_WDATA;
  wire axi_smc_M01_AXI_WREADY;
  wire [3:0]axi_smc_M01_AXI_WSTRB;
  wire axi_smc_M01_AXI_WVALID;
  wire [24:0]c_counter_binary_0_Q;
  wire ilconstant_0_dout;
  wire [0:0]ilconstant_0_dout1;
  wire [31:0]jtag_axi_0_M_AXI_ARADDR;
  wire [1:0]jtag_axi_0_M_AXI_ARBURST;
  wire [3:0]jtag_axi_0_M_AXI_ARCACHE;
  wire [0:0]jtag_axi_0_M_AXI_ARID;
  wire [7:0]jtag_axi_0_M_AXI_ARLEN;
  wire jtag_axi_0_M_AXI_ARLOCK;
  wire [2:0]jtag_axi_0_M_AXI_ARPROT;
  wire [3:0]jtag_axi_0_M_AXI_ARQOS;
  wire jtag_axi_0_M_AXI_ARREADY;
  wire [2:0]jtag_axi_0_M_AXI_ARSIZE;
  wire jtag_axi_0_M_AXI_ARVALID;
  wire [31:0]jtag_axi_0_M_AXI_AWADDR;
  wire [1:0]jtag_axi_0_M_AXI_AWBURST;
  wire [3:0]jtag_axi_0_M_AXI_AWCACHE;
  wire [0:0]jtag_axi_0_M_AXI_AWID;
  wire [7:0]jtag_axi_0_M_AXI_AWLEN;
  wire jtag_axi_0_M_AXI_AWLOCK;
  wire [2:0]jtag_axi_0_M_AXI_AWPROT;
  wire [3:0]jtag_axi_0_M_AXI_AWQOS;
  wire jtag_axi_0_M_AXI_AWREADY;
  wire [2:0]jtag_axi_0_M_AXI_AWSIZE;
  wire jtag_axi_0_M_AXI_AWVALID;
  wire [0:0]jtag_axi_0_M_AXI_BID;
  wire jtag_axi_0_M_AXI_BREADY;
  wire [1:0]jtag_axi_0_M_AXI_BRESP;
  wire jtag_axi_0_M_AXI_BVALID;
  wire [31:0]jtag_axi_0_M_AXI_RDATA;
  wire [0:0]jtag_axi_0_M_AXI_RID;
  wire jtag_axi_0_M_AXI_RLAST;
  wire jtag_axi_0_M_AXI_RREADY;
  wire [1:0]jtag_axi_0_M_AXI_RRESP;
  wire jtag_axi_0_M_AXI_RVALID;
  wire [31:0]jtag_axi_0_M_AXI_WDATA;
  wire jtag_axi_0_M_AXI_WLAST;
  wire jtag_axi_0_M_AXI_WREADY;
  wire [3:0]jtag_axi_0_M_AXI_WSTRB;
  wire jtag_axi_0_M_AXI_WVALID;
  wire [0:0]led_green_0;
  wire [0:0]led_red_0;
  wire sys_clk_clk_n;
  wire sys_clk_clk_p;
  wire util_ds_buf_0_IBUF_OUT;

  assign axi_iic_0_IIC_SCL_I = iic_rtl_0_scl_i;
  assign axi_iic_0_IIC_SDA_I = iic_rtl_0_sda_i;
  assign iic_rtl_0_scl_o = axi_iic_0_IIC_SCL_O;
  assign iic_rtl_0_scl_t = axi_iic_0_IIC_SCL_T;
  assign iic_rtl_0_sda_o = axi_iic_0_IIC_SDA_O;
  assign iic_rtl_0_sda_t = axi_iic_0_IIC_SDA_T;
  design_1_axi_gpio_0_1 axi_gpio_0
       (.gpio_io_o(led_green_0),
        .s_axi_aclk(util_ds_buf_0_IBUF_OUT),
        .s_axi_araddr(axi_smc_M00_AXI_ARADDR),
        .s_axi_aresetn(ilconstant_0_dout),
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
  design_1_axi_iic_0_0 axi_iic_0
       (.s_axi_aclk(util_ds_buf_0_IBUF_OUT),
        .s_axi_araddr(axi_smc_M01_AXI_ARADDR),
        .s_axi_aresetn(ilconstant_0_dout),
        .s_axi_arready(axi_smc_M01_AXI_ARREADY),
        .s_axi_arvalid(axi_smc_M01_AXI_ARVALID),
        .s_axi_awaddr(axi_smc_M01_AXI_AWADDR),
        .s_axi_awready(axi_smc_M01_AXI_AWREADY),
        .s_axi_awvalid(axi_smc_M01_AXI_AWVALID),
        .s_axi_bready(axi_smc_M01_AXI_BREADY),
        .s_axi_bresp(axi_smc_M01_AXI_BRESP),
        .s_axi_bvalid(axi_smc_M01_AXI_BVALID),
        .s_axi_rdata(axi_smc_M01_AXI_RDATA),
        .s_axi_rready(axi_smc_M01_AXI_RREADY),
        .s_axi_rresp(axi_smc_M01_AXI_RRESP),
        .s_axi_rvalid(axi_smc_M01_AXI_RVALID),
        .s_axi_wdata(axi_smc_M01_AXI_WDATA),
        .s_axi_wready(axi_smc_M01_AXI_WREADY),
        .s_axi_wstrb(axi_smc_M01_AXI_WSTRB),
        .s_axi_wvalid(axi_smc_M01_AXI_WVALID),
        .scl_i(axi_iic_0_IIC_SCL_I),
        .scl_o(axi_iic_0_IIC_SCL_O),
        .scl_t(axi_iic_0_IIC_SCL_T),
        .sda_i(axi_iic_0_IIC_SDA_I),
        .sda_o(axi_iic_0_IIC_SDA_O),
        .sda_t(axi_iic_0_IIC_SDA_T));
  design_1_axi_smc_2 axi_smc
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
        .M01_AXI_araddr(axi_smc_M01_AXI_ARADDR),
        .M01_AXI_arready(axi_smc_M01_AXI_ARREADY),
        .M01_AXI_arvalid(axi_smc_M01_AXI_ARVALID),
        .M01_AXI_awaddr(axi_smc_M01_AXI_AWADDR),
        .M01_AXI_awready(axi_smc_M01_AXI_AWREADY),
        .M01_AXI_awvalid(axi_smc_M01_AXI_AWVALID),
        .M01_AXI_bready(axi_smc_M01_AXI_BREADY),
        .M01_AXI_bresp(axi_smc_M01_AXI_BRESP),
        .M01_AXI_bvalid(axi_smc_M01_AXI_BVALID),
        .M01_AXI_rdata(axi_smc_M01_AXI_RDATA),
        .M01_AXI_rready(axi_smc_M01_AXI_RREADY),
        .M01_AXI_rresp(axi_smc_M01_AXI_RRESP),
        .M01_AXI_rvalid(axi_smc_M01_AXI_RVALID),
        .M01_AXI_wdata(axi_smc_M01_AXI_WDATA),
        .M01_AXI_wready(axi_smc_M01_AXI_WREADY),
        .M01_AXI_wstrb(axi_smc_M01_AXI_WSTRB),
        .M01_AXI_wvalid(axi_smc_M01_AXI_WVALID),
        .S00_AXI_araddr(jtag_axi_0_M_AXI_ARADDR),
        .S00_AXI_arburst(jtag_axi_0_M_AXI_ARBURST),
        .S00_AXI_arcache(jtag_axi_0_M_AXI_ARCACHE),
        .S00_AXI_arid(jtag_axi_0_M_AXI_ARID),
        .S00_AXI_arlen(jtag_axi_0_M_AXI_ARLEN),
        .S00_AXI_arlock(jtag_axi_0_M_AXI_ARLOCK),
        .S00_AXI_arprot(jtag_axi_0_M_AXI_ARPROT),
        .S00_AXI_arqos(jtag_axi_0_M_AXI_ARQOS),
        .S00_AXI_arready(jtag_axi_0_M_AXI_ARREADY),
        .S00_AXI_arsize(jtag_axi_0_M_AXI_ARSIZE),
        .S00_AXI_arvalid(jtag_axi_0_M_AXI_ARVALID),
        .S00_AXI_awaddr(jtag_axi_0_M_AXI_AWADDR),
        .S00_AXI_awburst(jtag_axi_0_M_AXI_AWBURST),
        .S00_AXI_awcache(jtag_axi_0_M_AXI_AWCACHE),
        .S00_AXI_awid(jtag_axi_0_M_AXI_AWID),
        .S00_AXI_awlen(jtag_axi_0_M_AXI_AWLEN),
        .S00_AXI_awlock(jtag_axi_0_M_AXI_AWLOCK),
        .S00_AXI_awprot(jtag_axi_0_M_AXI_AWPROT),
        .S00_AXI_awqos(jtag_axi_0_M_AXI_AWQOS),
        .S00_AXI_awready(jtag_axi_0_M_AXI_AWREADY),
        .S00_AXI_awsize(jtag_axi_0_M_AXI_AWSIZE),
        .S00_AXI_awvalid(jtag_axi_0_M_AXI_AWVALID),
        .S00_AXI_bid(jtag_axi_0_M_AXI_BID),
        .S00_AXI_bready(jtag_axi_0_M_AXI_BREADY),
        .S00_AXI_bresp(jtag_axi_0_M_AXI_BRESP),
        .S00_AXI_bvalid(jtag_axi_0_M_AXI_BVALID),
        .S00_AXI_rdata(jtag_axi_0_M_AXI_RDATA),
        .S00_AXI_rid(jtag_axi_0_M_AXI_RID),
        .S00_AXI_rlast(jtag_axi_0_M_AXI_RLAST),
        .S00_AXI_rready(jtag_axi_0_M_AXI_RREADY),
        .S00_AXI_rresp(jtag_axi_0_M_AXI_RRESP),
        .S00_AXI_rvalid(jtag_axi_0_M_AXI_RVALID),
        .S00_AXI_wdata(jtag_axi_0_M_AXI_WDATA),
        .S00_AXI_wlast(jtag_axi_0_M_AXI_WLAST),
        .S00_AXI_wready(jtag_axi_0_M_AXI_WREADY),
        .S00_AXI_wstrb(jtag_axi_0_M_AXI_WSTRB),
        .S00_AXI_wvalid(jtag_axi_0_M_AXI_WVALID),
        .aclk(util_ds_buf_0_IBUF_OUT),
        .aresetn(ilconstant_0_dout));
  design_1_c_counter_binary_0_1 c_counter_binary_0
       (.CLK(util_ds_buf_0_IBUF_OUT),
        .Q(c_counter_binary_0_Q));
  design_1_clk_wiz_0_0 clk_wiz_0
       (.clk_in1_n(sys_clk_clk_n),
        .clk_in1_p(sys_clk_clk_p),
        .clk_out1(util_ds_buf_0_IBUF_OUT),
        .locked(ilconstant_0_dout),
        .resetn(ilconstant_0_dout1));
  assign ilconstant_0_dout1 = 1'h1;
  assign led_red_0 = c_counter_binary_0_Q[24:24];
  design_1_jtag_axi_0_0 jtag_axi_0
       (.aclk(util_ds_buf_0_IBUF_OUT),
        .aresetn(ilconstant_0_dout),
        .m_axi_araddr(jtag_axi_0_M_AXI_ARADDR),
        .m_axi_arburst(jtag_axi_0_M_AXI_ARBURST),
        .m_axi_arcache(jtag_axi_0_M_AXI_ARCACHE),
        .m_axi_arid(jtag_axi_0_M_AXI_ARID),
        .m_axi_arlen(jtag_axi_0_M_AXI_ARLEN),
        .m_axi_arlock(jtag_axi_0_M_AXI_ARLOCK),
        .m_axi_arprot(jtag_axi_0_M_AXI_ARPROT),
        .m_axi_arqos(jtag_axi_0_M_AXI_ARQOS),
        .m_axi_arready(jtag_axi_0_M_AXI_ARREADY),
        .m_axi_arsize(jtag_axi_0_M_AXI_ARSIZE),
        .m_axi_arvalid(jtag_axi_0_M_AXI_ARVALID),
        .m_axi_awaddr(jtag_axi_0_M_AXI_AWADDR),
        .m_axi_awburst(jtag_axi_0_M_AXI_AWBURST),
        .m_axi_awcache(jtag_axi_0_M_AXI_AWCACHE),
        .m_axi_awid(jtag_axi_0_M_AXI_AWID),
        .m_axi_awlen(jtag_axi_0_M_AXI_AWLEN),
        .m_axi_awlock(jtag_axi_0_M_AXI_AWLOCK),
        .m_axi_awprot(jtag_axi_0_M_AXI_AWPROT),
        .m_axi_awqos(jtag_axi_0_M_AXI_AWQOS),
        .m_axi_awready(jtag_axi_0_M_AXI_AWREADY),
        .m_axi_awsize(jtag_axi_0_M_AXI_AWSIZE),
        .m_axi_awvalid(jtag_axi_0_M_AXI_AWVALID),
        .m_axi_bid(jtag_axi_0_M_AXI_BID),
        .m_axi_bready(jtag_axi_0_M_AXI_BREADY),
        .m_axi_bresp(jtag_axi_0_M_AXI_BRESP),
        .m_axi_bvalid(jtag_axi_0_M_AXI_BVALID),
        .m_axi_rdata(jtag_axi_0_M_AXI_RDATA),
        .m_axi_rid(jtag_axi_0_M_AXI_RID),
        .m_axi_rlast(jtag_axi_0_M_AXI_RLAST),
        .m_axi_rready(jtag_axi_0_M_AXI_RREADY),
        .m_axi_rresp(jtag_axi_0_M_AXI_RRESP),
        .m_axi_rvalid(jtag_axi_0_M_AXI_RVALID),
        .m_axi_wdata(jtag_axi_0_M_AXI_WDATA),
        .m_axi_wlast(jtag_axi_0_M_AXI_WLAST),
        .m_axi_wready(jtag_axi_0_M_AXI_WREADY),
        .m_axi_wstrb(jtag_axi_0_M_AXI_WSTRB),
        .m_axi_wvalid(jtag_axi_0_M_AXI_WVALID));
  design_1_system_ila_0_0 system_ila_0
       (.SLOT_0_IIC_scl_i(axi_iic_0_IIC_SCL_I),
        .SLOT_0_IIC_scl_o(axi_iic_0_IIC_SCL_O),
        .SLOT_0_IIC_scl_t(axi_iic_0_IIC_SCL_T),
        .SLOT_0_IIC_sda_i(axi_iic_0_IIC_SDA_I),
        .SLOT_0_IIC_sda_o(axi_iic_0_IIC_SDA_O),
        .SLOT_0_IIC_sda_t(axi_iic_0_IIC_SDA_T),
        .clk(util_ds_buf_0_IBUF_OUT));
endmodule
