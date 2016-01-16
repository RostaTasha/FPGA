
// Wrapper that inserts registers at all inputs and outputs, to make Quartus report accurate fmax

module quartus_top (
    input  logic clk,
    input  logic rst_n,

    input  logic add_valid,
    output logic add_ready,
    input  logic [WIDTH-1:0] add_a,
    input  logic [WIDTH-1:0] add_b,

    input  logic sub_valid,
    output logic sub_ready,
    input  logic [WIDTH-1:0] sub_a,
    input  logic [WIDTH-1:0] sub_b,

    input  logic mul_valid,
    output logic mul_ready,
    input  logic [WIDTH-1:0] mul_a,
    input  logic [WIDTH-1:0] mul_b,

    output logic result_valid,
    input  logic result_ready,
    output logic [2:0] result_unit,
    output logic [WIDTH-1:0] result
);

parameter WIDTH = 64;


logic i_add_valid;
logic i_add_ready;
logic [WIDTH-1:0] i_add_a;
logic [WIDTH-1:0] i_add_b;

logic i_sub_valid;
logic i_sub_ready;
logic [WIDTH-1:0] i_sub_a;
logic [WIDTH-1:0] i_sub_b;

logic i_mul_valid;
logic i_mul_ready;
logic [WIDTH-1:0] i_mul_a;
logic [WIDTH-1:0] i_mul_b;

logic i_result_valid;
logic i_result_ready;
logic [2:0] i_result_unit;
logic [WIDTH-1:0] i_result;

always_ff @(posedge clk)
begin
    // inputs
    i_add_valid <= add_valid;
    i_add_a <= add_a;
    i_add_b <= add_b;
    i_sub_valid <= sub_valid;
    i_sub_a <= sub_a;
    i_sub_b <= sub_b;
    i_mul_valid <= mul_valid;
    i_mul_a <= mul_a;
    i_mul_b <= mul_b;
    i_result_ready <= result_ready;

    // outputs
    add_ready <= i_add_ready;
    sub_ready <= i_sub_ready;
    mul_ready <= i_mul_ready;
    result_valid <= i_result_valid;
    result_unit <= i_result_unit;
    result <= i_result;
end

calculator #(
    .WIDTH(WIDTH)
) calculator_inst (
    .clk(clk),
    .rst_n(rst_n),

    .add_valid(i_add_valid),
    .add_ack(i_add_ready),
    .add_a(i_add_a),
    .add_b(i_add_b),

    .sub_valid(i_sub_valid),
    .sub_ack(i_sub_ready),
    .sub_a(i_sub_a),
    .sub_b(i_sub_b),

    .mul_valid(i_mul_valid),
    .mul_ack(i_mul_ready),
    .mul_a(i_mul_a),
    .mul_b(i_mul_b),

    .result_valid(i_result_valid),
    .result_ack(i_result_ready),
    .result_unit(i_result_unit),
    .result(i_result)
);

endmodule
