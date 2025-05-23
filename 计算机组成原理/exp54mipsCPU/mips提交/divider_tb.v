`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/05 22:20:47
// Design Name: 
// Module Name: divider_tb
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


module divider_tb();
    reg [31 : 0] a;
    reg [31 : 0] b;
    reg instr;
    wire [31 : 0] lo;
    wire [31 : 0] hi;
    divider divider_inst(a, b, instr, lo, hi);
    initial
    begin
        a = -2;
        b = 2;
        instr = 1;
        #100 instr = 0;
    end
endmodule
