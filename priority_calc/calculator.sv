/* verilator lint_off UNUSED */


module calculator (
    input  logic clk,
    input  logic rst_n,

    input  logic add_valid,
    output logic add_ack,
    input  logic [WIDTH-1:0] add_a,
    input  logic [WIDTH-1:0] add_b,

    input  logic sub_valid,
    output logic sub_ack,
    input  logic [WIDTH-1:0] sub_a,
    input  logic [WIDTH-1:0] sub_b,

    input  logic mul_valid,
    output logic mul_ack,
    input  logic [WIDTH-1:0] mul_a,
    input  logic [WIDTH-1:0] mul_b,

    output logic result_valid,
    input  logic result_ack,
    output logic [2:0] result_unit,
    output logic [WIDTH-1:0] result
);

parameter WIDTH = 64; // LEAVE AS DEFAULT

logic  add_res_ready;
logic [WIDTH-1:0] add_result;
logic add_res_valid;

logic sub_res_ready;
logic [WIDTH-1:0] sub_result;
logic sub_res_valid;

logic mul_res_ready;
logic [WIDTH-1:0] mul_result;
logic mul_res_valid;

 
add#(
    .WIDTH(WIDTH)
) add_inst (
	.rst_n(rst_n),
	.clk(clk),
	.add_valid(add_valid),
	.add_ack(add_ack),
	.add_a(add_a),
	.add_b(add_b),
	.add_result(add_result),
	.add_res_valid(add_res_valid),
	.add_res_ready(add_res_ready)
);


sub#(
    .WIDTH(WIDTH)
) sub_inst (
	.rst_n(rst_n),
	.clk(clk),
	.sub_valid(sub_valid),
	.sub_ack(sub_ack),
	.sub_a(sub_a),
	.sub_b(sub_b),
	.sub_result(sub_result),
	.sub_res_valid(sub_res_valid),
	.sub_res_ready(sub_res_ready)
);


mul#(
    .WIDTH(WIDTH)
) mul_inst (
	.rst_n(rst_n),
	.clk(clk),
	.mul_valid(mul_valid),
	.mul_ack(mul_ack),
	.mul_a(mul_a),
	.mul_b(mul_b),
	.mul_result(mul_result),
	.mul_res_valid(mul_res_valid),
	.mul_res_ready(mul_res_ready)
);


arbiter#(
    .WIDTH(WIDTH)
) arbiter_inst (
	.rst_n(rst_n),
	.clk(clk),
	.a(add_result[WIDTH-1:0]),
	.a_valid(add_res_valid),
	.a_ready(add_res_ready),
	.b(sub_result[WIDTH-1:0]),
	.b_valid(sub_res_valid),
	.b_ready(sub_res_ready),	
	.c(mul_result[WIDTH-1:0]),
	.c_valid(mul_res_valid),
	.c_ready(mul_res_ready),
	.result(result),
	.result_valid(result_valid),
	.result_unit(result_unit),	
	.result_ack(result_ack)
);


endmodule
