// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vadc_ad_ltc22xx.h for the primary calling header

#include "Vadc_ad_ltc22xx__pch.h"
#include "Vadc_ad_ltc22xx___024root.h"

VL_ATTR_COLD void Vadc_ad_ltc22xx___024root___eval_static__TOP(Vadc_ad_ltc22xx___024root* vlSelf);

VL_ATTR_COLD void Vadc_ad_ltc22xx___024root___eval_static(Vadc_ad_ltc22xx___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_ad_ltc22xx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_ad_ltc22xx___024root___eval_static\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vadc_ad_ltc22xx___024root___eval_static__TOP(vlSelf);
}

VL_ATTR_COLD void Vadc_ad_ltc22xx___024root___eval_static__TOP(Vadc_ad_ltc22xx___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_ad_ltc22xx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_ad_ltc22xx___024root___eval_static__TOP\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.adc_c2h_bridge_tb__DOT__sample_clk = 0U;
    vlSelfRef.adc_c2h_bridge_tb__DOT__sample_rst_n = 0U;
    vlSelfRef.adc_c2h_bridge_tb__DOT__m_axis_aclk = 0U;
    vlSelfRef.adc_c2h_bridge_tb__DOT__m_axis_aresetn = 0U;
    vlSelfRef.adc_c2h_bridge_tb__DOT__error_count = 0U;
    vlSelfRef.adc_c2h_bridge_tb__DOT__samples_checked = 0U;
    vlSelfRef.adc_c2h_bridge_tb__DOT__beat_count = 0U;
    vlSelfRef.adc_c2h_bridge_tb__DOT__expected_beat_in_pkt = 0U;
}

VL_ATTR_COLD void Vadc_ad_ltc22xx___024root___eval_initial__TOP(Vadc_ad_ltc22xx___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_ad_ltc22xx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_ad_ltc22xx___024root___eval_initial__TOP\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__adc_clk_reg = 0U;
}

