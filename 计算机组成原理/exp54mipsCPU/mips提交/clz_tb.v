`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/09 10:50:19
// Design Name: 
// Module Name: clz_tb
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


module clz_tb();
    reg [31 : 0] a;
    wire [31 : 0] r;
    clz clz_inst(a, r);
    
    initial
    begin
        a = 32'h0000f000;
        #100 a = 32'h7fffffff;
        #100 a = 32'h07ffffff;
        #100 a = 32'h00000000;
        #100 a = 32'h77777777;
    end
endmodule
