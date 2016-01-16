// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcalculator.h for the primary calling header

#include "Vcalculator.h"       // For This
#include "Vcalculator__Syms.h"

//--------------------
// STATIC VARIABLES


//--------------------

VL_CTOR_IMP(Vcalculator) {
    Vcalculator__Syms* __restrict vlSymsp = __VlSymsp = new Vcalculator__Syms(this, name());
    Vcalculator* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    clk = VL_RAND_RESET_I(1);
    rst_n = VL_RAND_RESET_I(1);
    add_valid = VL_RAND_RESET_I(1);
    add_ack = VL_RAND_RESET_I(1);
    add_a = VL_RAND_RESET_Q(64);
    add_b = VL_RAND_RESET_Q(64);
    sub_valid = VL_RAND_RESET_I(1);
    sub_ack = VL_RAND_RESET_I(1);
    sub_a = VL_RAND_RESET_Q(64);
    sub_b = VL_RAND_RESET_Q(64);
    mul_valid = VL_RAND_RESET_I(1);
    mul_ack = VL_RAND_RESET_I(1);
    mul_a = VL_RAND_RESET_Q(64);
    mul_b = VL_RAND_RESET_Q(64);
    result_valid = VL_RAND_RESET_I(1);
    result_ack = VL_RAND_RESET_I(1);
    result_unit = VL_RAND_RESET_I(3);
    result = VL_RAND_RESET_Q(64);
    v__DOT__add_result = VL_RAND_RESET_Q(64);
    v__DOT__add_res_valid = VL_RAND_RESET_I(1);
    v__DOT__sub_result = VL_RAND_RESET_Q(64);
    v__DOT__sub_res_valid = VL_RAND_RESET_I(1);
    v__DOT__mul_inst__DOT__a_high = VL_RAND_RESET_I(32);
    v__DOT__mul_inst__DOT__a_low = VL_RAND_RESET_I(32);
    v__DOT__mul_inst__DOT__b_high = VL_RAND_RESET_I(32);
    v__DOT__mul_inst__DOT__b_low = VL_RAND_RESET_I(32);
    VL_RAND_RESET_W(128,v__DOT__mul_inst__DOT__mul_res1);
    VL_RAND_RESET_W(128,v__DOT__mul_inst__DOT__mul_res2);
    VL_RAND_RESET_W(128,v__DOT__mul_inst__DOT__mul_res3);
    VL_RAND_RESET_W(128,v__DOT__mul_inst__DOT__mul_res4);
    VL_RAND_RESET_W(128,v__DOT__mul_inst__DOT__mul_res5);
    VL_RAND_RESET_W(128,v__DOT__mul_inst__DOT__mul_res6);
    VL_RAND_RESET_W(128,v__DOT__mul_inst__DOT__mul_res7);
    VL_RAND_RESET_W(128,v__DOT__mul_inst__DOT__keep_res);
    VL_RAND_RESET_W(128,v__DOT__mul_inst__DOT__add_result);
    v__DOT__mul_inst__DOT__sub_res1 = VL_RAND_RESET_I(32);
    v__DOT__mul_inst__DOT__sub_res2 = VL_RAND_RESET_I(32);
    v__DOT__mul_inst__DOT__valid_pipe = VL_RAND_RESET_I(4);
    v__DOT__mul_inst__DOT__run_pipeline = VL_RAND_RESET_I(1);
    v__DOT__arbiter_inst__DOT__req = VL_RAND_RESET_I(3);
    v__DOT__arbiter_inst__DOT__arbiter_ready = VL_RAND_RESET_I(3);
    v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__pre_req = VL_RAND_RESET_I(3);
    v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__mask_pre = VL_RAND_RESET_I(3);
    v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__win = VL_RAND_RESET_I(3);
    __Vclklast__TOP__clk = VL_RAND_RESET_I(1);
    __Vclklast__TOP__rst_n = VL_RAND_RESET_I(1);
    __Vm_traceActivity = VL_RAND_RESET_I(32);
}

