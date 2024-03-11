`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/08 21:15:04
// Design Name: 
// Module Name: regfile
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


module regfile(
    input clk, //寄存器组时钟信号，下降沿写入数据（注意：pc 为上升沿，此为下降沿）
    input rst, //reset 信号，reset 有效时全部寄存器置零
    input we, //写有效信号，we 有效时寄存器才能被写入
    input [4:0] raddr1, //所需读取的寄存器的地址
    input [4:0] raddr2, //所需读取的寄存器的地址
    input [4:0] waddr, //写寄存器的地址
    input [31:0] wdata, //写寄存器数据
    output [31:0] rdata1, //raddr1 所对应寄存器的数据，只要有 raddr1 的输入即输出相应数据
    output [31:0] rdata2 //raddr2 所对应寄存器的数据，只要有 raddr2 的输入即输出相应数据
    );
    reg [31 : 0] array_reg [31 : 0];
    assign rdata1 = array_reg[raddr1];
    assign rdata2 = array_reg[raddr2];
    initial
    begin
        array_reg[0] = 0;
        array_reg[1] = 0;
        array_reg[2] = 0;
        array_reg[3] = 0;
        array_reg[4] = 0;
        array_reg[5] = 0;
        array_reg[6] = 0;
        array_reg[7] = 0;
        array_reg[8] = 0;
        array_reg[9] = 0;
        array_reg[10] = 0;
        array_reg[11] = 0;
        array_reg[12] = 0;
        array_reg[13] = 0;
        array_reg[14] = 0;
        array_reg[15] = 0;
        array_reg[16] = 0;
        array_reg[17] = 0;
        array_reg[18] = 0;
        array_reg[19] = 0;
        array_reg[20] = 0;
        array_reg[21] = 0;
        array_reg[22] = 0;
        array_reg[23] = 0;
        array_reg[24] = 0;
        array_reg[25] = 0;
        array_reg[26] = 0;
        array_reg[27] = 0;
        array_reg[28] = 0;
        array_reg[29] = 0;
        array_reg[30] = 0;
        array_reg[31] = 0;
    end
    always @ (posedge clk)
    begin
        if (rst == 1)
        begin
            array_reg[0] = 0;
            array_reg[1] = 0;
            array_reg[2] = 0;
            array_reg[3] = 0;
            array_reg[4] = 0;
            array_reg[5] = 0;
            array_reg[6] = 0;
            array_reg[7] = 0;
            array_reg[8] = 0;
            array_reg[9] = 0;
            array_reg[10] = 0;
            array_reg[11] = 0;
            array_reg[12] = 0;
            array_reg[13] = 0;
            array_reg[14] = 0;
            array_reg[15] = 0;
            array_reg[16] = 0;
            array_reg[17] = 0;
            array_reg[18] = 0;
            array_reg[19] = 0;
            array_reg[20] = 0;
            array_reg[21] = 0;
            array_reg[22] = 0;
            array_reg[23] = 0;
            array_reg[24] = 0;
            array_reg[25] = 0;
            array_reg[26] = 0;
            array_reg[27] = 0;
            array_reg[28] = 0;
            array_reg[29] = 0;
            array_reg[30] = 0;
            array_reg[31] = 0;
        end
        else
        begin
            if (we == 1 && waddr != 0)
            begin
                array_reg[waddr] = wdata;
            end
        end
    end
endmodule
