//This is a test for Swarm64 Hardware Design Exercise
//It tests design, which includes three arithmetic units (addition, subtraction and multiplication) and arbiter module,  
//which selects between outputs of these modules.
// Test checks the correctness of data in case of random stimuli and also estimates the throughput. 
//Fairness* of the arbiter can be estimated from the ratio between different types of answers. 
//
//
//*Note that the number of multiplication answers is a little bit higher due to the pipeline.
//

#include "verilated_vcd_c.h"
#include "Vcalculator.h"
#include <random>
#include <iostream>
#include <queue>
#include <time.h> 
#include <limits.h>
using namespace std;

//defines
#define TIMEOUT 3 		// no responses got before timeout CRITICAL_NUM_CYCLES
#define MUL_V  	2		//data error
#define SUB_V  	1		//data error
#define ADD_V  	0		//data error



#define PS_MUL 4 		//pipeline length for mul module
#define PS_ADD 1		//pipeline length for add module
#define PS_SUB 1		//pipeline length for sub module


// constants
const int WIDTH = 64;
const int NUM_CYCLES = 300000;
const int NUM_CYCLES_THROUGHPUT = 10000;
const int CRITICAL_NUM_CYCLES=2*NUM_CYCLES;

// device under test
Vcalculator* dut = nullptr;

// time
int main_time = 0;
void check_throuput(VerilatedVcdC & v);

