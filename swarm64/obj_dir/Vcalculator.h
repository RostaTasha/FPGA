// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _Vcalculator_H_
#define _Vcalculator_H_

#include "verilated.h"
class Vcalculator__Syms;
class VerilatedVcd;

//----------

VL_MODULE(Vcalculator) {
  public:
    // CELLS
    // Public to allow access to /*verilator_public*/ items;
    // otherwise the application code can consider these internals.
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(clk,0,0);
    VL_IN8(rst_n,0,0);
    VL_IN8(add_valid,0,0);
    VL_OUT8(add_ack,0,0);
    VL_IN8(sub_valid,0,0);
    VL_OUT8(sub_ack,0,0);
    VL_IN8(mul_valid,0,0);
    VL_OUT8(mul_ack,0,0);
    VL_OUT8(result_valid,0,0);
    VL_IN8(result_ack,0,0);
    VL_OUT8(result_unit,2,0);
    //char	__VpadToAlign11[5];
    VL_IN64(add_a,63,0);
    VL_IN64(add_b,63,0);
    VL_IN64(sub_a,63,0);
    VL_IN64(sub_b,63,0);
    VL_IN64(mul_a,63,0);
    VL_IN64(mul_b,63,0);
    VL_OUT64(result,63,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    VL_SIG8(v__DOT__add_res_valid,0,0);
    VL_SIG8(v__DOT__sub_res_valid,0,0);
    VL_SIG8(v__DOT__mul_inst__DOT__valid_pipe,3,0);
    VL_SIG8(v__DOT__mul_inst__DOT__run_pipeline,0,0);
    VL_SIG8(v__DOT__arbiter_inst__DOT__req,2,0);
    VL_SIG8(v__DOT__arbiter_inst__DOT__arbiter_ready,2,0);
    VL_SIG8(v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__pre_req,2,0);
    VL_SIG8(v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__mask_pre,2,0);
    VL_SIG8(v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__win,2,0);
    //char	__VpadToAlign85[3];
    VL_SIG(v__DOT__mul_inst__DOT__a_high,31,0);
    VL_SIG(v__DOT__mul_inst__DOT__a_low,31,0);
    VL_SIG(v__DOT__mul_inst__DOT__b_high,31,0);
    VL_SIG(v__DOT__mul_inst__DOT__b_low,31,0);
    VL_SIGW(v__DOT__mul_inst__DOT__mul_res1,127,0,4);
    VL_SIGW(v__DOT__mul_inst__DOT__mul_res2,127,0,4);
    VL_SIGW(v__DOT__mul_inst__DOT__mul_res3,127,0,4);
    VL_SIGW(v__DOT__mul_inst__DOT__mul_res4,127,0,4);
    VL_SIGW(v__DOT__mul_inst__DOT__mul_res5,127,0,4);
    VL_SIGW(v__DOT__mul_inst__DOT__mul_res6,127,0,4);
    VL_SIGW(v__DOT__mul_inst__DOT__mul_res7,127,0,4);
    VL_SIGW(v__DOT__mul_inst__DOT__keep_res,127,0,4);
    VL_SIGW(v__DOT__mul_inst__DOT__add_result,127,0,4);
    VL_SIG(v__DOT__mul_inst__DOT__sub_res1,31,0);
    VL_SIG(v__DOT__mul_inst__DOT__sub_res2,31,0);
    VL_SIG64(v__DOT__add_result,63,0);
    VL_SIG64(v__DOT__sub_result,63,0);
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    VL_SIG8(__Vclklast__TOP__clk,0,0);
    VL_SIG8(__Vclklast__TOP__rst_n,0,0);
    //char	__VpadToAlign278[2];
    VL_SIG(__Vm_traceActivity,31,0);
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vcalculator__Syms*	__VlSymsp;		// Symbol table
    
    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code
    
    // CONSTRUCTORS
  private:
    Vcalculator& operator= (const Vcalculator&);	///< Copying not allowed
    Vcalculator(const Vcalculator&);	///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible WRT DPI scope names.
    Vcalculator(const char* name="TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vcalculator();
    /// Trace signals in the model; called by application code
    void trace (VerilatedVcdC* tfp, int levels, int options=0);
    
    // USER METHODS
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval();
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vcalculator__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vcalculator__Syms* symsp, bool first);
  private:
    static QData	_change_request(Vcalculator__Syms* __restrict vlSymsp);
  public:
    static void	_combo__TOP__6(Vcalculator__Syms* __restrict vlSymsp);
    static void	_combo__TOP__8(Vcalculator__Syms* __restrict vlSymsp);
    static void	_eval(Vcalculator__Syms* __restrict vlSymsp);
    static void	_eval_initial(Vcalculator__Syms* __restrict vlSymsp);
    static void	_eval_settle(Vcalculator__Syms* __restrict vlSymsp);
    static void	_sequent__TOP__1(Vcalculator__Syms* __restrict vlSymsp);
    static void	_sequent__TOP__3(Vcalculator__Syms* __restrict vlSymsp);
    static void	_sequent__TOP__5(Vcalculator__Syms* __restrict vlSymsp);
    static void	_settle__TOP__2(Vcalculator__Syms* __restrict vlSymsp);
    static void	_settle__TOP__4(Vcalculator__Syms* __restrict vlSymsp);
    static void	_settle__TOP__7(Vcalculator__Syms* __restrict vlSymsp);
    static void	traceChgThis(Vcalculator__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void	traceChgThis__2(Vcalculator__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void	traceChgThis__3(Vcalculator__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void	traceChgThis__4(Vcalculator__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void	traceChgThis__5(Vcalculator__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void	traceFullThis(Vcalculator__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void	traceFullThis__1(Vcalculator__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void	traceInitThis(Vcalculator__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void	traceInitThis__1(Vcalculator__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceInit (VerilatedVcd* vcdp, void* userthis, uint32_t code);
    static void traceFull (VerilatedVcd* vcdp, void* userthis, uint32_t code);
    static void traceChg  (VerilatedVcd* vcdp, void* userthis, uint32_t code);
} VL_ATTR_ALIGNED(128);

#endif  /*guard*/
