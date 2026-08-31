// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vadc_c2h_bridge_tb.h for the primary calling header

#include "Vadc_c2h_bridge_tb__pch.h"
#include "Vadc_c2h_bridge_tb__Syms.h"
#include "Vadc_c2h_bridge_tb___024root.h"

VL_INLINE_OPT VlCoroutine Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__1(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__1\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ adc_c2h_bridge_tb__DOT__timeout_cycles;
    adc_c2h_bridge_tb__DOT__timeout_cycles = 0;
    // Body
    adc_c2h_bridge_tb__DOT__timeout_cycles = 0U;
    while ((1U & (~ (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__sample_rst_n)))) {
        co_await vlSelfRef.__VtrigSched_h54500120__0.trigger(1U, 
                                                             nullptr, 
                                                             "@([changed] adc_c2h_bridge_tb.sample_rst_n)", 
                                                             "adc_c2h_bridge_tb.sv", 
                                                             202);
    }
    while ((VL_GTS_III(32, 0x200U, vlSelfRef.adc_c2h_bridge_tb__DOT__samples_checked) 
            & VL_GTS_III(32, 0x30d40U, adc_c2h_bridge_tb__DOT__timeout_cycles))) {
        co_await vlSelfRef.__VtrigSched_h8830d6f9__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge adc_c2h_bridge_tb.m_axis_aclk)", 
                                                             "adc_c2h_bridge_tb.sv", 
                                                             204);
        adc_c2h_bridge_tb__DOT__timeout_cycles = ((IData)(1U) 
                                                  + adc_c2h_bridge_tb__DOT__timeout_cycles);
    }
    if (VL_UNLIKELY(VL_GTS_III(32, 0x200U, vlSelfRef.adc_c2h_bridge_tb__DOT__samples_checked))) {
        vlSelfRef.adc_c2h_bridge_tb__DOT__error_count 
            = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__error_count);
        VL_WRITEF_NX("[%0t] %%Error: adc_c2h_bridge_tb.sv:210: Assertion failed in %Nadc_c2h_bridge_tb: Timeout: only checked %0d/512 samples\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.adc_c2h_bridge_tb__DOT__samples_checked);
        VL_STOP_MT("adc_c2h_bridge_tb.sv", 210, "");
    }
    if (VL_LIKELY((0U == vlSelfRef.adc_c2h_bridge_tb__DOT__error_count))) {
        VL_WRITEF_NX("Test complete: PASS (%0d samples, %0d beats checked)\n",0,
                     32,vlSelfRef.adc_c2h_bridge_tb__DOT__samples_checked,
                     32,vlSelfRef.adc_c2h_bridge_tb__DOT__beat_count);
    } else {
        VL_WRITEF_NX("Test complete: FAIL (%0d errors)\n[%0t] %%Fatal: adc_c2h_bridge_tb.sv:217: Assertion failed in %Nadc_c2h_bridge_tb\n",0,
                     32,vlSelfRef.adc_c2h_bridge_tb__DOT__error_count,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("adc_c2h_bridge_tb.sv", 217, "", false);
    }
    VL_FINISH_MT("adc_c2h_bridge_tb.sv", 219, "");
}

VlCoroutine Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__4____Vfork_1__1(Vadc_c2h_bridge_tb___024root* vlSelf);
VlCoroutine Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__4____Vfork_2__1(Vadc_c2h_bridge_tb___024root* vlSelf);
VlCoroutine Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__4____Vfork_3__1(Vadc_c2h_bridge_tb___024root* vlSelf);
VlCoroutine Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__4____Vfork_4__1(Vadc_c2h_bridge_tb___024root* vlSelf);

