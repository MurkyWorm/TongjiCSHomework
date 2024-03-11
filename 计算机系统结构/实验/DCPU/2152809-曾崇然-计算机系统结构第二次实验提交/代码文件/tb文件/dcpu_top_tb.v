`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/28 22:57:39
// Design Name: 
// Module Name: pcpu_top_tb
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


module dcpu_top_tb();
    reg clk;
    reg rst;
    reg [4:0] raddr;
    wire [31:0] instr;
    wire [31:0] pc;
    wire [31:0] odata;
    integer count = 0;
    integer count_nop = 0;
    initial  
    begin
        clk = 1;
        rst = 1; 
        raddr = 5'b00001;
        #1 rst = 0; 
    end
    
    always 
    begin
        #50 clk <= ~clk;
    end
    
    always@(posedge clk)
    begin
        count <= count + 1;
        if (instr == 32'b0)
        begin
            count_nop <= count_nop + 1; 
        end
    end
    
    dcpu_top dcpu_top_inst(clk, rst, raddr, instr, pc, odata);
endmodule