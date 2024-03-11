`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/28 22:48:13
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


module regfiles(
    input clk,
    input rst,
    input write,
    input [4:0] rn1,
    input [4:0] rn2,
    input [4:0] w_addr,
    input [4:0] r_addr,
    input [31:0] data_in,
    output [31:0] data_out1,
    output [31:0] data_out2,
    output [31:0] data_out
    );
    
    integer i;
    reg [31:0] regs[31:0];
     
    //从寄存器读取数据
    assign data_out1 = (rn1)?regs[rn1]:0;
    assign data_out2 = (rn2)?regs[rn2]:0;
    assign data_out = (r_addr)?regs[r_addr]:0;
    
    //将数据写入寄存器
    always@(negedge clk or posedge rst) 
    begin
        if(rst==1) 
        begin
            for(i=0;i<32;i=i+1) 
            begin
                regs[i]<=0; 
            end 
        end
        else if(w_addr != 0 && write) 
        begin
            regs[w_addr]<=data_in; 
        end
    end
endmodule

