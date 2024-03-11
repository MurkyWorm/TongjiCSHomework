`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/09 11:21:07
// Design Name: 
// Module Name: ram
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


module ram(
    input clk, // �洢��ʱ���źţ�������ʱ�� ram �ڲ�д������
    input ram_ena, // �洢����Ч�źţ���Чʱ�洢�������У�������� z
    input wena, // �洢��д��Ч�źţ��� ram_ena ͬʱ��Чʱ�ſ�д�洢��
    input [1 : 0] instr,
    input [10 : 0] addr, // �����ַ��ָ�����ݶ�д�ĵ�ַ
    input [31 : 0] data_in, // �洢��д������ݣ��� clk ������ʱ��д��
    output [31 : 0] data_out // �洢�����������ݣ�ram ����ʱ���������Ӧ��ַ������
    );
    reg [31 : 0] data [2047 : 0];
        
    assign data_out = ram_ena ? data[addr] : 32'bzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz;
    
    always @ (posedge clk)
    begin
        if (ram_ena == 1 && wena == 1)
        begin
            if (instr == 0)
            begin
                data[addr] = data_in;
            end
            else if (instr == 1)
            begin
                data[addr][7 : 0] = data_in[7 : 0];
            end
            else if (instr == 2)
            begin
                data[addr][15 : 0] = data_in[15 : 0];
            end
        end
    end
endmodule
