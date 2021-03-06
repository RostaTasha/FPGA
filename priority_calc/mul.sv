// the module calculates the result of multiplication of two values
// if BASIC defined the simple variant of module is used. In this case the multiplication is performed in one step and the result is saved to register.
// Otherwise the multiplication is pipelined and performed using Karatsuba algorithm.
//
module mul#(
WIDTH=64
) 
(
    input  logic clk,
    input  logic rst_n,
    input  logic mul_valid,
	output logic mul_ack,
    input  logic [WIDTH-1:0] mul_a,
    input  logic [WIDTH-1:0] mul_b,
	output logic [WIDTH-1:0] mul_result,
	output logic mul_res_valid,
	input  logic mul_res_ready
	
);

//`define BASIC

`ifdef BASIC
	always_ff @(posedge clk or negedge rst_n)
	if (!rst_n) begin
		mul_res_valid<=0;
		mul_result<=0;
	end else begin
		mul_res_valid<= mul_valid;	
		if (mul_valid)
			mul_result<=mul_a*mul_b;		
	end

assign mul_ack=mul_valid && mul_res_ready;	
	
`else
// Karatsuba algorithm
//x*y=(b^2+b)*x1*y1 - b*(x1-x0)*(y1-y0)+(b+1)*x0*y0

/* verilator lint_off UNUSED */

localparam SIZE=64;
localparam DSIZE=SIZE*2;
localparam HSIZE=SIZE/2;
localparam b2b=HSIZE*HSIZE+HSIZE;
localparam b=HSIZE;
localparam b1=HSIZE+1;
 
logic [HSIZE-1:0] a_high;
logic [HSIZE-1:0] a_low;

logic [HSIZE-1:0] a_high_;
logic [HSIZE-1:0] a_low_;

logic [HSIZE-1:0] b_high;
logic [HSIZE-1:0] b_low;

logic [HSIZE-1:0] b_high_;
logic [HSIZE-1:0] b_low_;

logic [DSIZE-1:0] mul_res1;
logic [DSIZE-1:0] mul_res2;
logic [DSIZE-1:0] mul_res3;

logic [DSIZE-1:0] mul_res4;
logic [DSIZE-1:0] mul_res5;
logic [DSIZE-1:0] mul_res6;
logic [DSIZE-1:0] mul_res7;
logic [DSIZE-1:0]  keep_res;

logic [DSIZE-1:0] add_result;

logic [HSIZE-1:0] sub_res1;
logic [HSIZE-1:0] sub_res2;

logic [3:0] valid_pipe;

logic run_pipeline;

assign a_high_	=mul_a[SIZE-1:HSIZE];
assign a_low_	=mul_a[HSIZE-1:0];

assign b_high_	=mul_b[SIZE-1:HSIZE];
assign b_low_	=mul_b[HSIZE-1:0];

assign mul_res_valid = valid_pipe[3];

assign mul_result 	 = add_result[SIZE-1:0];


assign mul_ack=valid_pipe[0] && (run_pipeline);
assign run_pipeline= (mul_res_ready || (~valid_pipe[3]));	

always_ff @(posedge clk or negedge rst_n)
	if (!rst_n) begin
		
		mul_res1<=0;
		mul_res2<=0;
		mul_res3<=0;
		
		mul_res4<=0;
		mul_res5<=0;
		mul_res6<=0;
		mul_res7<=0;
		keep_res<=0;
		
		sub_res1<=0;
		sub_res2<=0;
		
		valid_pipe<=0;
		add_result<=0;

		
	end else begin
	if (run_pipeline)
	begin

			sub_res1<=a_high_-a_low_;
			sub_res2<=b_high_-b_low_;
			a_high<=a_high_;
			a_low<=a_low_;
			b_high<=b_high_;
			b_low<=b_low_;

		valid_pipe[0]<=mul_valid;
	

			mul_res1<=a_high*b_high;
			mul_res2<=sub_res1*sub_res2;
			mul_res3<=a_low*b_low;

		valid_pipe[1]<=valid_pipe[0];
	

			mul_res4<=mul_res1<<HSIZE;
			mul_res5<=mul_res1<<SIZE;	
			mul_res6<=mul_res2<<HSIZE;
			mul_res7<=mul_res3<<HSIZE;
			keep_res<=mul_res3;

		valid_pipe[2]<=valid_pipe[1];
		
			add_result<=mul_res4+mul_res5-mul_res6+mul_res7+keep_res;

		valid_pipe[3]<=valid_pipe[2];
	end
	
	end

	




`endif




endmodule