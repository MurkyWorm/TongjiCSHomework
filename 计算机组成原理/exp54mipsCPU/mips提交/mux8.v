`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/08 19:07:37
// Design Name: 
// Module Name: mux8
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


module mux8(
    input [31 : 0] a, // 32 λ���� a
    input [31 : 0] b, // 32 λ���� b
    input [31 : 0] c, // 32 λ���� c
    input [31 : 0] d, // 32 λ���� d
    input [31 : 0] e, // 32 λ���� e
    input [31 : 0] f, // 32 λ���� f
    input [31 : 0] g, // 32 λ���� g
    input [31 : 0] h, // 32 λ���� h
    input [2 : 0] s, // 3 λ���룬�� s=00 ʱ r ��ֵ���� a��s=01 ʱ r ��ֵ���� b��s=10 ʱ r ��ֵ���� c��s=11 ʱ r ��ֵ���� d
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
        else if (s == 3)
        begin
            r = d;
        end
        else if (s == 4)
        begin
            r = e;
        end
        else if (s == 5)
        begin
            r = f;
        end
        else if (s == 6)
        begin
            r = g;
        end
        else if (s == 7)
        begin
            r = h;
        end
    end
endmodule
