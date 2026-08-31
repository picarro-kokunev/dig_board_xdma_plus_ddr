// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vadc_ad_ltc22xx.h for the primary calling header

#include "Vadc_ad_ltc22xx__pch.h"
#include "Vadc_ad_ltc22xx__Syms.h"
#include "Vadc_ad_ltc22xx___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vadc_ad_ltc22xx___024root___dump_triggers__stl(Vadc_ad_ltc22xx___024root* vlSelf);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vadc_ad_ltc22xx___024root___eval_triggers__stl(Vadc_ad_ltc22xx___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadc_ad_ltc22xx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadc_ad_ltc22xx___024root___eval_triggers__stl\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered.set(0U, (IData)(vlSelfRef.__VstlFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vadc_ad_ltc22xx___024root___dump_triggers__stl(vlSelf);
    }
#endif
}
