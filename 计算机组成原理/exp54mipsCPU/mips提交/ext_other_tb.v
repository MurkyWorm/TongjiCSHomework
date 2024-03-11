`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/09 11:16:05
// Design Name: 
// Module Name: ext_other_tb
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


module ext_other_tb();
    reg [31 : 0] data_in;
    reg [1 : 0] instr;
    wire [31 : 0] data_out;
    ext_other ext_other_inst(data_in, instr, data_out);
    initial
    begin
        data_in = 32'h0000a0f0;
        instr = 0;
        #40 instr = 1;
        #40 instr = 2;
        #40 instr = 3;
    end
endmodule
