// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vcalculator__Syms.h"


//======================

void Vcalculator::traceChg(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->dump()
    Vcalculator* t=(Vcalculator*)userthis;
    Vcalculator__Syms* __restrict vlSymsp = t->__VlSymsp; // Setup global symbol table
    if (vlSymsp->getClearActivity()) {
	t->traceChgThis (vlSymsp, vcdp, code);
    }
}

//======================


void Vcalculator::traceChgThis(Vcalculator__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vcalculator* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	if (VL_UNLIKELY((1U & (vlTOPp->__Vm_traceActivity 
			       | (vlTOPp->__Vm_traceActivity 
				  >> 1U))))) {
	    vlTOPp->traceChgThis__2(vlSymsp, vcdp, code);
	}
	if (VL_UNLIKELY((1U & (vlTOPp->__Vm_traceActivity 
			       | (vlTOPp->__Vm_traceActivity 
				  >> 2U))))) {
	    vlTOPp->traceChgThis__3(vlSymsp, vcdp, code);
	}
	if (VL_UNLIKELY((2U & vlTOPp->__Vm_traceActivity))) {
	    vlTOPp->traceChgThis__4(vlSymsp, vcdp, code);
	}
	vlTOPp->traceChgThis__5(vlSymsp, vcdp, code);
    }
    // Final
    vlTOPp->__Vm_traceActivity = 0U;
}

void Vcalculator::traceChgThis__2(Vcalculator__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vcalculator* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->chgBus  (c+1,(vlTOPp->v__DOT__arbiter_inst__DOT__req),3);
	vcdp->chgQuad (c+3,(((1U == (IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__win))
			      ? vlTOPp->v__DOT__add_result
			      : ((2U == (IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__win))
				  ? vlTOPp->v__DOT__sub_result
				  : ((4U == (IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__win))
				      ? (((QData)((IData)(
							  vlTOPp->v__DOT__mul_inst__DOT__add_result[1U])) 
					  << 0x20U) 
					 | (QData)((IData)(
							   vlTOPp->v__DOT__mul_inst__DOT__add_result[0U])))
				      : VL_ULL(0))))),64);
	vcdp->chgBus  (c+5,(((IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__mask_pre) 
			     & ((IData)(1U) + (~ (IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__mask_pre))))),3);
	vcdp->chgBus  (c+6,(((IData)(vlTOPp->v__DOT__arbiter_inst__DOT__req) 
			     & ((IData)(1U) + (~ (IData)(vlTOPp->v__DOT__arbiter_inst__DOT__req))))),3);
	vcdp->chgBus  (c+7,(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__mask_pre),3);
	vcdp->chgBus  (c+2,(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__win),3);
    }
}

void Vcalculator::traceChgThis__3(Vcalculator__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vcalculator* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->chgBit  (c+11,(vlTOPp->v__DOT__mul_inst__DOT__run_pipeline));
	vcdp->chgBit  (c+8,((1U & (IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_ready))));
	vcdp->chgBit  (c+9,((1U & ((IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_ready) 
				   >> 1U))));
	vcdp->chgBit  (c+10,((1U & ((IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_ready) 
				    >> 2U))));
	vcdp->chgBus  (c+12,(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_ready),3);
    }
}

