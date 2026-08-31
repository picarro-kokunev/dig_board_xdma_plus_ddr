// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vadc_c2h_bridge_tb.h for the primary calling header

#include "Vadc_c2h_bridge_tb__pch.h"
#include "Vadc_c2h_bridge_tb__Syms.h"
#include "Vadc_c2h_bridge_tb___024root.h"

void Vadc_c2h_bridge_tb___024root___ctor_var_reset(Vadc_c2h_bridge_tb___024root* vlSelf);

Vadc_c2h_bridge_tb___024root::Vadc_c2h_bridge_tb___024root(Vadc_c2h_bridge_tb__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , __VdlySched{*symsp->_vm_contextp__}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vadc_c2h_bridge_tb___024root___ctor_var_reset(this);
}

void Vadc_c2h_bridge_tb___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vadc_c2h_bridge_tb___024root::~Vadc_c2h_bridge_tb___024root() {
}