VL_ATTR_COLD void Vadc_ad_ltc22xx___024root___eval_final(Vadc_ad_ltc22xx___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_ad_ltc22xx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_ad_ltc22xx___024root___eval_final\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vadc_ad_ltc22xx___024root___dump_triggers__stl(Vadc_ad_ltc22xx___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vadc_ad_ltc22xx___024root___eval_phase__stl(Vadc_ad_ltc22xx___024root* vlSelf);

VL_ATTR_COLD void Vadc_ad_ltc22xx___024root___eval_settle(Vadc_ad_ltc22xx___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_ad_ltc22xx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_ad_ltc22xx___024root___eval_settle\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY((0x64U < __VstlIterCount))) {
#ifdef VL_DEBUG
            Vadc_ad_ltc22xx___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("adc_c2h_bridge_tb.sv", 15, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vadc_ad_ltc22xx___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelfRef.__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vadc_ad_ltc22xx___024root___dump_triggers__stl(Vadc_ad_ltc22xx___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_ad_ltc22xx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_ad_ltc22xx___024root___dump_triggers__stl\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VstlTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vadc_ad_ltc22xx___024root___stl_sequent__TOP__0(Vadc_ad_ltc22xx___024root* vlSelf);

VL_ATTR_COLD void Vadc_ad_ltc22xx___024root___eval_stl(Vadc_ad_ltc22xx___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_ad_ltc22xx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_ad_ltc22xx___024root___eval_stl\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vadc_ad_ltc22xx___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD void Vadc_ad_ltc22xx___024root___stl_sequent__TOP__0(Vadc_ad_ltc22xx___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_ad_ltc22xx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_ad_ltc22xx___024root___stl_sequent__TOP__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*7:0*/ adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray_plus1;
    adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray_plus1 = 0;
    // Body
    vlSelfRef.adc_c2h_bridge_tb__DOT__m_axis_tlast 
        = ((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__beat_valid) 
           & (7U == (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__pkt_beat_cnt)));
    vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__beat_consumed 
        = ((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__m_axis_tready) 
           & (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__beat_valid));
    vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__fifo_empty 
        = ((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_gray) 
           == (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray_rclk_r2));
    adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray_plus1 
        = (0xffU & (((IData)(1U) + (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_bin)) 
                    ^ VL_SHIFTR_III(8,8,32, (0xffU 
                                             & ((IData)(1U) 
                                                + (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_bin))), 1U)));
    vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__fifo_rd_en 
        = (1U & ((~ (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__fifo_empty)) 
                 & ((~ (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__beat_valid)) 
                    | (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__beat_consumed))));
    vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__fifo_full 
        = ((IData)(adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray_plus1) 
           == ((0xc0U & ((~ ((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_gray_wclk_r2) 
                             >> 6U)) << 6U)) | (0x3fU 
                                                & (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_gray_wclk_r2))));
    vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_bin_next 
        = (0xffU & ((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_bin) 
                    + ((~ (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__fifo_empty)) 
                       & (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__fifo_rd_en))));
    vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_bin_next 
        = (0xffU & ((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_bin) 
                    + (1U & (~ (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__fifo_full)))));
    vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray_next 
        = ((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__fifo_full)
            ? (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray)
            : (IData)(adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray_plus1));
}

VL_ATTR_COLD void Vadc_ad_ltc22xx___024root___eval_triggers__stl(Vadc_ad_ltc22xx___024root* vlSelf);

VL_ATTR_COLD bool Vadc_ad_ltc22xx___024root___eval_phase__stl(Vadc_ad_ltc22xx___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_ad_ltc22xx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_ad_ltc22xx___024root___eval_phase__stl\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vadc_ad_ltc22xx___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelfRef.__VstlTriggered.any();
    if (__VstlExecute) {
        Vadc_ad_ltc22xx___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vadc_ad_ltc22xx___024root___dump_triggers__act(Vadc_ad_ltc22xx___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_ad_ltc22xx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_ad_ltc22xx___024root___dump_triggers__act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge adc_c2h_bridge_tb.m_axis_aclk)\n");
    }
    if ((2ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @(posedge adc_c2h_bridge_tb.sample_clk)\n");
    }
    if ((4ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 2 is active: @(negedge adc_c2h_bridge_tb.sample_clk)\n");
    }
    if ((8ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 3 is active: @(negedge adc_c2h_bridge_tb.sample_rst_n)\n");
    }
    if ((0x10ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 4 is active: @(negedge adc_c2h_bridge_tb.m_axis_aresetn)\n");
    }
    if ((0x20ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 5 is active: @(edge adc_c2h_bridge_tb.u_adc_ctrl.adc_clk_reg)\n");
    }
    if ((0x40ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 6 is active: @(negedge adc_c2h_bridge_tb.u_adc_ctrl.adc_clk_reg)\n");
    }
    if ((0x80ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 7 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
    if ((0x100ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 8 is active: @([changed] adc_c2h_bridge_tb.sample_rst_n)\n");
    }
    if ((0x200ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 9 is active: @(posedge adc_c2h_bridge_tb.u_adc_ctrl.adc_clk_reg)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vadc_ad_ltc22xx___024root___dump_triggers__nba(Vadc_ad_ltc22xx___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_ad_ltc22xx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_ad_ltc22xx___024root___dump_triggers__nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge adc_c2h_bridge_tb.m_axis_aclk)\n");
    }
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @(posedge adc_c2h_bridge_tb.sample_clk)\n");
    }
    if ((4ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 2 is active: @(negedge adc_c2h_bridge_tb.sample_clk)\n");
    }
    if ((8ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 3 is active: @(negedge adc_c2h_bridge_tb.sample_rst_n)\n");
    }
    if ((0x10ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 4 is active: @(negedge adc_c2h_bridge_tb.m_axis_aresetn)\n");
    }
    if ((0x20ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 5 is active: @(edge adc_c2h_bridge_tb.u_adc_ctrl.adc_clk_reg)\n");
    }
    if ((0x40ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 6 is active: @(negedge adc_c2h_bridge_tb.u_adc_ctrl.adc_clk_reg)\n");
    }
    if ((0x80ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 7 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
    if ((0x100ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 8 is active: @([changed] adc_c2h_bridge_tb.sample_rst_n)\n");
    }
    if ((0x200ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 9 is active: @(posedge adc_c2h_bridge_tb.u_adc_ctrl.adc_clk_reg)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vadc_ad_ltc22xx___024root___ctor_var_reset(Vadc_ad_ltc22xx___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_ad_ltc22xx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_ad_ltc22xx___024root___ctor_var_reset\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->adc_c2h_bridge_tb__DOT__sample_clk = VL_RAND_RESET_I(1);
    vlSelf->adc_c2h_bridge_tb__DOT__sample_rst_n = VL_RAND_RESET_I(1);
    vlSelf->adc_c2h_bridge_tb__DOT__m_axis_aclk = VL_RAND_RESET_I(1);
    vlSelf->adc_c2h_bridge_tb__DOT__m_axis_aresetn = VL_RAND_RESET_I(1);
    vlSelf->adc_c2h_bridge_tb__DOT__adc_data_a = VL_RAND_RESET_I(14);
    vlSelf->adc_c2h_bridge_tb__DOT__adc_ofa_a = VL_RAND_RESET_I(1);
    vlSelf->adc_c2h_bridge_tb__DOT__m_axis_tready = VL_RAND_RESET_I(1);
    vlSelf->adc_c2h_bridge_tb__DOT__m_axis_tlast = VL_RAND_RESET_I(1);
    vlSelf->adc_c2h_bridge_tb__DOT__error_count = 0;
    vlSelf->adc_c2h_bridge_tb__DOT__golden_q.atDefault() = VL_RAND_RESET_I(16);
    vlSelf->adc_c2h_bridge_tb__DOT__samples_checked = 0;
    vlSelf->adc_c2h_bridge_tb__DOT__beat_count = 0;
    vlSelf->adc_c2h_bridge_tb__DOT__expected_beat_in_pkt = 0;
    vlSelf->adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__got = VL_RAND_RESET_I(16);
    vlSelf->adc_c2h_bridge_tb__DOT__unnamedblk1__DOT__unnamedblk2__DOT__exp = VL_RAND_RESET_I(16);
    vlSelf->adc_c2h_bridge_tb__DOT__unnamedblk3__DOT__unnamedblk4__DOT__val_a = 0;
    vlSelf->adc_c2h_bridge_tb__DOT__unnamedblk3__DOT__unnamedblk4__DOT__val_b = 0;
    vlSelf->adc_c2h_bridge_tb__DOT__unnamedblk3__DOT__unnamedblk4__DOT__ofa_a_v = 0;
    vlSelf->adc_c2h_bridge_tb__DOT__unnamedblk3__DOT__unnamedblk4__DOT__ofa_b_v = 0;
    vlSelf->adc_c2h_bridge_tb__DOT__u_adc_model__DOT__adc_a.atDefault() = VL_RAND_RESET_I(14);
    vlSelf->adc_c2h_bridge_tb__DOT__u_adc_model__DOT__adc_b.atDefault() = VL_RAND_RESET_I(14);
    vlSelf->adc_c2h_bridge_tb__DOT__u_adc_model__DOT__ofa_a.atDefault() = VL_RAND_RESET_I(1);
    vlSelf->adc_c2h_bridge_tb__DOT__u_adc_model__DOT__ofa_b.atDefault() = VL_RAND_RESET_I(1);
    vlSelf->adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__data_reg = VL_RAND_RESET_I(16);
    vlSelf->adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__adc_clk_reg = VL_RAND_RESET_I(1);
    vlSelf->adc_c2h_bridge_tb__DOT__u_bridge__DOT__fifo_full = VL_RAND_RESET_I(1);
    vlSelf->adc_c2h_bridge_tb__DOT__u_bridge__DOT__fifo_rd_en = VL_RAND_RESET_I(1);
    vlSelf->adc_c2h_bridge_tb__DOT__u_bridge__DOT__fifo_empty = VL_RAND_RESET_I(1);
    vlSelf->adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_cnt = VL_RAND_RESET_I(3);
    VL_RAND_RESET_W(128, vlSelf->adc_c2h_bridge_tb__DOT__u_bridge__DOT__pack_reg);
    vlSelf->adc_c2h_bridge_tb__DOT__u_bridge__DOT__beat_valid = VL_RAND_RESET_I(1);
    vlSelf->adc_c2h_bridge_tb__DOT__u_bridge__DOT__beat_consumed = VL_RAND_RESET_I(1);
    vlSelf->adc_c2h_bridge_tb__DOT__u_bridge__DOT__pkt_beat_cnt = VL_RAND_RESET_I(3);
    for (int __Vi0 = 0; __Vi0 < 128; ++__Vi0) {
        vlSelf->adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__mem[__Vi0] = VL_RAND_RESET_I(16);
    }
    vlSelf->adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_bin = VL_RAND_RESET_I(8);
    vlSelf->adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_bin = VL_RAND_RESET_I(8);
    vlSelf->adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray = VL_RAND_RESET_I(8);
    vlSelf->adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_gray = VL_RAND_RESET_I(8);
    vlSelf->adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_bin_next = VL_RAND_RESET_I(8);
    vlSelf->adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray_next = VL_RAND_RESET_I(8);
    vlSelf->adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_bin_next = VL_RAND_RESET_I(8);
    vlSelf->adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_gray_wclk_r1 = VL_RAND_RESET_I(8);
    vlSelf->adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_gray_wclk_r2 = VL_RAND_RESET_I(8);
    vlSelf->adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray_rclk_r1 = VL_RAND_RESET_I(8);
    vlSelf->adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray_rclk_r2 = VL_RAND_RESET_I(8);
    vlSelf->__Vintraval_h7f9db57c__0 = VL_RAND_RESET_I(14);
    vlSelf->__Vintraval_h1bccb41a__0 = VL_RAND_RESET_I(14);
    vlSelf->__Vintraval_h4b5cce90__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vintraval_h81bdc1ad__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vintraval_h2dd28eb9__0 = VL_RAND_RESET_I(14);
    vlSelf->__Vintraval_h1bccb41a__1 = VL_RAND_RESET_I(14);
    vlSelf->__Vintraval_ha72360d1__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vintraval_h81bdc1ad__1 = VL_RAND_RESET_I(1);
    vlSelf->__Vdly__adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__adc_clk_reg = VL_RAND_RESET_I(1);
    vlSelf->__VdlyVal__adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__mem__v0 = VL_RAND_RESET_I(16);
    vlSelf->__VdlyDim0__adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__mem__v0 = VL_RAND_RESET_I(7);
    vlSelf->__VdlySet__adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__mem__v0 = 0;
    vlSelf->__VdlyVal__adc_c2h_bridge_tb__DOT__adc_data_a__v0 = VL_RAND_RESET_I(14);
    vlSelf->__VdlySet__adc_c2h_bridge_tb__DOT__adc_data_a__v0 = 0;
    vlSelf->__VdlyVal__adc_c2h_bridge_tb__DOT__adc_data_a__v1 = VL_RAND_RESET_I(14);
    vlSelf->__VdlySet__adc_c2h_bridge_tb__DOT__adc_data_a__v1 = 0;
    vlSelf->__VdlyVal__adc_c2h_bridge_tb__DOT__adc_ofa_a__v0 = VL_RAND_RESET_I(1);
    vlSelf->__VdlySet__adc_c2h_bridge_tb__DOT__adc_ofa_a__v0 = 0;
    vlSelf->__VdlyVal__adc_c2h_bridge_tb__DOT__adc_ofa_a__v1 = VL_RAND_RESET_I(1);
    vlSelf->__VdlySet__adc_c2h_bridge_tb__DOT__adc_ofa_a__v1 = 0;
    vlSelf->__VdlyVal__adc_c2h_bridge_tb__DOT__adc_data_a__v2 = VL_RAND_RESET_I(14);
    vlSelf->__VdlySet__adc_c2h_bridge_tb__DOT__adc_data_a__v2 = 0;
    vlSelf->__VdlyVal__adc_c2h_bridge_tb__DOT__adc_data_a__v3 = VL_RAND_RESET_I(14);
    vlSelf->__VdlySet__adc_c2h_bridge_tb__DOT__adc_data_a__v3 = 0;
    vlSelf->__VdlyVal__adc_c2h_bridge_tb__DOT__adc_ofa_a__v2 = VL_RAND_RESET_I(1);
    vlSelf->__VdlySet__adc_c2h_bridge_tb__DOT__adc_ofa_a__v2 = 0;
    vlSelf->__VdlyVal__adc_c2h_bridge_tb__DOT__adc_ofa_a__v3 = VL_RAND_RESET_I(1);
    vlSelf->__VdlySet__adc_c2h_bridge_tb__DOT__adc_ofa_a__v3 = 0;
    vlSelf->__Vtrigprevexpr___TOP__adc_c2h_bridge_tb__DOT__m_axis_aclk__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr___TOP__adc_c2h_bridge_tb__DOT__sample_clk__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr___TOP__adc_c2h_bridge_tb__DOT__sample_rst_n__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr___TOP__adc_c2h_bridge_tb__DOT__m_axis_aresetn__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr___TOP__adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__adc_clk_reg__0 = VL_RAND_RESET_I(1);
    vlSelf->__VactDidInit = 0;
}
