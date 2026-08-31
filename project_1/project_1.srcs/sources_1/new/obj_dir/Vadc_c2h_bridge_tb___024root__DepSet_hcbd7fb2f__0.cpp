// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vadc_c2h_bridge_tb.h for the primary calling header

#include "Vadc_c2h_bridge_tb__pch.h"
#include "Vadc_c2h_bridge_tb___024root.h"

VL_ATTR_COLD void Vadc_c2h_bridge_tb___024root___eval_initial__TOP(Vadc_c2h_bridge_tb___024root* vlSelf);
VlCoroutine Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__0(Vadc_c2h_bridge_tb___024root* vlSelf);
VlCoroutine Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__1(Vadc_c2h_bridge_tb___024root* vlSelf);
VlCoroutine Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__2(Vadc_c2h_bridge_tb___024root* vlSelf);
VlCoroutine Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__3(Vadc_c2h_bridge_tb___024root* vlSelf);
VlCoroutine Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__4(Vadc_c2h_bridge_tb___024root* vlSelf);
VlCoroutine Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__5(Vadc_c2h_bridge_tb___024root* vlSelf);

void Vadc_c2h_bridge_tb___024root___eval_initial(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___eval_initial\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vadc_c2h_bridge_tb___024root___eval_initial__TOP(vlSelf);
    Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__1(vlSelf);
    Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__2(vlSelf);
    Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__3(vlSelf);
    Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__4(vlSelf);
    Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__5(vlSelf);
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
}

VL_INLINE_OPT VlCoroutine Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__0(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ adc_c2h_bridge_tb__DOT__unnamedblk3__DOT__i;
    adc_c2h_bridge_tb__DOT__unnamedblk3__DOT__i = 0;
    // Body
    adc_c2h_bridge_tb__DOT__unnamedblk3__DOT__i = 0U;
    while (VL_GTS_III(32, 0x190U, adc_c2h_bridge_tb__DOT__unnamedblk3__DOT__i)) {
        vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk3__DOT__unnamedblk4__DOT__val_a 
            = VL_URANDOM_RANGE_I(0x3fffU, 0U);
        vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk3__DOT__unnamedblk4__DOT__val_b 
            = VL_URANDOM_RANGE_I(0x3fffU, 0U);
        vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk3__DOT__unnamedblk4__DOT__ofa_a_v 
            = VL_URANDOM_RANGE_I(1U, 0U);
        vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk3__DOT__unnamedblk4__DOT__ofa_b_v 
            = VL_URANDOM_RANGE_I(1U, 0U);
        vlSelfRef.adc_c2h_bridge_tb__DOT__u_adc_model__DOT__adc_a.push_back(
                                                                            (0x3fffU 
                                                                             & vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk3__DOT__unnamedblk4__DOT__val_a));
        vlSelfRef.adc_c2h_bridge_tb__DOT__u_adc_model__DOT__adc_b.push_back(
                                                                            (0x3fffU 
                                                                             & vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk3__DOT__unnamedblk4__DOT__val_b));
        vlSelfRef.adc_c2h_bridge_tb__DOT__u_adc_model__DOT__ofa_a.push_back(
                                                                            (1U 
                                                                             & vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk3__DOT__unnamedblk4__DOT__ofa_a_v));
        vlSelfRef.adc_c2h_bridge_tb__DOT__u_adc_model__DOT__ofa_b.push_back(
                                                                            (1U 
                                                                             & vlSelfRef.adc_c2h_bridge_tb__DOT__unnamedblk3__DOT__unnamedblk4__DOT__ofa_b_v));
        adc_c2h_bridge_tb__DOT__unnamedblk3__DOT__i 
            = ((IData)(1U) + adc_c2h_bridge_tb__DOT__unnamedblk3__DOT__i);
    }
    co_await vlSelfRef.__VdlySched.delay(0x61a8ULL, 
                                         nullptr, "adc_c2h_bridge_tb.sv", 
                                         184);
    vlSelfRef.adc_c2h_bridge_tb__DOT__sample_rst_n = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x4268ULL, 
                                         nullptr, "adc_c2h_bridge_tb.sv", 
                                         185);
    vlSelfRef.adc_c2h_bridge_tb__DOT__m_axis_aresetn = 1U;
}

VL_INLINE_OPT VlCoroutine Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__2(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__2\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (1U) {
        co_await vlSelfRef.__VdlySched.delay(0xfa0ULL, 
                                             nullptr, 
                                             "adc_c2h_bridge_tb.sv", 
                                             41);
        vlSelfRef.adc_c2h_bridge_tb__DOT__m_axis_aclk 
            = (1U & (~ (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__m_axis_aclk)));
    }
}

