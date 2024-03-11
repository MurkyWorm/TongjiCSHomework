`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/03/21 08:48:33
// Design Name: 
// Module Name: MULTU
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


module MULTU(
input clk,
input reset,
input [31:0] a,
input [31:0] b,
output reg [63:0] z
);
reg [31:0] part1;
reg [31:0] part2;
reg [31:0] A;
reg [31:0] B;
reg [4:0] i;
reg flag;

initial
begin
  i=0;
  part1=0;
  part2=0;
  A=0;
  B=0;
  flag=0;
end//初始化

always @ (a,b)
begin
  if(flag==0)
  begin
    A=a;
    B=b;
    flag=1;
  end
end//是否可进行下一次计算

always @ (clk)
begin
  if(flag==1)
  begin
    if(reset==1)
    begin
      part1=0;
      part2=0;
      i=0;
      z=0;
      A=0;
      B=0;
      flag=0;
    end
    else
    begin
      if(B[i]==1)
        part1=part1+A;
      part2[i]=part1[0];
      part1=part1>>1;
      if(i==31)
      begin
        z[63:32]=part1[31:0];
        z[31:0]=part2[31:0];
        part1=0;
        part2=0;
        i=0;
        flag=0;
      end
      else
        i=i+1;
    end
  end
end
endmodule
