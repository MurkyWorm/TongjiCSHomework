`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/04/02 15:47:19
// Design Name: 
// Module Name: DIV_tb
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


module DIV_tb();
reg [31:0] dividend;
reg [31:0] divisor;
wire start;
reg is_div;
reg clock;
reg reset;
wire [31:0] q;
wire [31:0] r;
wire busy;
assign start=is_div&~busy;
DIV DIV_inst(dividend,divisor,start,clock,reset,q,r,busy);
initial
begin
  clock=0;
  reset=1;
  is_div=0;
  dividend=-5;
  divisor=-2;
  #50 reset=0;
  #5 is_div=1;
  #20 is_div=0;
end
always
begin
  #10 clock=~clock;
end
endmodule