// entrypoint
int main(int argc, char* argv[]) {

	// user defined
	bool run[3];
	unsigned int cnt_add=0,cnt_sub=0,cnt_mul=0;
	unsigned int got_add=0,got_sub=0,got_mul=0;
	unsigned int err_code=0;
	bool flag_add=0, flag_sub=0,flag_mul=0;
	bool flag_end=0;
	bool flag_bad_end=0;
	bool checked_addmax1=0,checked_addmax2=0,checked_submax1=0,checked_submax2=0,checked_mulmax1=0,checked_mulmax2=0;
	uint64_t res_mul=0;
	uint64_t res_add=0;
	uint64_t res_sub=0;
	queue<uint64_t> mulqueue;
	queue<uint64_t> subqueue;
	queue<uint64_t> addqueue;	

    // initialize verilator
    Verilated::commandArgs(argc, argv);

    // 64-bit rngom generator
    std::mt19937_64 rng(time(NULL));//(0xbeefbabebaadf00dULL);

    // instantiate dut
    dut = new Vcalculator();

    // start trace
    Verilated::traceEverOn(true);
    VerilatedVcdC tfp;
    dut->trace(&tfp, 99);
    tfp.open("simx.vcd");

    // reset
    dut->clk = 0;
    dut->rst_n = 0;
    dut->eval();
    tfp.dump(main_time++);
    tfp.dump(main_time++);
    dut->rst_n = 1;
    dut->eval();
    tfp.dump(main_time++);
    tfp.dump(main_time++);
	
	
	for (int i =0; i<3; i++)
		run[i]=1;

	check_throuput(tfp);
	
	
	cout<<"Checking with randomized stimuli. Checking for data correctness and number of answers........."<<endl;
    // main loop
    dut->clk = 1;
	
	unsigned int local_time=0;
	
    while (!(flag_bad_end)&&!(flag_end && (subqueue.size()==0) && (addqueue.size()==0) && (mulqueue.size()==0))) { // just to make sure that all requests will be answered
		flag_end=local_time/4 >= NUM_CYCLES;					// stop sending requests when time is over
		flag_bad_end =local_time/4 >= CRITICAL_NUM_CYCLES;  // if waiting  for answers to requests takes too long...
		
		local_time+=4;
	
	  // clock posedge
        dut->clk = 1;
        
        // timestep
        dut->eval();
        tfp.dump(main_time++);

        dut->result_ack = rng()%2 && dut->result_valid;
				
		if (dut->result_ack && dut->result_unit==1) {
			got_add+=1;
			res_add=addqueue.front();
			flag_add=(dut->result!=res_add); 					// compare results
			addqueue.pop();
			//cout<<"!!!! + exp "<<dut->result<<" theory "<<res_add<<endl;
			}
        if (dut->result_ack && dut->result_unit==2) {
			got_sub+=1;
			res_sub=subqueue.front();
			flag_sub=(dut->result!=res_sub);					// compare results
			subqueue.pop();
			//cout<<"!!!! - exp "<<dut->result<<" theory "<<res_sub<<endl;
		}
        if (dut->result_ack && dut->result_unit==4) {
			got_mul+=1;
			res_mul=mulqueue.front();
			flag_mul=(dut->result!=res_mul);					// compare results
			mulqueue.pop();
			//cout<<"!!!! * exp "<<dut->result<<" theory "<<res_mul<<endl;
		}

        // timestep
        dut->eval();
        tfp.dump(main_time++);
	
        // clock negedge
        dut->clk = 0;

        // timestep
        dut->eval();
        tfp.dump(main_time++);
		
		run[0]=dut->add_ack | (not dut->add_valid);				// change input only if ack asserted
		run[1]=dut->sub_ack | (not dut->sub_valid);				
		run[2]=dut->mul_ack | (not dut->mul_valid);				
				
		    // apply inputs
		if (run[0]){
		
			dut->add_valid = rng()%2  && (!flag_end); // stop sending requests when time is over

			dut->add_a = (!checked_addmax1) ? ULLONG_MAX : rng();						//first check max values then random
			dut->add_b = (!checked_addmax1) ? rng() : (!checked_addmax2) ? ULLONG_MAX :  rng(); 			
			if (checked_addmax1 && dut->add_valid) 	checked_addmax2=1;
			if (dut->add_valid)						checked_addmax1=1;
			
			cnt_add+=dut->add_valid;
			
			if (dut->add_valid){					//if value to be sent, then push it into queue
			addqueue.push(dut->add_a+dut->add_b);
			//cout<<"theory req add "<<dut->add_a<<" "<<dut->add_b<<endl;
			}
			}
			
			
		if (run[1]){

			dut->sub_valid = rng()%2  && (!flag_end); // stop sending requests when time is over

			dut->sub_a = (!checked_submax1) ? ULLONG_MAX : rng();								//first check max values then random
			dut->sub_b = (!checked_submax1) ? rng() : (!checked_submax2) ? ULLONG_MAX : rng() ; 								 
			if (checked_submax1 && dut->sub_valid) checked_submax2=1;
			if (dut->sub_valid)					   checked_submax1=1;
			
			cnt_sub+=dut->sub_valid;
			
			if (dut->sub_valid){
			subqueue.push(dut->sub_a-dut->sub_b); 					//if value to be sent, then push it into queue
			//cout<<"theory req  sub "<<dut->sub_a<<" "<<dut->sub_b<<endl;
			}
		}
		
		
		if(run[2]){

			dut->mul_valid = rng()%2  &&  (!flag_end); // stop sending requests when time is over

			dut->mul_a = (!checked_mulmax1) ? ULLONG_MAX : rng();									//first check max values then random
			dut->mul_b = (!checked_mulmax1) ? rng() : (!checked_mulmax2) ?  ULLONG_MAX : rng(); 						
			if (checked_mulmax1 && dut->add_valid) checked_mulmax2=1;
			if(dut->add_valid)	 checked_mulmax1=1;
			
			cnt_mul+=dut->mul_valid; 
						
			if (dut->mul_valid){
			mulqueue.push(dut->mul_a*dut->mul_b);				//if value to be sent, then push it into queue
			//cout<<"theory req  mul "<<dut->mul_a<<" "<<dut->mul_b<<endl;
			}
		}
		    
	     // timestep
        dut->eval();
        tfp.dump(main_time++);	
		
		
/// Checks		

			
		if (flag_add) 						err_code=1<<ADD_V;
		if (flag_sub) 						err_code=1<<SUB_V;
		if (flag_mul) 						err_code=1<<MUL_V;
		if (flag_bad_end)					err_code=1<<TIMEOUT;
	
		if (err_code){
			cout<<endl<<endl<<"Error Exiting..."<<endl<<"Error code is 0x"<<hex<<err_code<<endl;
			break;
		}
	
    }
    dut->final();
	
	
	cout<<endl<<endl<<"+ requests num is "<<dec<<cnt_add<<" "<<"response num is "<<dec<<got_add<<endl<<endl;
	cout<<"- requests num is "<<dec<<cnt_sub<<" "<<"response num is "<<dec<<got_sub<<endl<<endl;
	cout<<"* requests num is "<<dec<<cnt_mul<<" "<<"response num is "<<dec<<got_mul<<endl<<endl;

    // report pass or fail
    if (!err_code) {
		cout<<endl<<"Ratio + : - : * \t 1:"<<(float)cnt_sub/cnt_add<<":"<<(float)cnt_mul/cnt_add<<endl;	
        cout <<"\n\t\t\tPASS. Congratulations!!!\n" << endl;
        return 0;
    } else {
        cout << "\n\t\t\tFAIL. Have a look at error codes for details\n" << endl;
        return 1;
    }
}


