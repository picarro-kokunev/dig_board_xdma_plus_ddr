// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vadc_ad_ltc22xx__pch.h"
#include "Vadc_ad_ltc22xx.h"
#include "Vadc_ad_ltc22xx___024root.h"

// FUNCTIONS
Vadc_ad_ltc22xx__Syms::~Vadc_ad_ltc22xx__Syms()
{
}

Vadc_ad_ltc22xx__Syms::Vadc_ad_ltc22xx__Syms(VerilatedContext* contextp, const char* namep, Vadc_ad_ltc22xx* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
{
        // Check resources
        Verilated::stackCheck(34);
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    // Setup scopes
    __Vscope_adc_c2h_bridge_tb.configure(this, name(), "adc_c2h_bridge_tb", "adc_c2h_bridge_tb", "<null>", -9, VerilatedScope::SCOPE_OTHER);
    __Vscope_adc_c2h_bridge_tb__u_adc_model.configure(this, name(), "adc_c2h_bridge_tb.u_adc_model", "u_adc_model", "<null>", -9, VerilatedScope::SCOPE_OTHER);
    __Vscope_adc_c2h_bridge_tb__unnamedblk1__unnamedblk2.configure(this, name(), "adc_c2h_bridge_tb.unnamedblk1.unnamedblk2", "unnamedblk2", "<null>", -9, VerilatedScope::SCOPE_OTHER);
}
