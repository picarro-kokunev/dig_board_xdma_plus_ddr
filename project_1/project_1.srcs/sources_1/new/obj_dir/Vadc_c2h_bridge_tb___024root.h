// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vadc_c2h_bridge_tb.h for the primary calling header

#ifndef VERILATED_VADC_C2H_BRIDGE_TB___024ROOT_H_
#define VERILATED_VADC_C2H_BRIDGE_TB___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vadc_c2h_bridge_tb__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vadc_c2h_bridge_tb___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        CData/*0:0*/ adc_c2h_bridge_tb__DOT__sample_clk;
        CData/*0:0*/ adc_c2h_bridge_tb__DOT__sample_rst_n;
        CData/*0:0*/ adc_c2h_bridge_tb__DOT__m_axis_aclk;
        CData/*0:0*/ adc_c2h_bridge_tb__DOT__m_axis_aresetn;
        CData/*0:0*/ adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__adc_clk_reg;
        CData/*0:0*/ adc_c2h_bridge_tb__DOT__adc_ofa_a;
        CData/*0:0*/ adc_c2h_bridge_tb__DOT__m_axis_tready;
        CData/*0:0*/ adc_c2h_bridge_tb__DOT__m_axis_tlast;
        CData/*0:0*/ adc_c2h_bridge_tb__DOT__u_bridge__DOT__fifo_full;
        CData/*0:0*/ adc_c2h_bridge_tb__DOT__u_bridge__DOT__fifo_rd_en;
        CData/*0:0*/ adc_c2h_bridge_tb__DOT__u_bridge__DOT__fifo_empty;
        CData/*2:0*/ adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_cnt;
        CData/*0:0*/ adc_c2h_bridge_tb__DOT__u_bridge__DOT__beat_valid;
        CData/*0:0*/ adc_c2h_bridge_tb__DOT__u_bridge__DOT__beat_consumed;
        CData/*0:0*/ __Vintraval_h4b5cce90__0;
        CData/*0:0*/ __Vintraval_h81bdc1ad__0;
        CData/*0:0*/ __Vintraval_ha72360d1__0;
        CData/*0:0*/ __Vintraval_h81bdc1ad__1;
        CData/*0:0*/ __Vdly__adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__adc_clk_reg;
        CData/*6:0*/ __VdlyDim0__adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__mem__v0;
        CData/*0:0*/ __VdlySet__adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__mem__v0;
        CData/*0:0*/ __VdlySet__adc_c2h_bridge_tb__DOT__adc_data_a__v0;
        CData/*0:0*/ __VdlySet__adc_c2h_bridge_tb__DOT__adc_data_a__v1;
        CData/*0:0*/ __VdlyVal__adc_c2h_bridge_tb__DOT__adc_ofa_a__v0;
        CData/*0:0*/ __VdlySet__adc_c2h_bridge_tb__DOT__adc_ofa_a__v0;
        CData/*0:0*/ __VdlyVal__adc_c2h_bridge_tb__DOT__adc_ofa_a__v1;
        CData/*0:0*/ __VdlySet__adc_c2h_bridge_tb__DOT__adc_ofa_a__v1;
        CData/*0:0*/ __VdlySet__adc_c2h_bridge_tb__DOT__adc_data_a__v2;
        CData/*0:0*/ __VdlySet__adc_c2h_bridge_tb__DOT__adc_data_a__v3;
        CData/*0:0*/ __VdlyVal__adc_c2h_bridge_tb__DOT__adc_ofa_a__v2;
        CData/*0:0*/ __VdlySet__adc_c2h_bridge_tb__DOT__adc_ofa_a__v2;
        CData/*0:0*/ __VdlyVal__adc_c2h_bridge_tb__DOT__adc_ofa_a__v3;
        CData/*0:0*/ __VdlySet__adc_c2h_bridge_tb__DOT__adc_ofa_a__v3;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __Vtrigprevexpr___TOP__adc_c2h_bridge_tb__DOT__m_axis_aclk__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__adc_c2h_bridge_tb__DOT__sample_clk__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__adc_c2h_bridge_tb__DOT__sample_rst_n__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__adc_c2h_bridge_tb__DOT__m_axis_aresetn__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__adc_clk_reg__0;
        CData/*0:0*/ __VactDidInit;
        CData/*0:0*/ __VactContinue;
        SData/*13:0*/ adc_c2h_bridge_tb__DOT__adc_data_a;
        SData/*15:0*/ adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__got;
        SData/*15:0*/ adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__exp;
        SData/*15:0*/ adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__data_reg;
        SData/*8:0*/ adc_c2h_bridge_tb__DOT__u_bridge__DOT__pkt_beat_cnt;
        SData/*11:0*/ adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_bin;
        SData/*11:0*/ adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_bin;
        SData/*11:0*/ adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray;
        SData/*11:0*/ adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_gray;
        SData/*11:0*/ adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_bin_next;
        SData/*11:0*/ adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray_next;
        SData/*11:0*/ adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_bin_next;
        SData/*11:0*/ adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_gray_wclk_r1;
        SData/*11:0*/ adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_gray_wclk_r2;
        SData/*11:0*/ adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray_rclk_r1;
        SData/*11:0*/ adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray_rclk_r2;
        SData/*13:0*/ __Vintraval_h7f9db57c__0;
        SData/*13:0*/ __Vintraval_h1bccb41a__0;
        SData/*13:0*/ __Vintraval_h2dd28eb9__0;
        SData/*13:0*/ __Vintraval_h1bccb41a__1;
        SData/*15:0*/ __VdlyVal__adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__mem__v0;
        SData/*13:0*/ __VdlyVal__adc_c2h_bridge_tb__DOT__adc_data_a__v0;
        SData/*13:0*/ __VdlyVal__adc_c2h_bridge_tb__DOT__adc_data_a__v1;
    };
    struct {
        SData/*13:0*/ __VdlyVal__adc_c2h_bridge_tb__DOT__adc_data_a__v2;
        SData/*13:0*/ __VdlyVal__adc_c2h_bridge_tb__DOT__adc_data_a__v3;
        IData/*31:0*/ adc_c2h_bridge_tb__DOT__error_count;
        IData/*31:0*/ adc_c2h_bridge_tb__DOT__samples_checked;
        IData/*31:0*/ adc_c2h_bridge_tb__DOT__beat_count;
        IData/*31:0*/ adc_c2h_bridge_tb__DOT__expected_beat_in_pkt;
        IData/*31:0*/ adc_c2h_bridge_tb__DOT__unnamedblk3__DOT__unnamedblk4__DOT__val_a;
        IData/*31:0*/ adc_c2h_bridge_tb__DOT__unnamedblk3__DOT__unnamedblk4__DOT__val_b;
        IData/*31:0*/ adc_c2h_bridge_tb__DOT__unnamedblk3__DOT__unnamedblk4__DOT__ofa_a_v;
        IData/*31:0*/ adc_c2h_bridge_tb__DOT__unnamedblk3__DOT__unnamedblk4__DOT__ofa_b_v;
        VlWide<4>/*127:0*/ adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_reg;
        IData/*31:0*/ __VactIterCount;
        VlUnpacked<SData/*15:0*/, 128> adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__mem;
    };
    VlQueue<CData/*0:0*/> adc_c2h_bridge_tb__DOT__u_adc_model__DOT__ofa_a;
    VlQueue<CData/*0:0*/> adc_c2h_bridge_tb__DOT__u_adc_model__DOT__ofa_b;
    VlQueue<SData/*15:0*/> adc_c2h_bridge_tb__DOT__golden_q;
    VlQueue<SData/*13:0*/> adc_c2h_bridge_tb__DOT__u_adc_model__DOT__adc_a;
    VlQueue<SData/*13:0*/> adc_c2h_bridge_tb__DOT__u_adc_model__DOT__adc_b;
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_h54500120__0;
    VlTriggerScheduler __VtrigSched_h8830d6f9__0;
    VlTriggerScheduler __VtrigSched_h05bb789a__0;
    VlTriggerScheduler __VtrigSched_h05bb795b__0;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<10> __VactTriggered;
    VlTriggerVec<10> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vadc_c2h_bridge_tb__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vadc_c2h_bridge_tb___024root(Vadc_c2h_bridge_tb__Syms* symsp, const char* v__name);
    ~Vadc_c2h_bridge_tb___024root();
    VL_UNCOPYABLE(Vadc_c2h_bridge_tb___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
