// the module calculates the result of subtraction of two values
// In this case the subtraction is performed in one step and the result is saved to register.

module sub#(
WIDTH=64
) 
(
    input  logic clk,
    input  logic rst_n,
    input  logic sub_valid,
	output logic sub_ack,
    input  logic [WIDTH-1:0] sub_a,
    input  logic [WIDTH-1:0] sub_b,
	output logic [WIDTH-1:0] sub_result,
	output logic sub_res_valid,
	input  logic sub_res_ready
	
);




always_ff @(posedge clk or negedge rst_n)
if (!rst_n) begin
	sub_result<=0;
	sub_res_valid<=0;
end else begin
	sub_res_valid<=sub_valid;
	if (sub_valid)
		sub_result<=sub_a-sub_b;
end



assign sub_ack=sub_valid && (sub_res_ready);

endmodule