// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vcalculator__Syms.h"


//======================

void Vcalculator::trace (VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addCallback (&Vcalculator::traceInit, &Vcalculator::traceFull, &Vcalculator::traceChg, this);
}
void Vcalculator::traceInit(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->open()
    Vcalculator* t=(Vcalculator*)userthis;
    Vcalculator__Syms* __restrict vlSymsp = t->__VlSymsp; // Setup global symbol table
    if (!Verilated::calcUnusedSigs()) vl_fatal(__FILE__,__LINE__,__FILE__,"Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    vcdp->scopeEscape(' ');
    t->traceInitThis (vlSymsp, vcdp, code);
    vcdp->scopeEscape('.');
}
void Vcalculator::traceFull(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->dump()
    Vcalculator* t=(Vcalculator*)userthis;
    Vcalculator__Syms* __restrict vlSymsp = t->__VlSymsp; // Setup global symbol table
    t->traceFullThis (vlSymsp, vcdp, code);
}

//======================


void Vcalculator::traceInitThis(Vcalculator__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vcalculator* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    vcdp->module(vlSymsp->name()); // Setup signal names
    // Body
    {
	vlTOPp->traceInitThis__1(vlSymsp, vcdp, code);
    }
}

void Vcalculator::traceFullThis(Vcalculator__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vcalculator* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vlTOPp->traceFullThis__1(vlSymsp, vcdp, code);
    }
    // Final
    vlTOPp->__Vm_traceActivity = 0U;
}