VL_INLINE_OPT VlCoroutine Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__4(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__4\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (1U) {
        co_await vlSelfRef.__VtrigSched_h05bb789a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge adc_c2h_bridge_tb.u_adc_ctrl.adc_clk_reg)", 
                                                             "adc_ad_ltc22xx.sv", 
                                                             25);
        if (VL_LIKELY(VL_LTS_III(32, 0U, vlSelfRef.adc_c2h_bridge_tb__DOT__u_adc_model__DOT__adc_a.size()))) {
            vlSelfRef.__Vintraval_h7f9db57c__0 = vlSelfRef.adc_c2h_bridge_tb__DOT__u_adc_model__DOT__adc_a.pop_front();
            Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__4____Vfork_1__1(vlSelf);
        } else {
            vlSelfRef.__Vintraval_h1bccb41a__0 = 0U;
            Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__4____Vfork_2__1(vlSelf);
            VL_WRITEF_NX("[%0t] %%Error: adc_ad_ltc22xx.sv:34: Assertion failed in %Nadc_c2h_bridge_tb.u_adc_model: adc_ad_ltc22xx error : adc_a is empty\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name());
            VL_STOP_MT("adc_ad_ltc22xx.sv", 34, "");
        }
        if (VL_LIKELY(VL_LTS_III(32, 0U, vlSelfRef.adc_c2h_bridge_tb__DOT__u_adc_model__DOT__ofa_a.size()))) {
            vlSelfRef.__Vintraval_h4b5cce90__0 = vlSelfRef.adc_c2h_bridge_tb__DOT__u_adc_model__DOT__ofa_a.pop_front();
            Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__4____Vfork_3__1(vlSelf);
        } else {
            vlSelfRef.__Vintraval_h81bdc1ad__0 = 0U;
            Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__4____Vfork_4__1(vlSelf);
            VL_WRITEF_NX("[%0t] %%Error: adc_ad_ltc22xx.sv:43: Assertion failed in %Nadc_c2h_bridge_tb.u_adc_model: adc_ad_ltc22xx error : ofa_a is empty\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name());
            VL_STOP_MT("adc_ad_ltc22xx.sv", 43, "");
        }
    }
}

VlCoroutine Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__5____Vfork_5__1(Vadc_c2h_bridge_tb___024root* vlSelf);
VlCoroutine Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__5____Vfork_6__1(Vadc_c2h_bridge_tb___024root* vlSelf);
VlCoroutine Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__5____Vfork_7__1(Vadc_c2h_bridge_tb___024root* vlSelf);
VlCoroutine Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__5____Vfork_8__1(Vadc_c2h_bridge_tb___024root* vlSelf);

