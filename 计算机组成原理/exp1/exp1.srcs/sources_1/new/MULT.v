`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/03/21 08:47:36
// Design Name: 
// Module Name: MULT
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


module MULT(
input clk,
input reset,
input [31:0] a,
input [31:0] b,
output reg [63:0] z
);
reg [32:0] A;
reg [31:0] B;
reg [32:0] part1;
reg [30:0] part2;
reg [4:0] i;
reg flag;
initial
begin
  part1=0;
  part2=0;
  i=0;
  flag=0;
end

always @ (a,b)
begin
  if(flag==0)
  begin
    A[32]=a[31];
    A[31:0]=a[31:0];
    B=b;
    flag=1;
  end
end

always @ (clk)
begin
  if(flag==1)
  begin
    if(reset==1)
    begin
      part1=0;
      part2=0;
      i=0;
      flag=0;
    end
    else
    begin
      if(B[i]==1)
        part1=part1+A;
      part2[i]=part1[0];
      part1[31:0]=part1[32:1];
      part1[32]=part1[31];
      if(i==30)
      begin
        z[63:31]=part1[32:0];
        z[30:0]=part2[30:0];
        if(B[31]==1)
          z[63:31]=z[63:31]-A;
        i=0;
        part1=0;
        part2=0;
        flag=0;
      end
      else
        i=i+1;
    end
  end
end
endmodule
