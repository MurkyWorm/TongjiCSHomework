`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/28 22:32:56
// Design Name: 
// Module Name: PC
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


module PC_reg(
    input clk,
    input rst,
    input [31:0] data_in,
    output reg [31:0] data_out
    );
    always@(posedge clk or posedge rst) 
    begin
        if(rst==1)
            data_out <= 32'h00400000;
        else
            data_out <= data_in;  
    end
endmodule