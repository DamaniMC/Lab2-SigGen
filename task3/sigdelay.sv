module sigdelay #( 
    parameter A_WIDTH=9,
    D_WIDTH=8)
(
    input logic     clk,            //clock
    input logic     rst,            //reset
    input logic     en,             //counter enable
    input logic [D_WIDTH-1:0] incr,
    output logic [D_WIDTH-1:0] count,
    input logic wr,
    input logic rd,
    input logic [D_WIDTH-1:0] din,
    output logic [D_WIDTH-1:0] dout,
    input logic [A_WIDTH-1:0] offset
);

logic [A_WIDTH-1:0] addr;

counter #(A_WIDTH) addrCounter(
    .clk (clk),
    .rst (rst),
    .en (en),
    .incr (incr),
    .count (addr)
);
ram2ports #(A_WIDTH, D_WIDTH) ram(
    .clk(clk),
    .wr_en(wr),
    .rd_en(rd),
    .din(din),
    .dout(dout),
    .wr_addr(addr+offset),
    .rd_addr(addr)
);
endmodule
