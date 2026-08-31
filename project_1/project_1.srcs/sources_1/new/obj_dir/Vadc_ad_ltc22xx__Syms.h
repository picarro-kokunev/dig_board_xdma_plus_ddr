// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VADC_AD_LTC22XX__SYMS_H_
#define VERILATED_VADC_AD_LTC22XX__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vadc_ad_ltc22xx.h"

// INCLUDE MODULE CLASSES
#include "Vadc_ad_ltc22xx___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vadc_ad_ltc22xx__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vadc_ad_ltc22xx* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vadc_ad_ltc22xx___024root      TOP;

    // SCOPE NAMES
    VerilatedScope __Vscope_adc_c2h_bridge_tb;
    VerilatedScope __Vscope_adc_c2h_bridge_tb__u_adc_model;
    VerilatedScope __Vscope_adc_c2h_bridge_tb__unnamedblk1__unnamedblk2;

    // CONSTRUCTORS
    Vadc_ad_ltc22xx__Syms(VerilatedContext* contextp, const char* namep, Vadc_ad_ltc22xx* modelp);
    ~Vadc_ad_ltc22xx__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
