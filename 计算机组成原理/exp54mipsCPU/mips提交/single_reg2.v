`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/10 17:23:07
// Design Name: 
// Module Name: single_reg2
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


module single_reg2(
    input clk, // 1 λ���룬�Ĵ���ʱ���źţ�������ʱΪ PC�Ĵ�����ֵ
    input rst, // 1 λ���룬�����źţ��ߵ�ƽʱ�� PC �Ĵ������� ע���� ena �ź���Чʱ��rst Ҳ�������üĴ���
    input ena, // 1 λ����,��Ч�źŸߵ�ƽʱ�Ĵ���������data_in ��ֵ�����򱣳�ԭ�����
    input [31 : 0] data_in, // 31 λ���룬�������ݽ�������Ĵ����ڲ�
    output reg [31 : 0] data_out // 31 λ���������ʱʼ����� PC �Ĵ����ڲ��洢��ֵ
    );
    initial
    begin
        data_out = 32'h00400000;
    end
    always @ (posedge clk)
    begin
        if (rst == 1)
        begin
            data_out <= 32'h00400000;
        end
        else
        begin
            if (ena == 1)
            begin
                data_out <= data_in;
            end
        end
    end
endmodule
