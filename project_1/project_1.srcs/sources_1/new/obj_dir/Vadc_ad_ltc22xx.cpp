// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vadc_ad_ltc22xx__pch.h"

//============================================================
// Constructors

Vadc_ad_ltc22xx::Vadc_ad_ltc22xx(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vadc_ad_ltc22xx__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vadc_ad_ltc22xx::Vadc_ad_ltc22xx(const char* _vcname__)
    : Vadc_ad_ltc22xx(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vadc_ad_ltc22xx::~Vadc_ad_ltc22xx() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vadc_ad_ltc22xx___024root___eval_debug_assertions(Vadc_ad_ltc22xx___024root* vlSelf);
#endif  // VL_DEBUG
void Vadc_ad_ltc22xx___024root___eval_static(Vadc_ad_ltc22xx___024root* vlSelf);
void Vadc_ad_ltc22xx___024root___eval_initial(Vadc_ad_ltc22xx___024root* vlSelf);
void Vadc_ad_ltc22xx___024root___eval_settle(Vadc_ad_ltc22xx___024root* vlSelf);
void Vadc_ad_ltc22xx___024root___eval(Vadc_ad_ltc22xx___024root* vlSelf);

void Vadc_ad_ltc22xx::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vadc_ad_ltc22xx::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vadc_ad_ltc22xx___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vadc_ad_ltc22xx___024root___eval_static(&(vlSymsp->TOP));
        Vadc_ad_ltc22xx___024root___eval_initial(&(vlSymsp->TOP));
        Vadc_ad_ltc22xx___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vadc_ad_ltc22xx___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vadc_ad_ltc22xx::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty(); }

uint64_t Vadc_ad_ltc22xx::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vadc_ad_ltc22xx::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vadc_ad_ltc22xx___024root___eval_final(Vadc_ad_ltc22xx___024root* vlSelf);

VL_ATTR_COLD void Vadc_ad_ltc22xx::final() {
    Vadc_ad_ltc22xx___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vadc_ad_ltc22xx::hierName() const { return vlSymsp->name(); }
const char* Vadc_ad_ltc22xx::modelName() const { return "Vadc_ad_ltc22xx"; }
unsigned Vadc_ad_ltc22xx::threads() const { return 1; }
void Vadc_ad_ltc22xx::prepareClone() const { contextp()->prepareClone(); }
void Vadc_ad_ltc22xx::atClone() const {
    contextp()->threadPoolpOnClone();
}
