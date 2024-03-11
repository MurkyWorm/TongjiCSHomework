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
    input [31 : 0] a, // 32 λ���� a
    input [31 : 0] b, // 32 λ���� b
    input s, // 1 λ���룬�� s=0 ʱ r ��ֵ���� a��s=1 ʱ r ��ֵ���� b
    output [31 : 0] r // 32 λ�������Ӧλ��ֵ�� a b s ��ֵȷ
    );
    assign r = s ? b : a;
endmodule
