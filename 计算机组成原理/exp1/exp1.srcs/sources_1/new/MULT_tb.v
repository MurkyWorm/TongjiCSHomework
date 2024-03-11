`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/03/26 14:50:34
// Design Name: 
// Module Name: MULT_tb
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


module MULT_tb();
reg clk;
reg reset;
reg [31:0] a;
reg [31:0] b;
wire [63:0] z;
MULT MULT_inst(clk,reset,a,b,z);
initial
begin
  clk=0;
  a=-3;
  b=-3;
  reset=0;
  #200 a=3;
  b=-3;
  #200
  a=300;
  b=-1;
end
always
  #10 clk=~clk;
endmodule
