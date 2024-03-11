`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/26 09:59:27
// Design Name: 
// Module Name: top_tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module top_tb();
reg clk_in;
reg enable;
reg reset;
reg start;

initial
begin
    clk_in = 1'b0;
    enable = 1'b1;
    reset = 1'b1;
    start = 1'b1;
    #10 reset = 1'b0;
end

always
begin
    #5 clk_in = ~clk_in;
end

top top_inst(clk_in, enable, reset, start);
endmodule
