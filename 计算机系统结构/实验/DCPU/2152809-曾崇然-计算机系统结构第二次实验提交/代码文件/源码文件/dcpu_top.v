`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/28 22:53:59
// Design Name: 
// Module Name: pcpu_top
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


module dcpu_top(
    input clk,
    input rst,
    input [4:0] raddr,
    output [31:0] instr,
    output [31:0] pc,
    output [31:0] odata
    );
    wire [31:0] a;
    assign a = pc - 32'h00400000;

    imem imem_inst(a[12:2], instr);
    dcpu dcpu_inst(clk, rst, instr, raddr, pc, odata);
endmodule
