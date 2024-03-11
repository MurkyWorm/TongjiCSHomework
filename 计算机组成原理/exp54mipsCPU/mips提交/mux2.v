`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/08 22:57:54
// Design Name: 
// Module Name: mux2
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


module mux2(
    input [31 : 0] a, // 32 位输入 a
    input [31 : 0] b, // 32 位输入 b
    input s, // 1 位输入，当 s=0 时 r 的值等于 a，s=1 时 r 的值等于 b
    output [31 : 0] r // 32 位输出，相应位的值由 a b s 的值确
    );
    assign r = s ? b : a;
endmodule
