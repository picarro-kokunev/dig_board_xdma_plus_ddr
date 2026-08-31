// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vadc_ad_ltc22xx.h for the primary calling header

#include "Vadc_ad_ltc22xx__pch.h"
#include "Vadc_ad_ltc22xx__Syms.h"
#include "Vadc_ad_ltc22xx___024root.h"

void Vadc_ad_ltc22xx___024root___ctor_var_reset(Vadc_ad_ltc22xx___024root* vlSelf);

Vadc_ad_ltc22xx___024root::Vadc_ad_ltc22xx___024root(Vadc_ad_ltc22xx__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , __VdlySched{*symsp->_vm_contextp__}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vadc_ad_ltc22xx___024root___ctor_var_reset(this);
}

void Vadc_ad_ltc22xx___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vadc_ad_ltc22xx___024root::~Vadc_ad_ltc22xx___024root() {
}
