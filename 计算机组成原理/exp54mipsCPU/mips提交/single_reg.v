`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/08 18:52:03
// Design Name: 
// Module Name: single_reg
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


module single_reg(
    input clk, // 1 位输入，寄存器时钟信号，上升沿时为 PC寄存器赋值
    input rst, // 1 位输入，重置信号，高电平时将 PC 寄存器清零 注：当 ena 信号无效时，rst 也可以重置寄存器
    input ena, // 1 位输入,有效信号高电平时寄存器工读入data_in 的值，否则保持原有输出
    input [31 : 0] data_in, // 31 位输入，输入数据将被存入寄存器内部
    output reg [31 : 0] data_out // 31 位输出，工作时始终输出 PC 寄存器内部存储的值
    );
    initial
    begin
        data_out = 32'h00400000;
    end
    always @ (negedge clk)
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
