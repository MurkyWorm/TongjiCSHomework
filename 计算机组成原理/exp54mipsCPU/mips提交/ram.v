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
    input clk, // 存储器时钟信号，上升沿时向 ram 内部写入数据
    input ram_ena, // 存储器有效信号，有效时存储器才运行，否则输出 z
    input wena, // 存储器写有效信号，与 ram_ena 同时有效时才可写存储器
    input [1 : 0] instr,
    input [10 : 0] addr, // 输入地址，指定数据读写的地址
    input [31 : 0] data_in, // 存储器写入的数据，在 clk 上升沿时被写入
    output [31 : 0] data_out // 存储器读出的数据，ram 工作时持续输出相应地址的数据
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
