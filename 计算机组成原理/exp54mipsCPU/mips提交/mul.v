`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/08 23:06:24
// Design Name: 
// Module Name: mul
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


module mul(
    input [31 : 0] a,
    input [31 : 0] b,
    input instr,
    output reg [31 : 0] lo,
    output reg [31 : 0] hi
    );
    reg [63 : 0] mid;
    always @ (*)
    begin
        if (instr)
        begin
            mid = a * b;
        end
        else
        begin
            mid = $signed(a) * $signed(b);
        end
        hi = mid[63 : 32];
        lo = mid[31 : 0];
    end
endmodule