void Vcalculator::traceInitThis__1(Vcalculator__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vcalculator* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->declBit  (c+66,"clk",-1);
	vcdp->declBit  (c+67,"rst_n",-1);
	vcdp->declBit  (c+68,"add_valid",-1);
	vcdp->declBit  (c+69,"add_ack",-1);
	vcdp->declQuad (c+70,"add_a",-1,63,0);
	vcdp->declQuad (c+72,"add_b",-1,63,0);
	vcdp->declBit  (c+74,"sub_valid",-1);
	vcdp->declBit  (c+75,"sub_ack",-1);
	vcdp->declQuad (c+76,"sub_a",-1,63,0);
	vcdp->declQuad (c+78,"sub_b",-1,63,0);
	vcdp->declBit  (c+80,"mul_valid",-1);
	vcdp->declBit  (c+81,"mul_ack",-1);
	vcdp->declQuad (c+82,"mul_a",-1,63,0);
	vcdp->declQuad (c+84,"mul_b",-1,63,0);
	vcdp->declBit  (c+86,"result_valid",-1);
	vcdp->declBit  (c+87,"result_ack",-1);
	vcdp->declBus  (c+88,"result_unit",-1,2,0);
	vcdp->declQuad (c+89,"result",-1,63,0);
	vcdp->declBit  (c+66,"v clk",-1);
	vcdp->declBit  (c+67,"v rst_n",-1);
	vcdp->declBit  (c+68,"v add_valid",-1);
	vcdp->declBit  (c+69,"v add_ack",-1);
	vcdp->declQuad (c+70,"v add_a",-1,63,0);
	vcdp->declQuad (c+72,"v add_b",-1,63,0);
	vcdp->declBit  (c+74,"v sub_valid",-1);
	vcdp->declBit  (c+75,"v sub_ack",-1);
	vcdp->declQuad (c+76,"v sub_a",-1,63,0);
	vcdp->declQuad (c+78,"v sub_b",-1,63,0);
	vcdp->declBit  (c+80,"v mul_valid",-1);
	vcdp->declBit  (c+81,"v mul_ack",-1);
	vcdp->declQuad (c+82,"v mul_a",-1,63,0);
	vcdp->declQuad (c+84,"v mul_b",-1,63,0);
	vcdp->declBit  (c+86,"v result_valid",-1);
	vcdp->declBit  (c+87,"v result_ack",-1);
	vcdp->declBus  (c+88,"v result_unit",-1,2,0);
	vcdp->declQuad (c+89,"v result",-1,63,0);
	vcdp->declBus  (c+95,"v WIDTH",-1,31,0);
	vcdp->declBit  (c+8,"v add_res_ready",-1);
	vcdp->declQuad (c+13,"v add_result",-1,63,0);
	vcdp->declBit  (c+15,"v add_res_valid",-1);
	vcdp->declBit  (c+9,"v sub_res_ready",-1);
	vcdp->declQuad (c+16,"v sub_result",-1,63,0);
	vcdp->declBit  (c+18,"v sub_res_valid",-1);
	vcdp->declBit  (c+10,"v mul_res_ready",-1);
	vcdp->declQuad (c+19,"v mul_result",-1,63,0);
	vcdp->declBit  (c+21,"v mul_res_valid",-1);
	vcdp->declBus  (c+95,"v add_inst WIDTH",-1,31,0);
	vcdp->declBit  (c+66,"v add_inst clk",-1);
	vcdp->declBit  (c+67,"v add_inst rst_n",-1);
	vcdp->declBit  (c+68,"v add_inst add_valid",-1);
	vcdp->declBit  (c+69,"v add_inst add_ack",-1);
	vcdp->declQuad (c+70,"v add_inst add_a",-1,63,0);
	vcdp->declQuad (c+72,"v add_inst add_b",-1,63,0);
	vcdp->declQuad (c+13,"v add_inst add_result",-1,63,0);
	vcdp->declBit  (c+15,"v add_inst add_res_valid",-1);
	vcdp->declBit  (c+8,"v add_inst add_res_ready",-1);
	vcdp->declBus  (c+95,"v sub_inst WIDTH",-1,31,0);
	vcdp->declBit  (c+66,"v sub_inst clk",-1);
	vcdp->declBit  (c+67,"v sub_inst rst_n",-1);
	vcdp->declBit  (c+74,"v sub_inst sub_valid",-1);
	vcdp->declBit  (c+75,"v sub_inst sub_ack",-1);
	vcdp->declQuad (c+76,"v sub_inst sub_a",-1,63,0);
	vcdp->declQuad (c+78,"v sub_inst sub_b",-1,63,0);
	vcdp->declQuad (c+16,"v sub_inst sub_result",-1,63,0);
	vcdp->declBit  (c+18,"v sub_inst sub_res_valid",-1);
	vcdp->declBit  (c+9,"v sub_inst sub_res_ready",-1);
	vcdp->declBus  (c+95,"v mul_inst WIDTH",-1,31,0);
	vcdp->declBit  (c+66,"v mul_inst clk",-1);
	vcdp->declBit  (c+67,"v mul_inst rst_n",-1);
	vcdp->declBit  (c+80,"v mul_inst mul_valid",-1);
	vcdp->declBit  (c+81,"v mul_inst mul_ack",-1);
	vcdp->declQuad (c+82,"v mul_inst mul_a",-1,63,0);
	vcdp->declQuad (c+84,"v mul_inst mul_b",-1,63,0);
	vcdp->declQuad (c+19,"v mul_inst mul_result",-1,63,0);
	vcdp->declBit  (c+21,"v mul_inst mul_res_valid",-1);
	vcdp->declBit  (c+10,"v mul_inst mul_res_ready",-1);
	vcdp->declBus  (c+95,"v mul_inst SIZE",-1,31,0);
	vcdp->declBus  (c+96,"v mul_inst DSIZE",-1,31,0);
	vcdp->declBus  (c+97,"v mul_inst HSIZE",-1,31,0);
	vcdp->declBus  (c+98,"v mul_inst b2b",-1,31,0);
	vcdp->declBus  (c+97,"v mul_inst b",-1,31,0);
	vcdp->declBus  (c+99,"v mul_inst b1",-1,31,0);
	vcdp->declBus  (c+22,"v mul_inst a_high",-1,31,0);
	vcdp->declBus  (c+23,"v mul_inst a_low",-1,31,0);
	vcdp->declBus  (c+91,"v mul_inst a_high_",-1,31,0);
	vcdp->declBus  (c+92,"v mul_inst a_low_",-1,31,0);
	vcdp->declBus  (c+24,"v mul_inst b_high",-1,31,0);
	vcdp->declBus  (c+25,"v mul_inst b_low",-1,31,0);
	vcdp->declBus  (c+93,"v mul_inst b_high_",-1,31,0);
	vcdp->declBus  (c+94,"v mul_inst b_low_",-1,31,0);
	vcdp->declArray(c+26,"v mul_inst mul_res1",-1,127,0);
	vcdp->declArray(c+30,"v mul_inst mul_res2",-1,127,0);
	vcdp->declArray(c+34,"v mul_inst mul_res3",-1,127,0);
	vcdp->declArray(c+38,"v mul_inst mul_res4",-1,127,0);
	vcdp->declArray(c+42,"v mul_inst mul_res5",-1,127,0);
	vcdp->declArray(c+46,"v mul_inst mul_res6",-1,127,0);
	vcdp->declArray(c+50,"v mul_inst mul_res7",-1,127,0);
	vcdp->declArray(c+54,"v mul_inst keep_res",-1,127,0);
	vcdp->declArray(c+58,"v mul_inst add_result",-1,127,0);
	vcdp->declBus  (c+62,"v mul_inst sub_res1",-1,31,0);
	vcdp->declBus  (c+63,"v mul_inst sub_res2",-1,31,0);
	vcdp->declBus  (c+64,"v mul_inst valid_pipe",-1,3,0);
	vcdp->declBit  (c+11,"v mul_inst run_pipeline",-1);
	vcdp->declBus  (c+95,"v arbiter_inst WIDTH",-1,31,0);
	vcdp->declBit  (c+67,"v arbiter_inst rst_n",-1);
	vcdp->declBit  (c+66,"v arbiter_inst clk",-1);
	vcdp->declQuad (c+13,"v arbiter_inst a",-1,63,0);
	vcdp->declBit  (c+15,"v arbiter_inst a_valid",-1);
	vcdp->declBit  (c+8,"v arbiter_inst a_ready",-1);
	vcdp->declQuad (c+16,"v arbiter_inst b",-1,63,0);
	vcdp->declBit  (c+18,"v arbiter_inst b_valid",-1);
	vcdp->declBit  (c+9,"v arbiter_inst b_ready",-1);
	vcdp->declQuad (c+19,"v arbiter_inst c",-1,63,0);
	vcdp->declBit  (c+21,"v arbiter_inst c_valid",-1);
	vcdp->declBit  (c+10,"v arbiter_inst c_ready",-1);
	vcdp->declQuad (c+89,"v arbiter_inst result",-1,63,0);
	vcdp->declBit  (c+86,"v arbiter_inst result_valid",-1);
	vcdp->declBus  (c+88,"v arbiter_inst result_unit",-1,2,0);
	vcdp->declBit  (c+87,"v arbiter_inst result_ack",-1);
	vcdp->declBus  (c+1,"v arbiter_inst req",-1,2,0);
	vcdp->declBus  (c+2,"v arbiter_inst grant",-1,2,0);
	vcdp->declBus  (c+12,"v arbiter_inst arbiter_ready",-1,2,0);
	vcdp->declQuad (c+3,"v arbiter_inst result_",-1,63,0);
	vcdp->declBit  (c+67,"v arbiter_inst arbiter_engine_inst rst_n",-1);
	vcdp->declBit  (c+66,"v arbiter_inst arbiter_engine_inst clk",-1);
	vcdp->declBus  (c+1,"v arbiter_inst arbiter_engine_inst req",-1,2,0);
	vcdp->declBus  (c+2,"v arbiter_inst arbiter_engine_inst grant",-1,2,0);
	vcdp->declBus  (c+2,"v arbiter_inst arbiter_engine_inst grant_q",-1,2,0);
	vcdp->declBus  (c+65,"v arbiter_inst arbiter_engine_inst pre_req",-1,2,0);
	vcdp->declBus  (c+5,"v arbiter_inst arbiter_engine_inst sel_gnt",-1,2,0);
	vcdp->declBus  (c+6,"v arbiter_inst arbiter_engine_inst isol_lsb",-1,2,0);
	vcdp->declBus  (c+7,"v arbiter_inst arbiter_engine_inst mask_pre",-1,2,0);
	vcdp->declBus  (c+2,"v arbiter_inst arbiter_engine_inst win",-1,2,0);
    }
}

