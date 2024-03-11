`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/31 10:28:22
// Design Name: 
// Module Name: dcpu_onboard
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


module dcpu_onboard(
    input clk_in,
    input enable,
    input reset,
    input stop,
    input [1:0] choice,
    input [4:0] raddr,
    output [7:0] o_seg,
    output [7:0] o_sel
    );
    wire [31:0] inst;
    wire [31:0] pc;
    wire [31:0] odata;
    wire [31:0] display;
    reg [24 : 0] cnt;
    always @ (posedge clk_in, posedge reset, posedge stop)
    if (reset)
        cnt <= 0;
    else if (stop)
        cnt <= cnt;
    else
        cnt <= cnt + 1'b1;
    wire clk_cpu = cnt[14];
    assign display = choice[0] ? inst : (choice[1] ? pc : odata);
    seg7x16 seg7x16_inst(clk_in, reset, enable, display, o_seg, o_sel);
    dcpu_top dcpu_top_inst(clk_cpu, reset, raddr, inst, pc, odata);
endmodule