void Vcalculator::__Vconfigure(Vcalculator__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vcalculator::~Vcalculator() {
    delete __VlSymsp; __VlSymsp=NULL;
}

//--------------------


void Vcalculator::eval() {
    Vcalculator__Syms* __restrict vlSymsp = this->__VlSymsp; // Setup global symbol table
    Vcalculator* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    VL_DEBUG_IF(VL_PRINTF("\n----TOP Evaluate Vcalculator::eval\n"); );
    int __VclockLoop = 0;
    QData __Vchange=1;
    while (VL_LIKELY(__Vchange)) {
	VL_DEBUG_IF(VL_PRINTF(" Clock loop\n"););
	vlSymsp->__Vm_activity = true;
	_eval(vlSymsp);
	__Vchange = _change_request(vlSymsp);
	if (++__VclockLoop > 100) vl_fatal(__FILE__,__LINE__,__FILE__,"Verilated model didn't converge");
    }
}

void Vcalculator::_eval_initial_loop(Vcalculator__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    vlSymsp->__Vm_activity = true;
    int __VclockLoop = 0;
    QData __Vchange=1;
    while (VL_LIKELY(__Vchange)) {
	_eval_settle(vlSymsp);
	_eval(vlSymsp);
	__Vchange = _change_request(vlSymsp);
	if (++__VclockLoop > 100) vl_fatal(__FILE__,__LINE__,__FILE__,"Verilated model didn't DC converge");
    }
}

//--------------------
// Internal Methods

VL_INLINE_OPT void Vcalculator::_sequent__TOP__1(Vcalculator__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    Vcalculator::_sequent__TOP__1\n"); );
    Vcalculator* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    VL_SIG8(__Vdly__v__DOT__mul_inst__DOT__valid_pipe,3,0);
    //char	__VpadToAlign5[3];
    VL_SIGW(__Vdly__v__DOT__mul_inst__DOT__mul_res4,127,0,4);
    VL_SIGW(__Vdly__v__DOT__mul_inst__DOT__mul_res6,127,0,4);
    VL_SIGW(__Vdly__v__DOT__mul_inst__DOT__mul_res7,127,0,4);
    VL_SIGW(__Vdly__v__DOT__mul_inst__DOT__mul_res5,127,0,4);
    VL_SIGW(__Vdly__v__DOT__mul_inst__DOT__keep_res,127,0,4);
    VL_SIGW(__Vdly__v__DOT__mul_inst__DOT__mul_res2,127,0,4);
    VL_SIGW(__Vdly__v__DOT__mul_inst__DOT__mul_res1,127,0,4);
    VL_SIGW(__Vdly__v__DOT__mul_inst__DOT__mul_res3,127,0,4);
    VL_SIG(__Vdly__v__DOT__mul_inst__DOT__sub_res1,31,0);
    VL_SIG(__Vdly__v__DOT__mul_inst__DOT__sub_res2,31,0);
    VL_SIG(__Vdly__v__DOT__mul_inst__DOT__a_high,31,0);
    VL_SIG(__Vdly__v__DOT__mul_inst__DOT__a_low,31,0);
    VL_SIG(__Vdly__v__DOT__mul_inst__DOT__b_high,31,0);
    VL_SIG(__Vdly__v__DOT__mul_inst__DOT__b_low,31,0);
    VL_SIGW(__Vtemp1,127,0,4);
    VL_SIGW(__Vtemp2,127,0,4);
    VL_SIGW(__Vtemp3,127,0,4);
    VL_SIGW(__Vtemp4,127,0,4);
    VL_SIGW(__Vtemp5,127,0,4);
    VL_SIGW(__Vtemp6,127,0,4);
    VL_SIGW(__Vtemp7,127,0,4);
    VL_SIGW(__Vtemp8,127,0,4);
    VL_SIGW(__Vtemp9,127,0,4);
    VL_SIGW(__Vtemp10,127,0,4);
    VL_SIGW(__Vtemp11,127,0,4);
    VL_SIGW(__Vtemp12,127,0,4);
    VL_SIGW(__Vtemp13,127,0,4);
    VL_SIGW(__Vtemp14,127,0,4);
    VL_SIGW(__Vtemp15,127,0,4);
    VL_SIGW(__Vtemp16,127,0,4);
    VL_SIGW(__Vtemp17,127,0,4);
    // Body
    __Vdly__v__DOT__mul_inst__DOT__mul_res4[0U] = vlTOPp->v__DOT__mul_inst__DOT__mul_res4[0U];
    __Vdly__v__DOT__mul_inst__DOT__mul_res4[1U] = vlTOPp->v__DOT__mul_inst__DOT__mul_res4[1U];
    __Vdly__v__DOT__mul_inst__DOT__mul_res4[2U] = vlTOPp->v__DOT__mul_inst__DOT__mul_res4[2U];
    __Vdly__v__DOT__mul_inst__DOT__mul_res4[3U] = vlTOPp->v__DOT__mul_inst__DOT__mul_res4[3U];
    __Vdly__v__DOT__mul_inst__DOT__mul_res6[0U] = vlTOPp->v__DOT__mul_inst__DOT__mul_res6[0U];
    __Vdly__v__DOT__mul_inst__DOT__mul_res6[1U] = vlTOPp->v__DOT__mul_inst__DOT__mul_res6[1U];
    __Vdly__v__DOT__mul_inst__DOT__mul_res6[2U] = vlTOPp->v__DOT__mul_inst__DOT__mul_res6[2U];
    __Vdly__v__DOT__mul_inst__DOT__mul_res6[3U] = vlTOPp->v__DOT__mul_inst__DOT__mul_res6[3U];
    __Vdly__v__DOT__mul_inst__DOT__mul_res7[0U] = vlTOPp->v__DOT__mul_inst__DOT__mul_res7[0U];
    __Vdly__v__DOT__mul_inst__DOT__mul_res7[1U] = vlTOPp->v__DOT__mul_inst__DOT__mul_res7[1U];
    __Vdly__v__DOT__mul_inst__DOT__mul_res7[2U] = vlTOPp->v__DOT__mul_inst__DOT__mul_res7[2U];
    __Vdly__v__DOT__mul_inst__DOT__mul_res7[3U] = vlTOPp->v__DOT__mul_inst__DOT__mul_res7[3U];
    __Vdly__v__DOT__mul_inst__DOT__mul_res5[0U] = vlTOPp->v__DOT__mul_inst__DOT__mul_res5[0U];
    __Vdly__v__DOT__mul_inst__DOT__mul_res5[1U] = vlTOPp->v__DOT__mul_inst__DOT__mul_res5[1U];
    __Vdly__v__DOT__mul_inst__DOT__mul_res5[2U] = vlTOPp->v__DOT__mul_inst__DOT__mul_res5[2U];
    __Vdly__v__DOT__mul_inst__DOT__mul_res5[3U] = vlTOPp->v__DOT__mul_inst__DOT__mul_res5[3U];
    __Vdly__v__DOT__mul_inst__DOT__keep_res[0U] = vlTOPp->v__DOT__mul_inst__DOT__keep_res[0U];
    __Vdly__v__DOT__mul_inst__DOT__keep_res[1U] = vlTOPp->v__DOT__mul_inst__DOT__keep_res[1U];
    __Vdly__v__DOT__mul_inst__DOT__keep_res[2U] = vlTOPp->v__DOT__mul_inst__DOT__keep_res[2U];
    __Vdly__v__DOT__mul_inst__DOT__keep_res[3U] = vlTOPp->v__DOT__mul_inst__DOT__keep_res[3U];
    __Vdly__v__DOT__mul_inst__DOT__mul_res2[0U] = vlTOPp->v__DOT__mul_inst__DOT__mul_res2[0U];
    __Vdly__v__DOT__mul_inst__DOT__mul_res2[1U] = vlTOPp->v__DOT__mul_inst__DOT__mul_res2[1U];
    __Vdly__v__DOT__mul_inst__DOT__mul_res2[2U] = vlTOPp->v__DOT__mul_inst__DOT__mul_res2[2U];
    __Vdly__v__DOT__mul_inst__DOT__mul_res2[3U] = vlTOPp->v__DOT__mul_inst__DOT__mul_res2[3U];
    __Vdly__v__DOT__mul_inst__DOT__mul_res1[0U] = vlTOPp->v__DOT__mul_inst__DOT__mul_res1[0U];
    __Vdly__v__DOT__mul_inst__DOT__mul_res1[1U] = vlTOPp->v__DOT__mul_inst__DOT__mul_res1[1U];
    __Vdly__v__DOT__mul_inst__DOT__mul_res1[2U] = vlTOPp->v__DOT__mul_inst__DOT__mul_res1[2U];
    __Vdly__v__DOT__mul_inst__DOT__mul_res1[3U] = vlTOPp->v__DOT__mul_inst__DOT__mul_res1[3U];
    __Vdly__v__DOT__mul_inst__DOT__mul_res3[0U] = vlTOPp->v__DOT__mul_inst__DOT__mul_res3[0U];
    __Vdly__v__DOT__mul_inst__DOT__mul_res3[1U] = vlTOPp->v__DOT__mul_inst__DOT__mul_res3[1U];
    __Vdly__v__DOT__mul_inst__DOT__mul_res3[2U] = vlTOPp->v__DOT__mul_inst__DOT__mul_res3[2U];
    __Vdly__v__DOT__mul_inst__DOT__mul_res3[3U] = vlTOPp->v__DOT__mul_inst__DOT__mul_res3[3U];
    __Vdly__v__DOT__mul_inst__DOT__sub_res1 = vlTOPp->v__DOT__mul_inst__DOT__sub_res1;
    __Vdly__v__DOT__mul_inst__DOT__sub_res2 = vlTOPp->v__DOT__mul_inst__DOT__sub_res2;
    __Vdly__v__DOT__mul_inst__DOT__a_high = vlTOPp->v__DOT__mul_inst__DOT__a_high;
    __Vdly__v__DOT__mul_inst__DOT__a_low = vlTOPp->v__DOT__mul_inst__DOT__a_low;
    __Vdly__v__DOT__mul_inst__DOT__b_high = vlTOPp->v__DOT__mul_inst__DOT__b_high;
    __Vdly__v__DOT__mul_inst__DOT__b_low = vlTOPp->v__DOT__mul_inst__DOT__b_low;
    __Vdly__v__DOT__mul_inst__DOT__valid_pipe = vlTOPp->v__DOT__mul_inst__DOT__valid_pipe;
    // ALWAYS at arbiter_engine.sv:30
    if (vlTOPp->rst_n) {
	if ((0U != (IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__win))) {
	    vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__pre_req 
		= vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__win;
	}
    } else {
	vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__pre_req = 0U;
    }
    // ALWAYS at add.sv:21
    if (vlTOPp->rst_n) {
	vlTOPp->v__DOT__add_res_valid = vlTOPp->add_valid;
	if (vlTOPp->add_valid) {
	    vlTOPp->v__DOT__add_result = (vlTOPp->add_a 
					  + vlTOPp->add_b);
	}
    } else {
	vlTOPp->v__DOT__add_result = VL_ULL(0);
	vlTOPp->v__DOT__add_res_valid = 0U;
    }
    // ALWAYS at sub.sv:23
    if (vlTOPp->rst_n) {
	vlTOPp->v__DOT__sub_res_valid = vlTOPp->sub_valid;
	if (vlTOPp->sub_valid) {
	    vlTOPp->v__DOT__sub_result = (vlTOPp->sub_a 
					  - vlTOPp->sub_b);
	}
    } else {
	vlTOPp->v__DOT__sub_result = VL_ULL(0);
	vlTOPp->v__DOT__sub_res_valid = 0U;
    }
    // ALWAYS at mul.sv:94
    if (vlTOPp->rst_n) {
	if (vlTOPp->v__DOT__mul_inst__DOT__run_pipeline) {
	    VL_ADD_W(4, __Vtemp1, vlTOPp->v__DOT__mul_inst__DOT__mul_res4, vlTOPp->v__DOT__mul_inst__DOT__mul_res5);
	    VL_SUB_W(4, __Vtemp2, __Vtemp1, vlTOPp->v__DOT__mul_inst__DOT__mul_res6);
	    VL_ADD_W(4, __Vtemp3, __Vtemp2, vlTOPp->v__DOT__mul_inst__DOT__mul_res7);
	    VL_ADD_W(4, __Vtemp4, __Vtemp3, vlTOPp->v__DOT__mul_inst__DOT__keep_res);
	    vlTOPp->v__DOT__mul_inst__DOT__add_result[0U] 
		= __Vtemp4[0U];
	    vlTOPp->v__DOT__mul_inst__DOT__add_result[1U] 
		= __Vtemp4[1U];
	    vlTOPp->v__DOT__mul_inst__DOT__add_result[2U] 
		= __Vtemp4[2U];
	    vlTOPp->v__DOT__mul_inst__DOT__add_result[3U] 
		= __Vtemp4[3U];
	    VL_SHIFTL_WWI(128,128,32, __Vtemp5, vlTOPp->v__DOT__mul_inst__DOT__mul_res1, 0x20U);
	    __Vdly__v__DOT__mul_inst__DOT__mul_res4[0U] 
		= __Vtemp5[0U];
	    __Vdly__v__DOT__mul_inst__DOT__mul_res4[1U] 
		= __Vtemp5[1U];
	    __Vdly__v__DOT__mul_inst__DOT__mul_res4[2U] 
		= __Vtemp5[2U];
	    __Vdly__v__DOT__mul_inst__DOT__mul_res4[3U] 
		= __Vtemp5[3U];
	    VL_SHIFTL_WWI(128,128,32, __Vtemp6, vlTOPp->v__DOT__mul_inst__DOT__mul_res2, 0x20U);
	    __Vdly__v__DOT__mul_inst__DOT__mul_res6[0U] 
		= __Vtemp6[0U];
	    __Vdly__v__DOT__mul_inst__DOT__mul_res6[1U] 
		= __Vtemp6[1U];
	    __Vdly__v__DOT__mul_inst__DOT__mul_res6[2U] 
		= __Vtemp6[2U];
	    __Vdly__v__DOT__mul_inst__DOT__mul_res6[3U] 
		= __Vtemp6[3U];
	    VL_SHIFTL_WWI(128,128,32, __Vtemp7, vlTOPp->v__DOT__mul_inst__DOT__mul_res3, 0x20U);
	    __Vdly__v__DOT__mul_inst__DOT__mul_res7[0U] 
		= __Vtemp7[0U];
	    __Vdly__v__DOT__mul_inst__DOT__mul_res7[1U] 
		= __Vtemp7[1U];
	    __Vdly__v__DOT__mul_inst__DOT__mul_res7[2U] 
		= __Vtemp7[2U];
	    __Vdly__v__DOT__mul_inst__DOT__mul_res7[3U] 
		= __Vtemp7[3U];
	    VL_SHIFTL_WWI(128,128,32, __Vtemp8, vlTOPp->v__DOT__mul_inst__DOT__mul_res1, 0x40U);
	    __Vdly__v__DOT__mul_inst__DOT__mul_res5[0U] 
		= __Vtemp8[0U];
	    __Vdly__v__DOT__mul_inst__DOT__mul_res5[1U] 
		= __Vtemp8[1U];
	    __Vdly__v__DOT__mul_inst__DOT__mul_res5[2U] 
		= __Vtemp8[2U];
	    __Vdly__v__DOT__mul_inst__DOT__mul_res5[3U] 
		= __Vtemp8[3U];
	    __Vdly__v__DOT__mul_inst__DOT__keep_res[0U] 
		= vlTOPp->v__DOT__mul_inst__DOT__mul_res3[0U];
	    __Vdly__v__DOT__mul_inst__DOT__keep_res[1U] 
		= vlTOPp->v__DOT__mul_inst__DOT__mul_res3[1U];
	    __Vdly__v__DOT__mul_inst__DOT__keep_res[2U] 
		= vlTOPp->v__DOT__mul_inst__DOT__mul_res3[2U];
	    __Vdly__v__DOT__mul_inst__DOT__keep_res[3U] 
		= vlTOPp->v__DOT__mul_inst__DOT__mul_res3[3U];
	    VL_EXTEND_WI(128,32, __Vtemp9, vlTOPp->v__DOT__mul_inst__DOT__sub_res1);
	    VL_EXTEND_WI(128,32, __Vtemp10, vlTOPp->v__DOT__mul_inst__DOT__sub_res2);
	    VL_MUL_W(4, __Vtemp11, __Vtemp9, __Vtemp10);
	    __Vdly__v__DOT__mul_inst__DOT__mul_res2[0U] 
		= __Vtemp11[0U];
	    __Vdly__v__DOT__mul_inst__DOT__mul_res2[1U] 
		= __Vtemp11[1U];
	    __Vdly__v__DOT__mul_inst__DOT__mul_res2[2U] 
		= __Vtemp11[2U];
	    __Vdly__v__DOT__mul_inst__DOT__mul_res2[3U] 
		= __Vtemp11[3U];
	    VL_EXTEND_WI(128,32, __Vtemp12, vlTOPp->v__DOT__mul_inst__DOT__a_high);
	    VL_EXTEND_WI(128,32, __Vtemp13, vlTOPp->v__DOT__mul_inst__DOT__b_high);
	    VL_MUL_W(4, __Vtemp14, __Vtemp12, __Vtemp13);
	    __Vdly__v__DOT__mul_inst__DOT__mul_res1[0U] 
		= __Vtemp14[0U];
	    __Vdly__v__DOT__mul_inst__DOT__mul_res1[1U] 
		= __Vtemp14[1U];
	    __Vdly__v__DOT__mul_inst__DOT__mul_res1[2U] 
		= __Vtemp14[2U];
	    __Vdly__v__DOT__mul_inst__DOT__mul_res1[3U] 
		= __Vtemp14[3U];
	    VL_EXTEND_WI(128,32, __Vtemp15, vlTOPp->v__DOT__mul_inst__DOT__a_low);
	    VL_EXTEND_WI(128,32, __Vtemp16, vlTOPp->v__DOT__mul_inst__DOT__b_low);
	    VL_MUL_W(4, __Vtemp17, __Vtemp15, __Vtemp16);
	    __Vdly__v__DOT__mul_inst__DOT__mul_res3[0U] 
		= __Vtemp17[0U];
	    __Vdly__v__DOT__mul_inst__DOT__mul_res3[1U] 
		= __Vtemp17[1U];
	    __Vdly__v__DOT__mul_inst__DOT__mul_res3[2U] 
		= __Vtemp17[2U];
	    __Vdly__v__DOT__mul_inst__DOT__mul_res3[3U] 
		= __Vtemp17[3U];
	    __Vdly__v__DOT__mul_inst__DOT__sub_res1 
		= ((IData)((vlTOPp->mul_a >> 0x20U)) 
		   - (IData)(vlTOPp->mul_a));
	    __Vdly__v__DOT__mul_inst__DOT__sub_res2 
		= ((IData)((vlTOPp->mul_b >> 0x20U)) 
		   - (IData)(vlTOPp->mul_b));
	    __Vdly__v__DOT__mul_inst__DOT__a_high = (IData)(
							    (vlTOPp->mul_a 
							     >> 0x20U));
	    __Vdly__v__DOT__mul_inst__DOT__a_low = (IData)(vlTOPp->mul_a);
	    __Vdly__v__DOT__mul_inst__DOT__b_high = (IData)(
							    (vlTOPp->mul_b 
							     >> 0x20U));
	    __Vdly__v__DOT__mul_inst__DOT__b_low = (IData)(vlTOPp->mul_b);
	    __Vdly__v__DOT__mul_inst__DOT__valid_pipe 
		= ((0xeU & (IData)(__Vdly__v__DOT__mul_inst__DOT__valid_pipe)) 
		   | (IData)(vlTOPp->mul_valid));
	    __Vdly__v__DOT__mul_inst__DOT__valid_pipe 
		= ((0xdU & (IData)(__Vdly__v__DOT__mul_inst__DOT__valid_pipe)) 
		   | (2U & ((IData)(vlTOPp->v__DOT__mul_inst__DOT__valid_pipe) 
			    << 1U)));
	    __Vdly__v__DOT__mul_inst__DOT__valid_pipe 
		= ((0xbU & (IData)(__Vdly__v__DOT__mul_inst__DOT__valid_pipe)) 
		   | (4U & ((IData)(vlTOPp->v__DOT__mul_inst__DOT__valid_pipe) 
			    << 1U)));
	    __Vdly__v__DOT__mul_inst__DOT__valid_pipe 
		= ((7U & (IData)(__Vdly__v__DOT__mul_inst__DOT__valid_pipe)) 
		   | (8U & ((IData)(vlTOPp->v__DOT__mul_inst__DOT__valid_pipe) 
			    << 1U)));
	}
    } else {
	__Vdly__v__DOT__mul_inst__DOT__mul_res1[0U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__mul_res1[1U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__mul_res1[2U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__mul_res1[3U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__mul_res2[0U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__mul_res2[1U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__mul_res2[2U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__mul_res2[3U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__mul_res3[0U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__mul_res3[1U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__mul_res3[2U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__mul_res3[3U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__mul_res4[0U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__mul_res4[1U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__mul_res4[2U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__mul_res4[3U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__mul_res5[0U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__mul_res5[1U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__mul_res5[2U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__mul_res5[3U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__mul_res6[0U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__mul_res6[1U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__mul_res6[2U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__mul_res6[3U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__mul_res7[0U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__mul_res7[1U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__mul_res7[2U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__mul_res7[3U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__keep_res[0U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__keep_res[1U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__keep_res[2U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__keep_res[3U] = 0U;
	__Vdly__v__DOT__mul_inst__DOT__sub_res1 = 0U;
	__Vdly__v__DOT__mul_inst__DOT__sub_res2 = 0U;
	__Vdly__v__DOT__mul_inst__DOT__valid_pipe = 0U;
	vlTOPp->v__DOT__mul_inst__DOT__add_result[0U] = 0U;
	vlTOPp->v__DOT__mul_inst__DOT__add_result[1U] = 0U;
	vlTOPp->v__DOT__mul_inst__DOT__add_result[2U] = 0U;
	vlTOPp->v__DOT__mul_inst__DOT__add_result[3U] = 0U;
    }
    vlTOPp->v__DOT__mul_inst__DOT__mul_res4[0U] = __Vdly__v__DOT__mul_inst__DOT__mul_res4[0U];
    vlTOPp->v__DOT__mul_inst__DOT__mul_res4[1U] = __Vdly__v__DOT__mul_inst__DOT__mul_res4[1U];
    vlTOPp->v__DOT__mul_inst__DOT__mul_res4[2U] = __Vdly__v__DOT__mul_inst__DOT__mul_res4[2U];
    vlTOPp->v__DOT__mul_inst__DOT__mul_res4[3U] = __Vdly__v__DOT__mul_inst__DOT__mul_res4[3U];
    vlTOPp->v__DOT__mul_inst__DOT__mul_res5[0U] = __Vdly__v__DOT__mul_inst__DOT__mul_res5[0U];
    vlTOPp->v__DOT__mul_inst__DOT__mul_res5[1U] = __Vdly__v__DOT__mul_inst__DOT__mul_res5[1U];
    vlTOPp->v__DOT__mul_inst__DOT__mul_res5[2U] = __Vdly__v__DOT__mul_inst__DOT__mul_res5[2U];
    vlTOPp->v__DOT__mul_inst__DOT__mul_res5[3U] = __Vdly__v__DOT__mul_inst__DOT__mul_res5[3U];
    vlTOPp->v__DOT__mul_inst__DOT__mul_res6[0U] = __Vdly__v__DOT__mul_inst__DOT__mul_res6[0U];
    vlTOPp->v__DOT__mul_inst__DOT__mul_res6[1U] = __Vdly__v__DOT__mul_inst__DOT__mul_res6[1U];
    vlTOPp->v__DOT__mul_inst__DOT__mul_res6[2U] = __Vdly__v__DOT__mul_inst__DOT__mul_res6[2U];
    vlTOPp->v__DOT__mul_inst__DOT__mul_res6[3U] = __Vdly__v__DOT__mul_inst__DOT__mul_res6[3U];
    vlTOPp->v__DOT__mul_inst__DOT__mul_res7[0U] = __Vdly__v__DOT__mul_inst__DOT__mul_res7[0U];
    vlTOPp->v__DOT__mul_inst__DOT__mul_res7[1U] = __Vdly__v__DOT__mul_inst__DOT__mul_res7[1U];
    vlTOPp->v__DOT__mul_inst__DOT__mul_res7[2U] = __Vdly__v__DOT__mul_inst__DOT__mul_res7[2U];
    vlTOPp->v__DOT__mul_inst__DOT__mul_res7[3U] = __Vdly__v__DOT__mul_inst__DOT__mul_res7[3U];
    vlTOPp->v__DOT__mul_inst__DOT__keep_res[0U] = __Vdly__v__DOT__mul_inst__DOT__keep_res[0U];
    vlTOPp->v__DOT__mul_inst__DOT__keep_res[1U] = __Vdly__v__DOT__mul_inst__DOT__keep_res[1U];
    vlTOPp->v__DOT__mul_inst__DOT__keep_res[2U] = __Vdly__v__DOT__mul_inst__DOT__keep_res[2U];
    vlTOPp->v__DOT__mul_inst__DOT__keep_res[3U] = __Vdly__v__DOT__mul_inst__DOT__keep_res[3U];
    vlTOPp->v__DOT__mul_inst__DOT__mul_res1[0U] = __Vdly__v__DOT__mul_inst__DOT__mul_res1[0U];
    vlTOPp->v__DOT__mul_inst__DOT__mul_res1[1U] = __Vdly__v__DOT__mul_inst__DOT__mul_res1[1U];
    vlTOPp->v__DOT__mul_inst__DOT__mul_res1[2U] = __Vdly__v__DOT__mul_inst__DOT__mul_res1[2U];
    vlTOPp->v__DOT__mul_inst__DOT__mul_res1[3U] = __Vdly__v__DOT__mul_inst__DOT__mul_res1[3U];
    vlTOPp->v__DOT__mul_inst__DOT__mul_res2[0U] = __Vdly__v__DOT__mul_inst__DOT__mul_res2[0U];
    vlTOPp->v__DOT__mul_inst__DOT__mul_res2[1U] = __Vdly__v__DOT__mul_inst__DOT__mul_res2[1U];
    vlTOPp->v__DOT__mul_inst__DOT__mul_res2[2U] = __Vdly__v__DOT__mul_inst__DOT__mul_res2[2U];
    vlTOPp->v__DOT__mul_inst__DOT__mul_res2[3U] = __Vdly__v__DOT__mul_inst__DOT__mul_res2[3U];
    vlTOPp->v__DOT__mul_inst__DOT__mul_res3[0U] = __Vdly__v__DOT__mul_inst__DOT__mul_res3[0U];
    vlTOPp->v__DOT__mul_inst__DOT__mul_res3[1U] = __Vdly__v__DOT__mul_inst__DOT__mul_res3[1U];
    vlTOPp->v__DOT__mul_inst__DOT__mul_res3[2U] = __Vdly__v__DOT__mul_inst__DOT__mul_res3[2U];
    vlTOPp->v__DOT__mul_inst__DOT__mul_res3[3U] = __Vdly__v__DOT__mul_inst__DOT__mul_res3[3U];
    vlTOPp->v__DOT__mul_inst__DOT__sub_res1 = __Vdly__v__DOT__mul_inst__DOT__sub_res1;
    vlTOPp->v__DOT__mul_inst__DOT__sub_res2 = __Vdly__v__DOT__mul_inst__DOT__sub_res2;
    vlTOPp->v__DOT__mul_inst__DOT__a_high = __Vdly__v__DOT__mul_inst__DOT__a_high;
    vlTOPp->v__DOT__mul_inst__DOT__b_high = __Vdly__v__DOT__mul_inst__DOT__b_high;
    vlTOPp->v__DOT__mul_inst__DOT__a_low = __Vdly__v__DOT__mul_inst__DOT__a_low;
    vlTOPp->v__DOT__mul_inst__DOT__b_low = __Vdly__v__DOT__mul_inst__DOT__b_low;
    vlTOPp->v__DOT__mul_inst__DOT__valid_pipe = __Vdly__v__DOT__mul_inst__DOT__valid_pipe;
    vlTOPp->v__DOT__arbiter_inst__DOT__req = ((4U & 
					       ((IData)(vlTOPp->v__DOT__mul_inst__DOT__valid_pipe) 
						>> 1U)) 
					      | (((IData)(vlTOPp->v__DOT__sub_res_valid) 
						  << 1U) 
						 | (IData)(vlTOPp->v__DOT__add_res_valid)));
}

void Vcalculator::_settle__TOP__2(Vcalculator__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    Vcalculator::_settle__TOP__2\n"); );
    Vcalculator* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->v__DOT__arbiter_inst__DOT__req = ((4U & 
					       ((IData)(vlTOPp->v__DOT__mul_inst__DOT__valid_pipe) 
						>> 1U)) 
					      | (((IData)(vlTOPp->v__DOT__sub_res_valid) 
						  << 1U) 
						 | (IData)(vlTOPp->v__DOT__add_res_valid)));
    vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__mask_pre 
	= ((IData)(vlTOPp->v__DOT__arbiter_inst__DOT__req) 
	   & (~ (((IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__pre_req) 
		  - (IData)(1U)) | (IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__pre_req))));
}

VL_INLINE_OPT void Vcalculator::_sequent__TOP__3(Vcalculator__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    Vcalculator::_sequent__TOP__3\n"); );
    Vcalculator* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__mask_pre 
	= ((IData)(vlTOPp->v__DOT__arbiter_inst__DOT__req) 
	   & (~ (((IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__pre_req) 
		  - (IData)(1U)) | (IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__pre_req))));
    // ALWAYS at arbiter_engine.sv:51
    vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__win 
	= ((0U != (IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__mask_pre))
	    ? ((IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__mask_pre) 
	       & ((IData)(1U) + (~ (IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__mask_pre))))
	    : ((IData)(vlTOPp->v__DOT__arbiter_inst__DOT__req) 
	       & ((IData)(1U) + (~ (IData)(vlTOPp->v__DOT__arbiter_inst__DOT__req)))));
}

void Vcalculator::_settle__TOP__4(Vcalculator__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    Vcalculator::_settle__TOP__4\n"); );
    Vcalculator* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // ALWAYS at arbiter_engine.sv:51
    vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__win 
	= ((0U != (IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__mask_pre))
	    ? ((IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__mask_pre) 
	       & ((IData)(1U) + (~ (IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__mask_pre))))
	    : ((IData)(vlTOPp->v__DOT__arbiter_inst__DOT__req) 
	       & ((IData)(1U) + (~ (IData)(vlTOPp->v__DOT__arbiter_inst__DOT__req)))));
    vlTOPp->result_valid = (1U & (((IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__win) 
				   | ((IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__win) 
				      >> 1U)) | ((IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__win) 
						 >> 2U)));
    vlTOPp->result_unit = vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__win;
    vlTOPp->result = ((1U == (IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__win))
		       ? vlTOPp->v__DOT__add_result
		       : ((2U == (IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__win))
			   ? vlTOPp->v__DOT__sub_result
			   : ((4U == (IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__win))
			       ? (((QData)((IData)(
						   vlTOPp->v__DOT__mul_inst__DOT__add_result[1U])) 
				   << 0x20U) | (QData)((IData)(
							       vlTOPp->v__DOT__mul_inst__DOT__add_result[0U])))
			       : VL_ULL(0))));
    vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_ready 
	= ((IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__win) 
	   & (((IData)(vlTOPp->result_ack) << 2U) | 
	      (((IData)(vlTOPp->result_ack) << 1U) 
	       | (IData)(vlTOPp->result_ack))));
}

VL_INLINE_OPT void Vcalculator::_sequent__TOP__5(Vcalculator__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    Vcalculator::_sequent__TOP__5\n"); );
    Vcalculator* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->result_valid = (1U & (((IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__win) 
				   | ((IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__win) 
				      >> 1U)) | ((IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__win) 
						 >> 2U)));
    vlTOPp->result_unit = vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__win;
    vlTOPp->result = ((1U == (IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__win))
		       ? vlTOPp->v__DOT__add_result
		       : ((2U == (IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__win))
			   ? vlTOPp->v__DOT__sub_result
			   : ((4U == (IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__win))
			       ? (((QData)((IData)(
						   vlTOPp->v__DOT__mul_inst__DOT__add_result[1U])) 
				   << 0x20U) | (QData)((IData)(
							       vlTOPp->v__DOT__mul_inst__DOT__add_result[0U])))
			       : VL_ULL(0))));
}

VL_INLINE_OPT void Vcalculator::_combo__TOP__6(Vcalculator__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    Vcalculator::_combo__TOP__6\n"); );
    Vcalculator* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_ready 
	= ((IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__win) 
	   & (((IData)(vlTOPp->result_ack) << 2U) | 
	      (((IData)(vlTOPp->result_ack) << 1U) 
	       | (IData)(vlTOPp->result_ack))));
    vlTOPp->add_ack = ((IData)(vlTOPp->add_valid) & (IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_ready));
    vlTOPp->sub_ack = ((IData)(vlTOPp->sub_valid) & 
		       ((IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_ready) 
			>> 1U));
    vlTOPp->v__DOT__mul_inst__DOT__run_pipeline = (1U 
						   & (((IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_ready) 
						       >> 2U) 
						      | (~ 
							 ((IData)(vlTOPp->v__DOT__mul_inst__DOT__valid_pipe) 
							  >> 3U))));
}

void Vcalculator::_settle__TOP__7(Vcalculator__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    Vcalculator::_settle__TOP__7\n"); );
    Vcalculator* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->add_ack = ((IData)(vlTOPp->add_valid) & (IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_ready));
    vlTOPp->sub_ack = ((IData)(vlTOPp->sub_valid) & 
		       ((IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_ready) 
			>> 1U));
    vlTOPp->v__DOT__mul_inst__DOT__run_pipeline = (1U 
						   & (((IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_ready) 
						       >> 2U) 
						      | (~ 
							 ((IData)(vlTOPp->v__DOT__mul_inst__DOT__valid_pipe) 
							  >> 3U))));
    vlTOPp->mul_ack = ((IData)(vlTOPp->v__DOT__mul_inst__DOT__valid_pipe) 
		       & (IData)(vlTOPp->v__DOT__mul_inst__DOT__run_pipeline));
}

VL_INLINE_OPT void Vcalculator::_combo__TOP__8(Vcalculator__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    Vcalculator::_combo__TOP__8\n"); );
    Vcalculator* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mul_ack = ((IData)(vlTOPp->v__DOT__mul_inst__DOT__valid_pipe) 
		       & (IData)(vlTOPp->v__DOT__mul_inst__DOT__run_pipeline));
}

void Vcalculator::_eval(Vcalculator__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    Vcalculator::_eval\n"); );
    Vcalculator* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk))) 
	 | ((~ (IData)(vlTOPp->rst_n)) & (IData)(vlTOPp->__Vclklast__TOP__rst_n)))) {
	vlTOPp->_sequent__TOP__1(vlSymsp);
	vlTOPp->__Vm_traceActivity = (2U | vlTOPp->__Vm_traceActivity);
	vlTOPp->_sequent__TOP__3(vlSymsp);
	vlTOPp->_sequent__TOP__5(vlSymsp);
    }
    vlTOPp->_combo__TOP__6(vlSymsp);
    vlTOPp->__Vm_traceActivity = (4U | vlTOPp->__Vm_traceActivity);
    vlTOPp->_combo__TOP__8(vlSymsp);
    // Final
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
    vlTOPp->__Vclklast__TOP__rst_n = vlTOPp->rst_n;
}

void Vcalculator::_eval_initial(Vcalculator__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    Vcalculator::_eval_initial\n"); );
    Vcalculator* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vcalculator::final() {
    VL_DEBUG_IF(VL_PRINTF("    Vcalculator::final\n"); );
    // Variables
    Vcalculator__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vcalculator* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vcalculator::_eval_settle(Vcalculator__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    Vcalculator::_eval_settle\n"); );
    Vcalculator* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__2(vlSymsp);
    vlTOPp->__Vm_traceActivity = (1U | vlTOPp->__Vm_traceActivity);
    vlTOPp->_settle__TOP__4(vlSymsp);
    vlTOPp->_settle__TOP__7(vlSymsp);
}

VL_INLINE_OPT QData Vcalculator::_change_request(Vcalculator__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    Vcalculator::_change_request\n"); );
    Vcalculator* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}