VL_INLINE_OPT VlCoroutine Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__5(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__5\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (1U) {
        co_await vlSelfRef.__VtrigSched_h05bb795b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(negedge adc_c2h_bridge_tb.u_adc_ctrl.adc_clk_reg)", 
                                                             "adc_ad_ltc22xx.sv", 
                                                             46);
        if (VL_LIKELY(VL_LTS_III(32, 0U, vlSelfRef.adc_c2h_bridge_tb__DOT__u_adc_model__DOT__adc_b.size()))) {
            vlSelfRef.__Vintraval_h2dd28eb9__0 = vlSelfRef.adc_c2h_bridge_tb__DOT__u_adc_model__DOT__adc_b.pop_front();
            Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__5____Vfork_5__1(vlSelf);
        } else {
            vlSelfRef.__Vintraval_h1bccb41a__1 = 0U;
            Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__5____Vfork_6__1(vlSelf);
            VL_WRITEF_NX("[%0t] %%Error: adc_ad_ltc22xx.sv:53: Assertion failed in %Nadc_c2h_bridge_tb.u_adc_model: adc_ad_ltc22xx error : adc_b is empty\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name());
            VL_STOP_MT("adc_ad_ltc22xx.sv", 53, "");
        }
        if (VL_LIKELY(VL_LTS_III(32, 0U, vlSelfRef.adc_c2h_bridge_tb__DOT__u_adc_model__DOT__ofa_b.size()))) {
            vlSelfRef.__Vintraval_ha72360d1__0 = vlSelfRef.adc_c2h_bridge_tb__DOT__u_adc_model__DOT__ofa_b.pop_front();
            Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__5____Vfork_7__1(vlSelf);
        } else {
            vlSelfRef.__Vintraval_h81bdc1ad__1 = 0U;
            Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__5____Vfork_8__1(vlSelf);
            VL_WRITEF_NX("[%0t] %%Error: adc_ad_ltc22xx.sv:62: Assertion failed in %Nadc_c2h_bridge_tb.u_adc_model: adc_ad_ltc22xx error : ofa_b is empty\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name());
            VL_STOP_MT("adc_ad_ltc22xx.sv", 62, "");
        }
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vadc_c2h_bridge_tb___024root___dump_triggers__act(Vadc_c2h_bridge_tb___024root* vlSelf);
#endif  // VL_DEBUG

void Vadc_c2h_bridge_tb___024root___eval_triggers__act(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___eval_triggers__act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered.set(0U, ((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__m_axis_aclk) 
                                       & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__adc_c2h_bridge_tb__DOT__m_axis_aclk__0))));
    vlSelfRef.__VactTriggered.set(1U, ((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__sample_clk) 
                                       & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__adc_c2h_bridge_tb__DOT__sample_clk__0))));
    vlSelfRef.__VactTriggered.set(2U, ((~ (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__sample_clk)) 
                                       & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__adc_c2h_bridge_tb__DOT__sample_clk__0)));
    vlSelfRef.__VactTriggered.set(3U, ((~ (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__sample_rst_n)) 
                                       & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__adc_c2h_bridge_tb__DOT__sample_rst_n__0)));
    vlSelfRef.__VactTriggered.set(4U, ((~ (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__m_axis_aresetn)) 
                                       & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__adc_c2h_bridge_tb__DOT__m_axis_aresetn__0)));
    vlSelfRef.__VactTriggered.set(5U, ((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__adc_clk_reg) 
                                       ^ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__adc_clk_reg__0)));
    vlSelfRef.__VactTriggered.set(6U, ((~ (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__adc_clk_reg)) 
                                       & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__adc_clk_reg__0)));
    vlSelfRef.__VactTriggered.set(7U, vlSelfRef.__VdlySched.awaitingCurrentTime());
    vlSelfRef.__VactTriggered.set(8U, ((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__sample_rst_n) 
                                       != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__adc_c2h_bridge_tb__DOT__sample_rst_n__0)));
    vlSelfRef.__VactTriggered.set(9U, ((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__adc_clk_reg) 
                                       & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__adc_clk_reg__0))));
    vlSelfRef.__Vtrigprevexpr___TOP__adc_c2h_bridge_tb__DOT__m_axis_aclk__0 
        = vlSelfRef.adc_c2h_bridge_tb__DOT__m_axis_aclk;
    vlSelfRef.__Vtrigprevexpr___TOP__adc_c2h_bridge_tb__DOT__sample_clk__0 
        = vlSelfRef.adc_c2h_bridge_tb__DOT__sample_clk;
    vlSelfRef.__Vtrigprevexpr___TOP__adc_c2h_bridge_tb__DOT__sample_rst_n__0 
        = vlSelfRef.adc_c2h_bridge_tb__DOT__sample_rst_n;
    vlSelfRef.__Vtrigprevexpr___TOP__adc_c2h_bridge_tb__DOT__m_axis_aresetn__0 
        = vlSelfRef.adc_c2h_bridge_tb__DOT__m_axis_aresetn;
    vlSelfRef.__Vtrigprevexpr___TOP__adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__adc_clk_reg__0 
        = vlSelfRef.adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__adc_clk_reg;
    if (VL_UNLIKELY((1U & (~ (IData)(vlSelfRef.__VactDidInit))))) {
        vlSelfRef.__VactDidInit = 1U;
        vlSelfRef.__VactTriggered.set(8U, 1U);
    }
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vadc_c2h_bridge_tb___024root___dump_triggers__act(vlSelf);
    }
#endif
}

