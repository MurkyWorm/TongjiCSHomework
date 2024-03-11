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
    input [31 : 0] a, // 32 λ���� a
    input [31 : 0] b, // 32 λ���� b
    input [31 : 0] c, // 32 λ���� c
    input [31 : 0] d, // 32 λ���� d
    input [1 : 0] s, // 2 λ���룬�� s=00 ʱ r ��ֵ���� a��s=01 ʱ r ��ֵ���� b��s=10 ʱ r ��ֵ���� c��s=11 ʱ r ��ֵ���� d
    output reg [31:0] r // 32 λ�������Ӧλ��ֵ�� a b c d s ��ֵȷ
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
