`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/08 19:04:34
// Design Name: 
// Module Name: concatenator
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


module concatenator(
    input [25 : 0] offset,
    input [3 : 0] pc,
    output [31 : 0] r
    );
    assign r = {{pc}, {offset}, {2'b00}};
endmodule