VL_INLINE_OPT void Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__0(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vdly__adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__adc_clk_reg 
        = vlSelfRef.adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__adc_clk_reg;
    vlSelfRef.__VdlySet__adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__mem__v0 = 0U;
    if (VL_UNLIKELY(((~ (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__sample_rst_n)) 
                     & (0U != (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__data_reg))))) {
        VL_WRITEF_NX("[%0t] %%Error: adc_c2h_bridge_tb.sv:194: Assertion failed in %Nadc_c2h_bridge_tb: %0t : adc_data non-zero (%x) while sample_rst_n is low\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     64,VL_TIME_UNITED_Q(1000),-9,16,
                     (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__data_reg));
        vlSelfRef.adc_c2h_bridge_tb__DOT__error_count 
            = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__error_count);
        VL_STOP_MT("adc_c2h_bridge_tb.sv", 194, "");
    }
    if (((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__sample_rst_n) 
         & (~ (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__fifo_full)))) {
        vlSelfRef.adc_c2h_bridge_tb__DOT__golden_q.push_back(vlSelfRef.adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__data_reg);
    }
    vlSelfRef.__Vdly__adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__adc_clk_reg 
        = (1U & (~ (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__adc_clk_reg)));
    if ((1U & (~ (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__fifo_full)))) {
        vlSelfRef.__VdlyVal__adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__mem__v0 
            = vlSelfRef.adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__data_reg;
        vlSelfRef.__VdlyDim0__adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__mem__v0 
            = (0x7fU & (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_bin));
        vlSelfRef.__VdlySet__adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__mem__v0 = 1U;
    }
}