VL_INLINE_OPT VlCoroutine Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__3(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__3\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (1U) {
        co_await vlSelfRef.__VdlySched.delay(0x2710ULL, 
                                             nullptr, 
                                             "adc_c2h_bridge_tb.sv", 
                                             36);
        vlSelfRef.adc_c2h_bridge_tb__DOT__sample_clk 
            = (1U & (~ (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__sample_clk)));
    }
}

VL_INLINE_OPT VlCoroutine Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__4____Vfork_4__1(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__4____Vfork_4__1\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    co_await vlSelfRef.__VdlySched.delay(0xa8cULL, 
                                         nullptr, "adc_ad_ltc22xx.sv", 
                                         42);
    vlSelfRef.__VdlyVal__adc_c2h_bridge_tb__DOT__adc_ofa_a__v1 
        = vlSelfRef.__Vintraval_h81bdc1ad__0;
    vlSelfRef.__VdlySet__adc_c2h_bridge_tb__DOT__adc_ofa_a__v1 = 1U;
}

VL_INLINE_OPT VlCoroutine Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__4____Vfork_3__1(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__4____Vfork_3__1\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    co_await vlSelfRef.__VdlySched.delay(0xa8cULL, 
                                         nullptr, "adc_ad_ltc22xx.sv", 
                                         38);
    vlSelfRef.__VdlyVal__adc_c2h_bridge_tb__DOT__adc_ofa_a__v0 
        = vlSelfRef.__Vintraval_h4b5cce90__0;
    vlSelfRef.__VdlySet__adc_c2h_bridge_tb__DOT__adc_ofa_a__v0 = 1U;
}

VL_INLINE_OPT VlCoroutine Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__4____Vfork_2__1(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__4____Vfork_2__1\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    co_await vlSelfRef.__VdlySched.delay(0xa8cULL, 
                                         nullptr, "adc_ad_ltc22xx.sv", 
                                         33);
    vlSelfRef.__VdlyVal__adc_c2h_bridge_tb__DOT__adc_data_a__v1 
        = vlSelfRef.__Vintraval_h1bccb41a__0;
    vlSelfRef.__VdlySet__adc_c2h_bridge_tb__DOT__adc_data_a__v1 = 1U;
}

VL_INLINE_OPT VlCoroutine Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__4____Vfork_1__1(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__4____Vfork_1__1\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    co_await vlSelfRef.__VdlySched.delay(0xa8cULL, 
                                         nullptr, "adc_ad_ltc22xx.sv", 
                                         29);
    vlSelfRef.__VdlyVal__adc_c2h_bridge_tb__DOT__adc_data_a__v0 
        = vlSelfRef.__Vintraval_h7f9db57c__0;
    vlSelfRef.__VdlySet__adc_c2h_bridge_tb__DOT__adc_data_a__v0 = 1U;
}

VL_INLINE_OPT VlCoroutine Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__5____Vfork_8__1(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__5____Vfork_8__1\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    co_await vlSelfRef.__VdlySched.delay(0xa8cULL, 
                                         nullptr, "adc_ad_ltc22xx.sv", 
                                         61);
    vlSelfRef.__VdlyVal__adc_c2h_bridge_tb__DOT__adc_ofa_a__v3 
        = vlSelfRef.__Vintraval_h81bdc1ad__1;
    vlSelfRef.__VdlySet__adc_c2h_bridge_tb__DOT__adc_ofa_a__v3 = 1U;
}

VL_INLINE_OPT VlCoroutine Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__5____Vfork_7__1(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__5____Vfork_7__1\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    co_await vlSelfRef.__VdlySched.delay(0xa8cULL, 
                                         nullptr, "adc_ad_ltc22xx.sv", 
                                         57);
    vlSelfRef.__VdlyVal__adc_c2h_bridge_tb__DOT__adc_ofa_a__v2 
        = vlSelfRef.__Vintraval_ha72360d1__0;
    vlSelfRef.__VdlySet__adc_c2h_bridge_tb__DOT__adc_ofa_a__v2 = 1U;
}

VL_INLINE_OPT VlCoroutine Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__5____Vfork_6__1(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__5____Vfork_6__1\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    co_await vlSelfRef.__VdlySched.delay(0xa8cULL, 
                                         nullptr, "adc_ad_ltc22xx.sv", 
                                         52);
    vlSelfRef.__VdlyVal__adc_c2h_bridge_tb__DOT__adc_data_a__v3 
        = vlSelfRef.__Vintraval_h1bccb41a__1;
    vlSelfRef.__VdlySet__adc_c2h_bridge_tb__DOT__adc_data_a__v3 = 1U;
}

