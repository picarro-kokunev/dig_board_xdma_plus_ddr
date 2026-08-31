// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vadc_c2h_bridge_tb__pch.h"

//============================================================
// Constructors

Vadc_c2h_bridge_tb::Vadc_c2h_bridge_tb(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vadc_c2h_bridge_tb__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vadc_c2h_bridge_tb::Vadc_c2h_bridge_tb(const char* _vcname__)
    : Vadc_c2h_bridge_tb(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vadc_c2h_bridge_tb::~Vadc_c2h_bridge_tb() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vadc_c2h_bridge_tb___024root___eval_debug_assertions(Vadc_c2h_bridge_tb___024root* vlSelf);
#endif  // VL_DEBUG
void Vadc_c2h_bridge_tb___024root___eval_static(Vadc_c2h_bridge_tb___024root* vlSelf);
void Vadc_c2h_bridge_tb___024root___eval_initial(Vadc_c2h_bridge_tb___024root* vlSelf);
void Vadc_c2h_bridge_tb___024root___eval_settle(Vadc_c2h_bridge_tb___024root* vlSelf);
void Vadc_c2h_bridge_tb___024root___eval(Vadc_c2h_bridge_tb___024root* vlSelf);

void Vadc_c2h_bridge_tb::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vadc_c2h_bridge_tb::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vadc_c2h_bridge_tb___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vadc_c2h_bridge_tb___024root___eval_static(&(vlSymsp->TOP));
        Vadc_c2h_bridge_tb___024root___eval_initial(&(vlSymsp->TOP));
        Vadc_c2h_bridge_tb___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vadc_c2h_bridge_tb___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vadc_c2h_bridge_tb::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty(); }

uint64_t Vadc_c2h_bridge_tb::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vadc_c2h_bridge_tb::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vadc_c2h_bridge_tb___024root___eval_final(Vadc_c2h_bridge_tb___024root* vlSelf);

VL_ATTR_COLD void Vadc_c2h_bridge_tb::final() {
    Vadc_c2h_bridge_tb___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vadc_c2h_bridge_tb::hierName() const { return vlSymsp->name(); }
const char* Vadc_c2h_bridge_tb::modelName() const { return "Vadc_c2h_bridge_tb"; }
unsigned Vadc_c2h_bridge_tb::threads() const { return 1; }
void Vadc_c2h_bridge_tb::prepareClone() const { contextp()->prepareClone(); }
void Vadc_c2h_bridge_tb::atClone() const {
    contextp()->threadPoolpOnClone();
}
