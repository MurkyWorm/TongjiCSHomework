`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/04 14:01:37
// Design Name: 
// Module Name: CP0
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


module CP0(
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
    reg [31 : 0] status12;
    reg [31 : 0] cause13;
    reg [31 : 0] epc14;
    
    assign rdata = exc && mfc0 ? ((Rd == 12) ? status12 : ((Rd == 13) ? cause13 : ((Rd == 14) ? epc14 : 32'bz))) : 32'bz;
    assign status = exc && mfc0 ? status12 : 32'bz;
    assign exc_addr = exc && eret ? epc14 : 32'bz;
    
    always @ (negedge clk)
    begin
        if (rst == 1 && exc == 1)
        begin
            status12 <= 0;
            cause13 <= 0;
            epc14 <= 0;
        end
        else if (exc == 1)
        begin
            if (mtc0)
            begin
                if (Rd == 12)
                begin
                    status12 <= wdata;
                end
                else if (Rd == 13)
                begin
                    cause13 <= wdata;
                end
                else if (Rd == 14)
                begin
                    epc14 <= wdata;
                end
            end
            else if (cause == 5'b01000 || cause == 5'b01001 || cause == 5'b01001)
            begin
                status12 <= status12 << 5;
                cause13 <= {24'b0, cause, 2'b0};
                epc14 <= pc;
            end
            else if (eret)
            begin
                status12 <= status12 >> 5;
            end
        end
    end
endmodule
