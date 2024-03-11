`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/08 18:48:36
// Design Name: 
// Module Name: mux4
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


module mux4(
    input [31 : 0] a, // 32 位输入 a
    input [31 : 0] b, // 32 位输入 b
    input [31 : 0] c, // 32 位输入 c
    input [31 : 0] d, // 32 位输入 d
    input [1 : 0] s, // 2 位输入，当 s=00 时 r 的值等于 a，s=01 时 r 的值等于 b，s=10 时 r 的值等于 c，s=11 时 r 的值等于 d
    output reg [31:0] r // 32 位输出，相应位的值由 a b c d s 的值确
    );
    always @ (*)
    begin
        if (s == 0)
        begin
            r = a;
        end
        else if (s == 1)
        begin
            r = b;
        end
        else if (s == 2)
        begin
            r = c;
        end
        else
        begin
            r = d;
        end
    end
endmodule
