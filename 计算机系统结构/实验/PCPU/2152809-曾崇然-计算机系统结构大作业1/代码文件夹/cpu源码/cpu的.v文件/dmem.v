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
    input clk, // 存储器时钟信号，上升沿时向 ram 内部写入数据
    input ram_ena, // 存储器有效信号，有效时存储器才运行，否则输出 z
    input wena, // 存储器写有效信号，与 ram_ena 同时有效时才可写存储器
    input [7 : 0] addr, // 输入地址，指定数据读写的地址
    input [15 : 0] data_in, // 存储器写入的数据，在 clk 上升沿时被写入
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
