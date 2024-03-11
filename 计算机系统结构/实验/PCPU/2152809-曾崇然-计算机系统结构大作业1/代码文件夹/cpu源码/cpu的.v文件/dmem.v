`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/24 09:53:27
// Design Name: 
// Module Name: dmem
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


module dmem(
    input clk, // �洢��ʱ���źţ�������ʱ�� ram �ڲ�д������
    input ram_ena, // �洢����Ч�źţ���Чʱ�洢�������У�������� z
    input wena, // �洢��д��Ч�źţ��� ram_ena ͬʱ��Чʱ�ſ�д�洢��
    input [7 : 0] addr, // �����ַ��ָ�����ݶ�д�ĵ�ַ
    input [15 : 0] data_in, // �洢��д������ݣ��� clk ������ʱ��д��
    output [15 : 0] data_out
    );
    reg [15:0] data [255:0];
    
    assign data_out = ram_ena ? data[addr] : 16'bzzzzzzzzzzzzzzzz;
    always @ (posedge clk)
    begin
        if (ram_ena == 1'b1 && wena == 1'b1)
        begin
            data[addr] = data_in;
        end
    end
endmodule
