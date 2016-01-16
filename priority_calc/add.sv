// the module calculates the result of addition of two values
// In this case the addition is performed in one step and the result is saved to register.

module add#(
WIDTH=64
) 
(
    input  logic clk,
    input  logic rst_n,
    input  logic add_valid,
	output logic add_ack,
    input  logic [WIDTH-1:0] add_a,
    input  logic [WIDTH-1:0] add_b,
	output logic [WIDTH-1:0] add_result,
	output logic add_res_valid,
	input  logic add_res_ready
	
);


always_ff @(posedge clk or negedge rst_n)
if (!rst_n) begin
	add_result<=0;
	add_res_valid<=0;
end else begin
	add_res_valid<=add_valid;
	if (add_valid)
		add_result<=add_a+add_b;
end

assign add_ack=add_valid && (add_res_ready);




endmodule