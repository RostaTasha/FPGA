// wrapper for arbiter engine
//chooses result value according to grant, which was set by arbiter engine
//

module arbiter #(
WIDTH=64
)
(
input rst_n,
input clk,
input [WIDTH-1:0] a,
input a_valid,
output a_ready,
input [WIDTH-1:0] b,
input b_valid,
output b_ready,
input [WIDTH-1:0] c,
input c_valid,
output c_ready,
output [WIDTH-1:0] result,
output result_valid,
output [2:0] result_unit,
input result_ack
);



logic [2:0] req, grant;
logic [2:0] arbiter_ready;
logic [WIDTH-1:0] result_;




always_comb begin

            case (grant)
            3'b001 : result_=a[WIDTH-1:0];
            3'b010 : result_=b[WIDTH-1:0];
            3'b100 : result_=c[WIDTH-1:0];
            default: result_=0;
            endcase
            end
            
            assign req={c_valid,b_valid,a_valid};
            assign a_ready = arbiter_ready[0];
            assign b_ready = arbiter_ready[1];
            assign c_ready = arbiter_ready[2];
            

            
            
            arbiter_engine arbiter_engine_inst (
                .clk(clk),
                .rst_n(rst_n),
                .req(req),
                .grant(grant)
            );
            
            
            assign arbiter_ready= ((grant)&{result_ack,result_ack,result_ack}); //((grant)&{result_ack,result_ack,result_ack}) | (~req); 
            assign			result_valid =grant[0]||grant[1]||grant[2];
            assign			result_unit =grant;
            assign 			result =result_;			
			

			
			

endmodule