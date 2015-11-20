#ifndef _RANDMT_H_
#define _RANDMT_H_



#include <cmath>

typedef unsigned long uint32;




class RandMT {

  static const int N =          624;                // length of state vector
  static const int M =          397;                // a period parameter
  static const uint32 K =       0x9908B0DFU;        // a magic constant

  // If you want a single generator, consider using a singleton class 
  // instead of trying to make these static.
  uint32   state[N+1];  // state vector + 1 extra to not violate ANSI C
  uint32   *next;       // next random value is computed from here
  uint32   initseed;    //
  int      left;        // can *next++ this many times before reloading

  inline uint32 hiBit(uint32 u) { 
    return u & 0x80000000U;    // mask all but highest   bit of u
  }

  inline uint32 loBit(uint32 u) { 
    return u & 0x00000001U;    // mask all but lowest    bit of u
  }

  inline uint32 loBits(uint32 u) { 
    return u & 0x7FFFFFFFU;   // mask     the highest   bit of u
  }

  inline uint32 mixBits(uint32 u, uint32 v) {
    return hiBit(u)|loBits(v);  // move hi bit of u to hi bit of v
  }
  
  uint32 reloadMT(void) ;

public:
  RandMT() ;
  RandMT(uint32 seed) ;
  inline uint32 randomMT(void) ; 
  void seedMT(uint32 seed) ;
};






class box_mull { 
RandMT * r1;
RandMT * r2;
public:

	box_mull(uint32 seed1, uint32 seed2){
	this->r1 = new RandMT(seed1);
	this->r2 = new RandMT(seed2); 
	}
	
	void get_rand_vals(float * val1, float * val2);
	
	~box_mull(){
	
	delete r1;
	delete r2;
	
	}

	
	

};










  
  #endif // _RANDMT_H_