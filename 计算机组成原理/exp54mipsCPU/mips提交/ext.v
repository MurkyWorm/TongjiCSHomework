`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/08 19:06:09
// Design Name: 
// Module Name: ext
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


module ext #(parameter WIDTH = 16)(
    input [WIDTH - 1 : 0] a,//�������ݣ����ݿ�ȿ��Ը�����Ҫ���ж���
    input sext,//sext ��ЧΪ������չ������ 0 ��չ
    output [31 : 0] b//32 λ�������
    );
    assign b = {sext ? {32 - WIDTH{a[WIDTH - 1]}} : {32 - WIDTH{1'b0}}, a[WIDTH - 1 : 0]};
endmodule