VL_INLINE_OPT void Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__1(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__1\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*2:0*/ __Vdly__adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_cnt;
    __Vdly__adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_cnt = 0;
    // Body
    __Vdly__adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_cnt 
        = vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_cnt;
    if (VL_UNLIKELY(((~ (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__m_axis_aresetn)) 
                     & (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__beat_valid)))) {
        VL_WRITEF_NX("[%0t] %%Error: adc_c2h_bridge_tb.sv:97: Assertion failed in %Nadc_c2h_bridge_tb: %0t : m_axis_tvalid asserted while m_axis_aresetn is low\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     64,VL_TIME_UNITED_Q(1000),-9);
        vlSelfRef.adc_c2h_bridge_tb__DOT__error_count 
            = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__error_count);
        VL_STOP_MT("adc_c2h_bridge_tb.sv", 97, "");
    }
    if ((((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__m_axis_aresetn) 
          & (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__beat_valid)) 
         & (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__m_axis_tready))) {
        vlSelfRef.adc_c2h_bridge_tb__DOT__beat_count 
            = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__beat_count);
        vlSelfRef.adc_c2h_bridge_tb__DOT__samples_checked 
            = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__samples_checked);
        if (VL_UNLIKELY(((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__m_axis_tlast) 
                         != (7U == vlSelfRef.adc_c2h_bridge_tb__DOT__expected_beat_in_pkt)))) {
            VL_WRITEF_NX("[%0t] %%Error: adc_c2h_bridge_tb.sv:142: Assertion failed in %Nadc_c2h_bridge_tb: %0t : TLAST mismatch on beat %0d of packet (expected %0b got %0b)\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),64,VL_TIME_UNITED_Q(1000),
                         -9,32,vlSelfRef.adc_c2h_bridge_tb__DOT__expected_beat_in_pkt,
                         1,(7U == vlSelfRef.adc_c2h_bridge_tb__DOT__expected_beat_in_pkt),
                         1,(IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__m_axis_tlast));
            vlSelfRef.adc_c2h_bridge_tb__DOT__error_count 
                = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__error_count);
            VL_STOP_MT("adc_c2h_bridge_tb.sv", 142, "");
        }
        vlSelfRef.adc_c2h_bridge_tb__DOT__samples_checked 
            = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__samples_checked);
        vlSelfRef.adc_c2h_bridge_tb__DOT__expected_beat_in_pkt 
            = ((7U == vlSelfRef.adc_c2h_bridge_tb__DOT__expected_beat_in_pkt)
                ? 0U : ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__expected_beat_in_pkt));
        vlSelfRef.adc_c2h_bridge_tb__DOT__samples_checked 
            = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__samples_checked);
        vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__got 
            = (0xffffU & vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_reg[0U]);
        vlSelfRef.adc_c2h_bridge_tb__DOT__samples_checked 
            = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__samples_checked);
        if (VL_UNLIKELY((0U == vlSelfRef.adc_c2h_bridge_tb__DOT__golden_q.size()))) {
            vlSelfRef.adc_c2h_bridge_tb__DOT__error_count 
                = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__error_count);
            VL_WRITEF_NX("[%0t] %%Error: adc_c2h_bridge_tb.sv:153: Assertion failed in %Nadc_c2h_bridge_tb.unnamedblk1.unnamedblk2: %0t : golden queue underflow while checking word 0 of beat %0d\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),64,VL_TIME_UNITED_Q(1000),
                         -9,32,vlSelfRef.adc_c2h_bridge_tb__DOT__beat_count);
            VL_STOP_MT("adc_c2h_bridge_tb.sv", 153, "");
        } else {
            vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__exp 
                = vlSelfRef.adc_c2h_bridge_tb__DOT__golden_q.pop_front();
            if (VL_UNLIKELY(((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__got) 
                             != (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__exp)))) {
                vlSelfRef.adc_c2h_bridge_tb__DOT__error_count 
                    = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__error_count);
                VL_WRITEF_NX("[%0t] %%Error: adc_c2h_bridge_tb.sv:159: Assertion failed in %Nadc_c2h_bridge_tb.unnamedblk1.unnamedblk2: %0t : sample mismatch (beat %0d, word 0): expected %x got %x\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),64,
                             VL_TIME_UNITED_Q(1000),
                             -9,32,vlSelfRef.adc_c2h_bridge_tb__DOT__beat_count,
                             16,(IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__exp),
                             16,vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__got);
                VL_STOP_MT("adc_c2h_bridge_tb.sv", 159, "");
            }
        }
        vlSelfRef.adc_c2h_bridge_tb__DOT__samples_checked 
            = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__samples_checked);
        vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__got 
            = (vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_reg[0U] 
               >> 0x10U);
        vlSelfRef.adc_c2h_bridge_tb__DOT__samples_checked 
            = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__samples_checked);
        if (VL_UNLIKELY((0U == vlSelfRef.adc_c2h_bridge_tb__DOT__golden_q.size()))) {
            vlSelfRef.adc_c2h_bridge_tb__DOT__error_count 
                = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__error_count);
            VL_WRITEF_NX("[%0t] %%Error: adc_c2h_bridge_tb.sv:153: Assertion failed in %Nadc_c2h_bridge_tb.unnamedblk1.unnamedblk2: %0t : golden queue underflow while checking word 1 of beat %0d\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),64,VL_TIME_UNITED_Q(1000),
                         -9,32,vlSelfRef.adc_c2h_bridge_tb__DOT__beat_count);
            VL_STOP_MT("adc_c2h_bridge_tb.sv", 153, "");
        } else {
            vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__exp 
                = vlSelfRef.adc_c2h_bridge_tb__DOT__golden_q.pop_front();
            if (VL_UNLIKELY(((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__got) 
                             != (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__exp)))) {
                vlSelfRef.adc_c2h_bridge_tb__DOT__error_count 
                    = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__error_count);
                VL_WRITEF_NX("[%0t] %%Error: adc_c2h_bridge_tb.sv:159: Assertion failed in %Nadc_c2h_bridge_tb.unnamedblk1.unnamedblk2: %0t : sample mismatch (beat %0d, word 1): expected %x got %x\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),64,
                             VL_TIME_UNITED_Q(1000),
                             -9,32,vlSelfRef.adc_c2h_bridge_tb__DOT__beat_count,
                             16,(IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__exp),
                             16,vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__got);
                VL_STOP_MT("adc_c2h_bridge_tb.sv", 159, "");
            }
        }
        vlSelfRef.adc_c2h_bridge_tb__DOT__samples_checked 
            = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__samples_checked);
        vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__got 
            = (0xffffU & vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_reg[1U]);
        vlSelfRef.adc_c2h_bridge_tb__DOT__samples_checked 
            = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__samples_checked);
        if (VL_UNLIKELY((0U == vlSelfRef.adc_c2h_bridge_tb__DOT__golden_q.size()))) {
            vlSelfRef.adc_c2h_bridge_tb__DOT__error_count 
                = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__error_count);
            VL_WRITEF_NX("[%0t] %%Error: adc_c2h_bridge_tb.sv:153: Assertion failed in %Nadc_c2h_bridge_tb.unnamedblk1.unnamedblk2: %0t : golden queue underflow while checking word 2 of beat %0d\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),64,VL_TIME_UNITED_Q(1000),
                         -9,32,vlSelfRef.adc_c2h_bridge_tb__DOT__beat_count);
            VL_STOP_MT("adc_c2h_bridge_tb.sv", 153, "");
        } else {
            vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__exp 
                = vlSelfRef.adc_c2h_bridge_tb__DOT__golden_q.pop_front();
            if (VL_UNLIKELY(((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__got) 
                             != (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__exp)))) {
                vlSelfRef.adc_c2h_bridge_tb__DOT__error_count 
                    = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__error_count);
                VL_WRITEF_NX("[%0t] %%Error: adc_c2h_bridge_tb.sv:159: Assertion failed in %Nadc_c2h_bridge_tb.unnamedblk1.unnamedblk2: %0t : sample mismatch (beat %0d, word 2): expected %x got %x\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),64,
                             VL_TIME_UNITED_Q(1000),
                             -9,32,vlSelfRef.adc_c2h_bridge_tb__DOT__beat_count,
                             16,(IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__exp),
                             16,vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__got);
                VL_STOP_MT("adc_c2h_bridge_tb.sv", 159, "");
            }
        }
        vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__got 
            = (vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_reg[1U] 
               >> 0x10U);
        if (VL_UNLIKELY((0U == vlSelfRef.adc_c2h_bridge_tb__DOT__golden_q.size()))) {
            vlSelfRef.adc_c2h_bridge_tb__DOT__error_count 
                = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__error_count);
            VL_WRITEF_NX("[%0t] %%Error: adc_c2h_bridge_tb.sv:153: Assertion failed in %Nadc_c2h_bridge_tb.unnamedblk1.unnamedblk2: %0t : golden queue underflow while checking word 3 of beat %0d\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),64,VL_TIME_UNITED_Q(1000),
                         -9,32,vlSelfRef.adc_c2h_bridge_tb__DOT__beat_count);
            VL_STOP_MT("adc_c2h_bridge_tb.sv", 153, "");
        } else {
            vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__exp 
                = vlSelfRef.adc_c2h_bridge_tb__DOT__golden_q.pop_front();
            if (VL_UNLIKELY(((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__got) 
                             != (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__exp)))) {
                vlSelfRef.adc_c2h_bridge_tb__DOT__error_count 
                    = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__error_count);
                VL_WRITEF_NX("[%0t] %%Error: adc_c2h_bridge_tb.sv:159: Assertion failed in %Nadc_c2h_bridge_tb.unnamedblk1.unnamedblk2: %0t : sample mismatch (beat %0d, word 3): expected %x got %x\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),64,
                             VL_TIME_UNITED_Q(1000),
                             -9,32,vlSelfRef.adc_c2h_bridge_tb__DOT__beat_count,
                             16,(IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__exp),
                             16,vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__got);
                VL_STOP_MT("adc_c2h_bridge_tb.sv", 159, "");
            }
        }
        vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__got 
            = (0xffffU & vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_reg[2U]);
        if (VL_UNLIKELY((0U == vlSelfRef.adc_c2h_bridge_tb__DOT__golden_q.size()))) {
            vlSelfRef.adc_c2h_bridge_tb__DOT__error_count 
                = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__error_count);
            VL_WRITEF_NX("[%0t] %%Error: adc_c2h_bridge_tb.sv:153: Assertion failed in %Nadc_c2h_bridge_tb.unnamedblk1.unnamedblk2: %0t : golden queue underflow while checking word 4 of beat %0d\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),64,VL_TIME_UNITED_Q(1000),
                         -9,32,vlSelfRef.adc_c2h_bridge_tb__DOT__beat_count);
            VL_STOP_MT("adc_c2h_bridge_tb.sv", 153, "");
        } else {
            vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__exp 
                = vlSelfRef.adc_c2h_bridge_tb__DOT__golden_q.pop_front();
            if (VL_UNLIKELY(((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__got) 
                             != (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__exp)))) {
                vlSelfRef.adc_c2h_bridge_tb__DOT__error_count 
                    = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__error_count);
                VL_WRITEF_NX("[%0t] %%Error: adc_c2h_bridge_tb.sv:159: Assertion failed in %Nadc_c2h_bridge_tb.unnamedblk1.unnamedblk2: %0t : sample mismatch (beat %0d, word 4): expected %x got %x\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),64,
                             VL_TIME_UNITED_Q(1000),
                             -9,32,vlSelfRef.adc_c2h_bridge_tb__DOT__beat_count,
                             16,(IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__exp),
                             16,vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__got);
                VL_STOP_MT("adc_c2h_bridge_tb.sv", 159, "");
            }
        }
        vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__got 
            = (vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_reg[2U] 
               >> 0x10U);
        if (VL_UNLIKELY((0U == vlSelfRef.adc_c2h_bridge_tb__DOT__golden_q.size()))) {
            vlSelfRef.adc_c2h_bridge_tb__DOT__error_count 
                = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__error_count);
            VL_WRITEF_NX("[%0t] %%Error: adc_c2h_bridge_tb.sv:153: Assertion failed in %Nadc_c2h_bridge_tb.unnamedblk1.unnamedblk2: %0t : golden queue underflow while checking word 5 of beat %0d\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),64,VL_TIME_UNITED_Q(1000),
                         -9,32,vlSelfRef.adc_c2h_bridge_tb__DOT__beat_count);
            VL_STOP_MT("adc_c2h_bridge_tb.sv", 153, "");
        } else {
            vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__exp 
                = vlSelfRef.adc_c2h_bridge_tb__DOT__golden_q.pop_front();
            if (VL_UNLIKELY(((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__got) 
                             != (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__exp)))) {
                vlSelfRef.adc_c2h_bridge_tb__DOT__error_count 
                    = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__error_count);
                VL_WRITEF_NX("[%0t] %%Error: adc_c2h_bridge_tb.sv:159: Assertion failed in %Nadc_c2h_bridge_tb.unnamedblk1.unnamedblk2: %0t : sample mismatch (beat %0d, word 5): expected %x got %x\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),64,
                             VL_TIME_UNITED_Q(1000),
                             -9,32,vlSelfRef.adc_c2h_bridge_tb__DOT__beat_count,
                             16,(IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__exp),
                             16,vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__got);
                VL_STOP_MT("adc_c2h_bridge_tb.sv", 159, "");
            }
        }
        vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__got 
            = (0xffffU & vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_reg[3U]);
        if (VL_UNLIKELY((0U == vlSelfRef.adc_c2h_bridge_tb__DOT__golden_q.size()))) {
            vlSelfRef.adc_c2h_bridge_tb__DOT__error_count 
                = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__error_count);
            VL_WRITEF_NX("[%0t] %%Error: adc_c2h_bridge_tb.sv:153: Assertion failed in %Nadc_c2h_bridge_tb.unnamedblk1.unnamedblk2: %0t : golden queue underflow while checking word 6 of beat %0d\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),64,VL_TIME_UNITED_Q(1000),
                         -9,32,vlSelfRef.adc_c2h_bridge_tb__DOT__beat_count);
            VL_STOP_MT("adc_c2h_bridge_tb.sv", 153, "");
        } else {
            vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__exp 
                = vlSelfRef.adc_c2h_bridge_tb__DOT__golden_q.pop_front();
            if (VL_UNLIKELY(((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__got) 
                             != (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__exp)))) {
                vlSelfRef.adc_c2h_bridge_tb__DOT__error_count 
                    = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__error_count);
                VL_WRITEF_NX("[%0t] %%Error: adc_c2h_bridge_tb.sv:159: Assertion failed in %Nadc_c2h_bridge_tb.unnamedblk1.unnamedblk2: %0t : sample mismatch (beat %0d, word 6): expected %x got %x\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),64,
                             VL_TIME_UNITED_Q(1000),
                             -9,32,vlSelfRef.adc_c2h_bridge_tb__DOT__beat_count,
                             16,(IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__exp),
                             16,vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__got);
                VL_STOP_MT("adc_c2h_bridge_tb.sv", 159, "");
            }
        }
        vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__got 
            = (vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_reg[3U] 
               >> 0x10U);
        if (VL_UNLIKELY((0U == vlSelfRef.adc_c2h_bridge_tb__DOT__golden_q.size()))) {
            vlSelfRef.adc_c2h_bridge_tb__DOT__error_count 
                = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__error_count);
            VL_WRITEF_NX("[%0t] %%Error: adc_c2h_bridge_tb.sv:153: Assertion failed in %Nadc_c2h_bridge_tb.unnamedblk1.unnamedblk2: %0t : golden queue underflow while checking word 7 of beat %0d\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),64,VL_TIME_UNITED_Q(1000),
                         -9,32,vlSelfRef.adc_c2h_bridge_tb__DOT__beat_count);
            VL_STOP_MT("adc_c2h_bridge_tb.sv", 153, "");
        } else {
            vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__exp 
                = vlSelfRef.adc_c2h_bridge_tb__DOT__golden_q.pop_front();
            if (VL_UNLIKELY(((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__got) 
                             != (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__exp)))) {
                vlSelfRef.adc_c2h_bridge_tb__DOT__error_count 
                    = ((IData)(1U) + vlSelfRef.adc_c2h_bridge_tb__DOT__error_count);
                VL_WRITEF_NX("[%0t] %%Error: adc_c2h_bridge_tb.sv:159: Assertion failed in %Nadc_c2h_bridge_tb.unnamedblk1.unnamedblk2: %0t : sample mismatch (beat %0d, word 7): expected %x got %x\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),64,
                             VL_TIME_UNITED_Q(1000),
                             -9,32,vlSelfRef.adc_c2h_bridge_tb__DOT__beat_count,
                             16,(IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__exp),
                             16,vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__got);
                VL_STOP_MT("adc_c2h_bridge_tb.sv", 159, "");
            }
        }
    }
    if (vlSelfRef.adc_c2h_bridge_tb__DOT__m_axis_aresetn) {
        if (vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__beat_consumed) {
            vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__pkt_beat_cnt 
                = ((7U == (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__pkt_beat_cnt))
                    ? 0U : (0x1ffU & ((IData)(1U) + (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__pkt_beat_cnt))));
        }
    } else {
        vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__pkt_beat_cnt = 0U;
    }
    if (vlSelfRef.adc_c2h_bridge_tb__DOT__m_axis_aresetn) {
        vlSelfRef.adc_c2h_bridge_tb__DOT__m_axis_tready 
            = (0x46U > VL_URANDOM_RANGE_I(0x63U, 0U));
    } else {
        vlSelfRef.adc_c2h_bridge_tb__DOT__m_axis_tready = 0U;
    }
    if (vlSelfRef.adc_c2h_bridge_tb__DOT__m_axis_aresetn) {
        if (vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__beat_consumed) {
            vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__beat_valid = 0U;
        }
        if (vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__fifo_rd_en) {
            VL_ASSIGNSEL_WI(128,16,(0x7fU & VL_SHIFTL_III(7,32,32, (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_cnt), 4U)), vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_reg, 
                            vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__mem
                            [(0x7fU & (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_bin))]);
            if ((7U == (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_cnt))) {
                __Vdly__adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_cnt = 0U;
                vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__beat_valid = 1U;
            } else {
                __Vdly__adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_cnt 
                    = (7U & ((IData)(1U) + (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_cnt)));
            }
        }
    } else {
        __Vdly__adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_cnt = 0U;
        vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_reg[0U] = 0U;
        vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_reg[1U] = 0U;
        vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_reg[2U] = 0U;
        vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_reg[3U] = 0U;
        vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__beat_valid = 0U;
    }
    vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_cnt 
        = __Vdly__adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_cnt;
    vlSelfRef.adc_c2h_bridge_tb__DOT__m_axis_tlast 
        = ((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__beat_valid) 
           & (7U == (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__pkt_beat_cnt)));
    vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__beat_consumed 
        = ((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__m_axis_tready) 
           & (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__beat_valid));
}