void Vcalculator::traceFullThis__1(Vcalculator__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vcalculator* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->fullBus  (c+1,(vlTOPp->v__DOT__arbiter_inst__DOT__req),3);
	vcdp->fullQuad (c+3,(((1U == (IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__win))
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
	vcdp->fullBus  (c+5,(((IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__mask_pre) 
			      & ((IData)(1U) + (~ (IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__mask_pre))))),3);
	vcdp->fullBus  (c+6,(((IData)(vlTOPp->v__DOT__arbiter_inst__DOT__req) 
			      & ((IData)(1U) + (~ (IData)(vlTOPp->v__DOT__arbiter_inst__DOT__req))))),3);
	vcdp->fullBus  (c+7,(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__mask_pre),3);
	vcdp->fullBus  (c+2,(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__win),3);
	vcdp->fullBit  (c+11,(vlTOPp->v__DOT__mul_inst__DOT__run_pipeline));
	vcdp->fullBit  (c+8,((1U & (IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_ready))));
	vcdp->fullBit  (c+9,((1U & ((IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_ready) 
				    >> 1U))));
	vcdp->fullBit  (c+10,((1U & ((IData)(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_ready) 
				     >> 2U))));
	vcdp->fullBus  (c+12,(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_ready),3);
	vcdp->fullBus  (c+22,(vlTOPp->v__DOT__mul_inst__DOT__a_high),32);
	vcdp->fullBus  (c+23,(vlTOPp->v__DOT__mul_inst__DOT__a_low),32);
	vcdp->fullBus  (c+24,(vlTOPp->v__DOT__mul_inst__DOT__b_high),32);
	vcdp->fullBus  (c+25,(vlTOPp->v__DOT__mul_inst__DOT__b_low),32);
	vcdp->fullArray(c+26,(vlTOPp->v__DOT__mul_inst__DOT__mul_res1),128);
	vcdp->fullArray(c+30,(vlTOPp->v__DOT__mul_inst__DOT__mul_res2),128);
	vcdp->fullArray(c+34,(vlTOPp->v__DOT__mul_inst__DOT__mul_res3),128);
	vcdp->fullArray(c+38,(vlTOPp->v__DOT__mul_inst__DOT__mul_res4),128);
	vcdp->fullArray(c+42,(vlTOPp->v__DOT__mul_inst__DOT__mul_res5),128);
	vcdp->fullArray(c+46,(vlTOPp->v__DOT__mul_inst__DOT__mul_res6),128);
	vcdp->fullArray(c+50,(vlTOPp->v__DOT__mul_inst__DOT__mul_res7),128);
	vcdp->fullArray(c+54,(vlTOPp->v__DOT__mul_inst__DOT__keep_res),128);
	vcdp->fullArray(c+58,(vlTOPp->v__DOT__mul_inst__DOT__add_result),128);
	vcdp->fullBus  (c+62,(vlTOPp->v__DOT__mul_inst__DOT__sub_res1),32);
	vcdp->fullBus  (c+63,(vlTOPp->v__DOT__mul_inst__DOT__sub_res2),32);
	vcdp->fullBus  (c+64,(vlTOPp->v__DOT__mul_inst__DOT__valid_pipe),4);
	vcdp->fullQuad (c+13,(vlTOPp->v__DOT__add_result),64);
	vcdp->fullBit  (c+15,(vlTOPp->v__DOT__add_res_valid));
	vcdp->fullQuad (c+16,(vlTOPp->v__DOT__sub_result),64);
	vcdp->fullBit  (c+18,(vlTOPp->v__DOT__sub_res_valid));
	vcdp->fullQuad (c+19,((((QData)((IData)(vlTOPp->v__DOT__mul_inst__DOT__add_result[1U])) 
				<< 0x20U) | (QData)((IData)(
							    vlTOPp->v__DOT__mul_inst__DOT__add_result[0U])))),64);
	vcdp->fullBit  (c+21,((1U & ((IData)(vlTOPp->v__DOT__mul_inst__DOT__valid_pipe) 
				     >> 3U))));
	vcdp->fullBus  (c+65,(vlTOPp->v__DOT__arbiter_inst__DOT__arbiter_engine_inst__DOT__pre_req),3);
	vcdp->fullBit  (c+68,(vlTOPp->add_valid));
	vcdp->fullBit  (c+69,(vlTOPp->add_ack));
	vcdp->fullQuad (c+70,(vlTOPp->add_a),64);
	vcdp->fullQuad (c+72,(vlTOPp->add_b),64);
	vcdp->fullBit  (c+74,(vlTOPp->sub_valid));
	vcdp->fullBit  (c+75,(vlTOPp->sub_ack));
	vcdp->fullQuad (c+76,(vlTOPp->sub_a),64);
	vcdp->fullQuad (c+78,(vlTOPp->sub_b),64);
	vcdp->fullBit  (c+80,(vlTOPp->mul_valid));
	vcdp->fullBit  (c+81,(vlTOPp->mul_ack));
	vcdp->fullQuad (c+82,(vlTOPp->mul_a),64);
	vcdp->fullQuad (c+84,(vlTOPp->mul_b),64);
	vcdp->fullBus  (c+91,((IData)((vlTOPp->mul_a 
				       >> 0x20U))),32);
	vcdp->fullBus  (c+92,((IData)(vlTOPp->mul_a)),32);
	vcdp->fullBus  (c+93,((IData)((vlTOPp->mul_b 
				       >> 0x20U))),32);
	vcdp->fullBus  (c+94,((IData)(vlTOPp->mul_b)),32);
	vcdp->fullQuad (c+89,(vlTOPp->result),64);
	vcdp->fullBit  (c+86,(vlTOPp->result_valid));
	vcdp->fullBus  (c+88,(vlTOPp->result_unit),3);
	vcdp->fullBit  (c+87,(vlTOPp->result_ack));
	vcdp->fullBit  (c+67,(vlTOPp->rst_n));
	vcdp->fullBit  (c+66,(vlTOPp->clk));
	vcdp->fullBus  (c+96,(0x80U),32);
	vcdp->fullBus  (c+97,(0x20U),32);
	vcdp->fullBus  (c+98,(0x420U),32);
	vcdp->fullBus  (c+99,(0x21U),32);
	vcdp->fullBus  (c+95,(0x40U),32);
    }
}