void Vcalculator::traceChgThis__4(Vcalculator__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vcalculator* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->chgBus  (c+22,(vlTOPp->v__DOT__mul_inst__DOT__a_high),32);
	vcdp->chgBus  (c+23,(vlTOPp->v__DOT__mul_inst__DOT__a_low),32);
	vcdp->chgBus  (c+24,(vlTOPp->v__DOT__mul_inst__DOT__b_high),32);
	vcdp->chgBus  (c+25,(vlTOPp->v__DOT__mul_inst__DOT__b_low),32);
	vcdp->chgArray(c+26,(vlTOPp->v__DOT__mul_inst__DOT__mul_res1),128);
	vcdp->chgArray(c+30,(vlTOPp->v__DOT__mul_inst__DOT__mul_res2),128);
	vcdp->chgArray(c+34,(vlTOPp->v__DOT__mul_inst__DOT__mul_res3),128);
	vcdp->chgArray(c+38,(vlTOPp->v__DOT__mul_inst__DOT__mul_res4),128);
	vcdp->chgArray(c+42,(vlTOPp->v__DOT__mul_inst__DOT__mul_res5),128);
	vcdp->chgArray(c+46,(vlTOPp->v__DOT__mul_inst__DOT__mul_res6),128);
	vcdp->chgArray(c+50,(vlTOPp->v__DOT__mul_inst__DOT__mul_res7),128);
	vcdp->chgArray(c+54,(vlTOPp->v__DOT__mul_inst__DOT__keep_res),128);
	vcdp->chgArray(c+58,(vlTOPp->v__DOT__mul_inst__DOT__add_result),128);
	vcdp->chgBus  (c+62,(vlTOPp->v__DOT__mul_inst__DOT__sub_res1),32);
	vcdp->chgBus  (c+63,(vlTOPp->v__DOT__mul_inst__DOT__sub_res2),32);
	vcdp->chgBus  (c+64,(vlTOPp->v__DOT__mul_inst__DOT__valid_pipe),4);
	vcdp->chgQuad (c+13,(vlTOPp->v__DOT__add_result),64);
	vcdp->chgBit  (c+15,(vlTOPp->v__DOT__add_res_valid));
	vcdp->chgQuad (c+16,(vlTOPp->v__DOT__sub_result),64);
	vcdp->chgBit  (c+18,(vlTOPp->v__DOT__sub_res_valid));
	vcdp->chgQuad (c+19,((((QData)((IData)(vlTOPp->v__DOT__mul_inst__DOT__add_result[1U])) 
			       << 0x20U) | (QData)((IData)(
							   vlTOPp->v__DOT__mul_inst__DOT__add_result[0U])))),64);
	vcdp->chgBit  (c+21,((1U & ((IData)(vlTOPp->v__DOT__mul_inst__DOT__valid_pipe) 
				    >> 3U))));
	vcdp->chgBus  (c+65,(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__pre_req),3);
    }
}

void Vcalculator::traceChgThis__5(Vcalculator__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vcalculator* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->chgBit  (c+68,(vlTOPp->add_valid));
	vcdp->chgBit  (c+69,(vlTOPp->add_ack));
	vcdp->chgQuad (c+70,(vlTOPp->add_a),64);
	vcdp->chgQuad (c+72,(vlTOPp->add_b),64);
	vcdp->chgBit  (c+74,(vlTOPp->sub_valid));
	vcdp->chgBit  (c+75,(vlTOPp->sub_ack));
	vcdp->chgQuad (c+76,(vlTOPp->sub_a),64);
	vcdp->chgQuad (c+78,(vlTOPp->sub_b),64);
	vcdp->chgBit  (c+80,(vlTOPp->mul_valid));
	vcdp->chgBit  (c+81,(vlTOPp->mul_ack));
	vcdp->chgQuad (c+82,(vlTOPp->mul_a),64);
	vcdp->chgQuad (c+84,(vlTOPp->mul_b),64);
	vcdp->chgBus  (c+91,((IData)((vlTOPp->mul_a 
				      >> 0x20U))),32);
	vcdp->chgBus  (c+92,((IData)(vlTOPp->mul_a)),32);
	vcdp->chgBus  (c+93,((IData)((vlTOPp->mul_b 
				      >> 0x20U))),32);
	vcdp->chgBus  (c+94,((IData)(vlTOPp->mul_b)),32);
	vcdp->chgQuad (c+89,(vlTOPp->result),64);
	vcdp->chgBit  (c+86,(vlTOPp->result_valid));
	vcdp->chgBus  (c+88,(vlTOPp->result_unit),3);
	vcdp->chgBit  (c+87,(vlTOPp->result_ack));
	vcdp->chgBit  (c+67,(vlTOPp->rst_n));
	vcdp->chgBit  (c+66,(vlTOPp->clk));
    }
}
