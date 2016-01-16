// original arbiter engine taken from  http://www.krll.de/portfolio/round-robin-arbiter/
// modified  by Tasha 
// 18.10.2015  arbiter produces grant on the same cycle as request was set
//



module arbiter_engine
(
input rst_n,
input clk,
input [2:0] req,
output[2:0]	grant
);



logic [3-1:0] grant_q ;
logic [3-1:0] pre_req  ;
logic [3-1:0] sel_gnt  ;
logic [3-1:0] isol_lsb ;
logic [3-1:0] mask_pre ;
logic [3-1:0] win      ;






always_ff @(posedge clk, negedge rst_n)
begin
if (!rst_n) begin
    pre_req <= 0;
   // grant_q <= 0;
end    
else begin
   // if (grant_q == 0) begin
        if (win != 0) pre_req <= win;
    //    grant_q <= win;
    // end   
end
end

assign grant_q = win;

assign grant    = grant_q;
assign mask_pre = req & ~(((pre_req) - 1) | pre_req); // Mask off previous winners
assign sel_gnt  = mask_pre  & ((~(mask_pre)) + 1);       // Select new winner
assign isol_lsb = req &  ((~(req)) + 1);            // Isolate least significant set bit.
   
always_comb begin 
	if (mask_pre !=0)
		win      = sel_gnt;
	else 
		win      = isol_lsb;
end
   
endmodule