void check_throuput(VerilatedVcdC & v){ // here we don't care about the data, which we send and accept
	cout<<" Checking througput........."<<endl;
		bool run[3];
		bool flag_end=0;
		bool req_add=0, req_sub=0, req_mul=0;
		unsigned int got_add=0, got_sub=0, got_mul=0;
		unsigned int cnt_add=0, cnt_sub=0, cnt_mul=0;
		unsigned int local_time;
					
		dut->add_a = 0;						
		dut->add_b = 0; 			
						
		dut->sub_a = 0;						
		dut->sub_b = 0;

		dut->mul_a = 0;						
		dut->mul_b = 0; 		
	
	    for (int i =0; i< 8; i++){
		
			got_add=0; got_sub=0; got_mul=0;
							
			req_add=(i==0) ? 1: (i==3) ? 1 : (i==4) ? 1 : (i==6) ? 1 : 0;
			req_sub=(i==1) ? 1: (i==3) ? 1 : (i==5) ? 1 : (i==6) ? 1 : 0;
			req_mul=(i==2) ? 1: (i==4) ? 1 : (i==5) ? 1 : (i==6) ? 1 : 0;
			
			local_time=0;
			flag_end=0;
				
		
			while (!flag_end ) { 
					flag_end=local_time/4 >= NUM_CYCLES_THROUGHPUT;					// stop sending requests when time is over
					local_time+=4; 
				
				// clock posedge
					dut->clk = 1;
					
					// timestep
					dut->eval();
					v.dump(main_time++);
						
					dut->result_ack = 1 && dut->result_valid;
										
					if (dut->result_ack && dut->result_unit==1) {
						got_add+=1;
						}
					if (dut->result_ack && dut->result_unit==2) {
						got_sub+=1;
					}
					if (dut->result_ack && dut->result_unit==4) {
						got_mul+=1;
					}			
			
					// timestep
					dut->eval();
					v.dump(main_time++);
				
			
					// clock negedge
					dut->clk = 0;
			
					// timestep
					dut->eval();
					v.dump(main_time++);
					
					run[0]=dut->add_ack | (not dut->add_valid);				// change input only if ack asserted
					run[1]=dut->sub_ack | (not dut->sub_valid);				
					run[2]=dut->mul_ack | (not dut->mul_valid);				
										
						// apply inputs
					if (run[0]){
						dut->add_valid = req_add  && (!flag_end); // stop sending requests when time is over
						cnt_add+=dut->add_valid;		
						}
										
					if (run[1]){
						dut->sub_valid = req_sub  && (!flag_end); // stop sending requests when time is over
						cnt_sub+=dut->sub_valid;
					}
					
					if(run[2]){
						dut->mul_valid =  req_mul &&  (!flag_end); // stop sending requests when time is over
						cnt_mul+=dut->mul_valid; 
					}
					// timestep
					dut->eval();
					v.dump(main_time++);						
					
				}
			
			cout<<((i<3)?"Single request asserted " :(i<6) ?"Two requests asserted" :(i==6) ? "Three requests asserted" : "")<<endl;
			if (req_add)  cout<<"\t"<<"ADD throughput  is "<<(float)got_add/NUM_CYCLES_THROUGHPUT<<endl;
			if (req_sub)  cout<<"\t"<<"SUB throughput  is "<<(float)got_sub/NUM_CYCLES_THROUGHPUT<<endl;
			if (req_mul)  cout<<"\t"<<"MUL throughput  is "<<(float)got_mul/NUM_CYCLES_THROUGHPUT<<endl;
			cout<<endl<<endl;
	
	}
	
	
	
	
}

