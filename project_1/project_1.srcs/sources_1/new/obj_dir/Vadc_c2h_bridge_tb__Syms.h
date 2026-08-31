// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VADC_C2H_BRIDGE_TB__SYMS_H_
#define VERILATED_VADC_C2H_BRIDGE_TB__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vadc_c2h_bridge_tb.h"

// INCLUDE MODULE CLASSES
#include "Vadc_c2h_bridge_tb___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vadc_c2h_bridge_tb__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vadc_c2h_bridge_tb* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vadc_c2h_bridge_tb___024root   TOP;

    // SCOPE NAMES
    VerilatedScope __Vscope_adc_c2h_bridge_tb;
    VerilatedScope __Vscope_adc_c2h_bridge_tb__u_adc_model;
    VerilatedScope __Vscope_adc_c2h_bridge_tb__unnamedblk1__unnamedblk2;

    // CONSTRUCTORS
    Vadc_c2h_bridge_tb__Syms(VerilatedContext* contextp, const char* namep, Vadc_c2h_bridge_tb* modelp);
    ~Vadc_c2h_bridge_tb__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
