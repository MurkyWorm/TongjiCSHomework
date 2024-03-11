`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/24 09:59:16
// Design Name: 
// Module Name: top
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


module top(
    input clk_in,
    input enable,
    input reset,
    input start,
    output [7:0] o_seg,
    output [7:0] o_sel
    );
    wire [15:0] instruction;
    wire [15:0] datain;
    wire [7:0] i_addr;
    wire [7:0] d_addr;
    wire wena;
    wire [15:0] dataout;
    
    reg [24 : 0] cnt;
    always @ (posedge clk_in, negedge reset)
    if (reset)
        cnt <= 0;
    else
        cnt <= cnt + 1'b1;
    wire clk_cpu = cnt[24];
    seg7x16(clk_in, reset, 1, {8'b0000_0000, instruction}, o_seg, o_sel);
    pcpu pcpu_inst(clk_cpu, enable, reset, start, instruction, datain, i_addr, d_addr, wena, dataout);
    imem imem_inst(i_addr, instruction);
    dmem dmem_inst(clk_cpu, enable, wena, d_addr, dataout, datain);
endmodule
