`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/08 23:02:24
// Design Name: 
// Module Name: cp0
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


module cp0(
    input clk,//时钟信号
    input rst,//复位信号
    input exc,//是否发生中断
    input mfc0,//CP0 指令是Mfc0
    input mtc0,//CP0 指令是Mtc0
    input eret,//CP0指令是ERET
    input [31:0] pc,//写入的pc地址
    input [4:0] Rd,//要写入的寄存器编号
    input [4:0] cause,//中断类型
    input [31:0] wdata,//通用寄存器到CP0寄存器的数据       
    output [31:0] rdata,//从CP0输出到通用寄存器的数据
    output [31:0] status,//从CP0输出的状态
    output [31:0] exc_addr//CP0保存的PC的地址
    );
    reg [31 : 0] regfiles [31 : 0];
    
    assign rdata = exc && mfc0 ? regfiles[Rd] : 32'bz;
    assign status = exc && mfc0 ? regfiles[12] : 32'bz;
    assign exc_addr = exc && eret ? regfiles[14] : 32'bz;
    
    always @ (posedge clk)
    begin
        if (rst == 1 && exc == 1)
        begin
            regfiles[0] <= 0;
            regfiles[1] <= 0;
            regfiles[2] <= 0;
            regfiles[3] <= 0;
            regfiles[4] <= 0;
            regfiles[5] <= 0;
            regfiles[6] <= 0;
            regfiles[7] <= 0;
            regfiles[8] <= 0;
            regfiles[9] <= 0;
            regfiles[10] <= 0;
            regfiles[11] <= 0;
            regfiles[12] <= 0;
            regfiles[13] <= 0;
            regfiles[14] <= 0;
            regfiles[15] <= 0;
            regfiles[16] <= 0;
            regfiles[17] <= 0;
            regfiles[18] <= 0;
            regfiles[19] <= 0;
            regfiles[20] <= 0;
            regfiles[21] <= 0;
            regfiles[22] <= 0;
            regfiles[23] <= 0;
            regfiles[24] <= 0;
            regfiles[25] <= 0;
            regfiles[26] <= 0;
            regfiles[27] <= 0;
            regfiles[28] <= 0;
            regfiles[29] <= 0;
            regfiles[30] <= 0;
            regfiles[31] <= 0;
        end
        else if (exc == 1)
        begin
            if (mtc0)
            begin
                regfiles[Rd] <= wdata;
            end
            else if (cause == 5'b01000 || cause == 5'b01001 || cause == 5'b01001)
            begin
                regfiles[12] <= regfiles[12] << 5;
                regfiles[13] <= {24'b0, cause, 2'b0};
                regfiles[14] <= pc;
            end
            else if (eret)
            begin
                regfiles[12] <= regfiles[12] >> 5;
            end
        end
    end
endmodule