VL_INLINE_OPT VlCoroutine Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__5____Vfork_5__1(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___eval_initial__TOP__Vtiming__5____Vfork_5__1\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    co_await vlSelfRef.__VdlySched.delay(0xa8cULL, 
                                         nullptr, "adc_ad_ltc22xx.sv", 
                                         49);
    vlSelfRef.__VdlyVal__adc_c2h_bridge_tb__DOT__adc_data_a__v2 
        = vlSelfRef.__Vintraval_h2dd28eb9__0;
    vlSelfRef.__VdlySet__adc_c2h_bridge_tb__DOT__adc_data_a__v2 = 1U;
}

void Vadc_c2h_bridge_tb___024root___eval_act(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___eval_act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__0(Vadc_c2h_bridge_tb___024root* vlSelf);
void Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__1(Vadc_c2h_bridge_tb___024root* vlSelf);
void Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__2(Vadc_c2h_bridge_tb___024root* vlSelf);
void Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__3(Vadc_c2h_bridge_tb___024root* vlSelf);
void Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__4(Vadc_c2h_bridge_tb___024root* vlSelf);
void Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__5(Vadc_c2h_bridge_tb___024root* vlSelf);
void Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__6(Vadc_c2h_bridge_tb___024root* vlSelf);
void Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__7(Vadc_c2h_bridge_tb___024root* vlSelf);
void Vadc_c2h_bridge_tb___024root___nba_comb__TOP__0(Vadc_c2h_bridge_tb___024root* vlSelf);

void Vadc_c2h_bridge_tb___024root___eval_nba(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___eval_nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__0(vlSelf);
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__1(vlSelf);
    }
    if ((0x11ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__2(vlSelf);
    }
    if ((0xaULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__3(vlSelf);
    }
    if ((0xcULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__4(vlSelf);
    }
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__5(vlSelf);
    }
    if ((0x11ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__6(vlSelf);
    }
    if ((0xe0ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__7(vlSelf);
    }
    if ((0x11ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vadc_c2h_bridge_tb___024root___nba_comb__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__2(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__2\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.adc_c2h_bridge_tb__DOT__m_axis_aresetn) {
        vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray_rclk_r2 
            = vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray_rclk_r1;
        vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_bin 
            = vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_bin_next;
        vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray_rclk_r1 
            = vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray;
    } else {
        vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray_rclk_r2 = 0U;
        vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_bin = 0U;
        vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray_rclk_r1 = 0U;
    }
}

VL_INLINE_OPT void Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__3(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__3\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    SData/*11:0*/ adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray_plus1;
    adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray_plus1 = 0;
    // Body
    if (vlSelfRef.adc_c2h_bridge_tb__DOT__sample_rst_n) {
        vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_gray_wclk_r2 
            = vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_gray_wclk_r1;
        vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_bin 
            = vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_bin_next;
        vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray 
            = vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray_next;
        vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_gray_wclk_r1 
            = vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_gray;
    } else {
        vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_gray_wclk_r2 = 0U;
        vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_bin = 0U;
        vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray = 0U;
        vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_gray_wclk_r1 = 0U;
    }
    adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray_plus1 
        = (0xfffU & (((IData)(1U) + (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_bin)) 
                     ^ VL_SHIFTR_III(12,12,32, (0xfffU 
                                                & ((IData)(1U) 
                                                   + (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_bin))), 1U)));
    vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__fifo_full 
        = ((IData)(adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray_plus1) 
           == ((0xc00U & ((~ ((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_gray_wclk_r2) 
                              >> 0xaU)) << 0xaU)) | 
               (0x3ffU & (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_gray_wclk_r2))));
    vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_bin_next 
        = (0xfffU & ((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_bin) 
                     + (1U & (~ (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__fifo_full)))));
    vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray_next 
        = ((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__fifo_full)
            ? (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray)
            : (IData)(adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray_plus1));
}

VL_INLINE_OPT void Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__4(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__4\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__data_reg 
        = ((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__sample_rst_n)
            ? ((0x8000U & ((~ (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__adc_clk_reg)) 
                           << 0xfU)) | (((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__adc_ofa_a) 
                                         << 0xeU) | (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__adc_data_a)))
            : 0U);
}

VL_INLINE_OPT void Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__5(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__5\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.__VdlySet__adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__mem__v0) {
        vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__mem[vlSelfRef.__VdlyDim0__adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__mem__v0] 
            = vlSelfRef.__VdlyVal__adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__mem__v0;
    }
    vlSelfRef.adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__adc_clk_reg 
        = vlSelfRef.__Vdly__adc_c2h_bridge_tb__DOT__u_adc_ctrl__DOT__adc_clk_reg;
}

VL_INLINE_OPT void Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__6(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__6\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_gray 
        = ((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__m_axis_aresetn)
            ? (0xfffU & ((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_bin_next) 
                         ^ VL_SHIFTR_III(12,12,32, (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_bin_next), 1U)))
            : 0U);
    vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__fifo_empty 
        = ((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_gray) 
           == (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__wr_ptr_gray_rclk_r2));
}

VL_INLINE_OPT void Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__7(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___nba_sequent__TOP__7\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.__VdlySet__adc_c2h_bridge_tb__DOT__adc_ofa_a__v0) {
        vlSelfRef.__VdlySet__adc_c2h_bridge_tb__DOT__adc_ofa_a__v0 = 0U;
        vlSelfRef.adc_c2h_bridge_tb__DOT__adc_ofa_a 
            = vlSelfRef.__VdlyVal__adc_c2h_bridge_tb__DOT__adc_ofa_a__v0;
    }
    if (vlSelfRef.__VdlySet__adc_c2h_bridge_tb__DOT__adc_ofa_a__v1) {
        vlSelfRef.__VdlySet__adc_c2h_bridge_tb__DOT__adc_ofa_a__v1 = 0U;
        vlSelfRef.adc_c2h_bridge_tb__DOT__adc_ofa_a 
            = vlSelfRef.__VdlyVal__adc_c2h_bridge_tb__DOT__adc_ofa_a__v1;
    }
    if (vlSelfRef.__VdlySet__adc_c2h_bridge_tb__DOT__adc_ofa_a__v2) {
        vlSelfRef.__VdlySet__adc_c2h_bridge_tb__DOT__adc_ofa_a__v2 = 0U;
        vlSelfRef.adc_c2h_bridge_tb__DOT__adc_ofa_a 
            = vlSelfRef.__VdlyVal__adc_c2h_bridge_tb__DOT__adc_ofa_a__v2;
    }
    if (vlSelfRef.__VdlySet__adc_c2h_bridge_tb__DOT__adc_ofa_a__v3) {
        vlSelfRef.__VdlySet__adc_c2h_bridge_tb__DOT__adc_ofa_a__v3 = 0U;
        vlSelfRef.adc_c2h_bridge_tb__DOT__adc_ofa_a 
            = vlSelfRef.__VdlyVal__adc_c2h_bridge_tb__DOT__adc_ofa_a__v3;
    }
    if (vlSelfRef.__VdlySet__adc_c2h_bridge_tb__DOT__adc_data_a__v0) {
        vlSelfRef.__VdlySet__adc_c2h_bridge_tb__DOT__adc_data_a__v0 = 0U;
        vlSelfRef.adc_c2h_bridge_tb__DOT__adc_data_a 
            = vlSelfRef.__VdlyVal__adc_c2h_bridge_tb__DOT__adc_data_a__v0;
    }
    if (vlSelfRef.__VdlySet__adc_c2h_bridge_tb__DOT__adc_data_a__v1) {
        vlSelfRef.__VdlySet__adc_c2h_bridge_tb__DOT__adc_data_a__v1 = 0U;
        vlSelfRef.adc_c2h_bridge_tb__DOT__adc_data_a 
            = vlSelfRef.__VdlyVal__adc_c2h_bridge_tb__DOT__adc_data_a__v1;
    }
    if (vlSelfRef.__VdlySet__adc_c2h_bridge_tb__DOT__adc_data_a__v2) {
        vlSelfRef.__VdlySet__adc_c2h_bridge_tb__DOT__adc_data_a__v2 = 0U;
        vlSelfRef.adc_c2h_bridge_tb__DOT__adc_data_a 
            = vlSelfRef.__VdlyVal__adc_c2h_bridge_tb__DOT__adc_data_a__v2;
    }
    if (vlSelfRef.__VdlySet__adc_c2h_bridge_tb__DOT__adc_data_a__v3) {
        vlSelfRef.__VdlySet__adc_c2h_bridge_tb__DOT__adc_data_a__v3 = 0U;
        vlSelfRef.adc_c2h_bridge_tb__DOT__adc_data_a 
            = vlSelfRef.__VdlyVal__adc_c2h_bridge_tb__DOT__adc_data_a__v3;
    }
}

VL_INLINE_OPT void Vadc_c2h_bridge_tb___024root___nba_comb__TOP__0(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___nba_comb__TOP__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__fifo_rd_en 
        = (1U & ((~ (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__fifo_empty)) 
                 & ((~ (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__beat_valid)) 
                    | (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__beat_consumed))));
    vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_bin_next 
        = (0xfffU & ((IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__u_async_fifo__DOT__rd_ptr_bin) 
                     + ((~ (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__fifo_empty)) 
                        & (IData)(vlSelfRef.adc_c2h_bridge_tb__DOT__u_bridge__DOT__fifo_rd_en))));
}

void Vadc_c2h_bridge_tb___024root___timing_resume(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___timing_resume\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((0x100ULL & vlSelfRef.__VactTriggered.word(0U))) {
        vlSelfRef.__VtrigSched_h54500120__0.resume(
                                                   "@([changed] adc_c2h_bridge_tb.sample_rst_n)");
    }
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        vlSelfRef.__VtrigSched_h8830d6f9__0.resume(
                                                   "@(posedge adc_c2h_bridge_tb.m_axis_aclk)");
    }
    if ((0x200ULL & vlSelfRef.__VactTriggered.word(0U))) {
        vlSelfRef.__VtrigSched_h05bb789a__0.resume(
                                                   "@(posedge adc_c2h_bridge_tb.u_adc_ctrl.adc_clk_reg)");
    }
    if ((0x40ULL & vlSelfRef.__VactTriggered.word(0U))) {
        vlSelfRef.__VtrigSched_h05bb795b__0.resume(
                                                   "@(negedge adc_c2h_bridge_tb.u_adc_ctrl.adc_clk_reg)");
    }
    if ((0x80ULL & vlSelfRef.__VactTriggered.word(0U))) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vadc_c2h_bridge_tb___024root___timing_commit(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___timing_commit\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((! (0x100ULL & vlSelfRef.__VactTriggered.word(0U)))) {
        vlSelfRef.__VtrigSched_h54500120__0.commit(
                                                   "@([changed] adc_c2h_bridge_tb.sample_rst_n)");
    }
    if ((! (1ULL & vlSelfRef.__VactTriggered.word(0U)))) {
        vlSelfRef.__VtrigSched_h8830d6f9__0.commit(
                                                   "@(posedge adc_c2h_bridge_tb.m_axis_aclk)");
    }
    if ((! (0x200ULL & vlSelfRef.__VactTriggered.word(0U)))) {
        vlSelfRef.__VtrigSched_h05bb789a__0.commit(
                                                   "@(posedge adc_c2h_bridge_tb.u_adc_ctrl.adc_clk_reg)");
    }
    if ((! (0x40ULL & vlSelfRef.__VactTriggered.word(0U)))) {
        vlSelfRef.__VtrigSched_h05bb795b__0.commit(
                                                   "@(negedge adc_c2h_bridge_tb.u_adc_ctrl.adc_clk_reg)");
    }
}

void Vadc_c2h_bridge_tb___024root___eval_triggers__act(Vadc_c2h_bridge_tb___024root* vlSelf);

bool Vadc_c2h_bridge_tb___024root___eval_phase__act(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___eval_phase__act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<10> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vadc_c2h_bridge_tb___024root___eval_triggers__act(vlSelf);
    Vadc_c2h_bridge_tb___024root___timing_commit(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vadc_c2h_bridge_tb___024root___timing_resume(vlSelf);
        Vadc_c2h_bridge_tb___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vadc_c2h_bridge_tb___024root___eval_phase__nba(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___eval_phase__nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vadc_c2h_bridge_tb___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vadc_c2h_bridge_tb___024root___dump_triggers__nba(Vadc_c2h_bridge_tb___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vadc_c2h_bridge_tb___024root___dump_triggers__act(Vadc_c2h_bridge_tb___024root* vlSelf);
#endif  // VL_DEBUG

void Vadc_c2h_bridge_tb___024root___eval(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___eval\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vadc_c2h_bridge_tb___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("adc_c2h_bridge_tb.sv", 15, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelfRef.__VactIterCount))) {
#ifdef VL_DEBUG
                Vadc_c2h_bridge_tb___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("adc_c2h_bridge_tb.sv", 15, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vadc_c2h_bridge_tb___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vadc_c2h_bridge_tb___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vadc_c2h_bridge_tb___024root___eval_debug_assertions(Vadc_c2h_bridge_tb___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_c2h_bridge_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_c2h_bridge_tb___024root___eval_debug_assertions\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
