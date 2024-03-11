`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/28 22:46:29
// Design Name: 
// Module Name: dmem
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


module dmem(
    input clk,
    input rst,
    input write,
	input [31:0] addr,
    input [31:0] data_in,
    output [31:0] data_out
    );
    integer i;
    reg [31:0] mem[0:2047];
    wire [31:0] addr_true;
    
    assign addr_true = addr - 32'h10010000;
    assign data_out = mem[addr_true[10:0]];

    always @(negedge clk or posedge rst) 
    begin
        if(rst==1) 
        begin
            for(i=0;i<2048;i=i+1) 
                mem[i] <= 0; 
        end
        else if(write==1) 
        begin
            mem[addr_true[10:0]] <= data_in; 
        end
    end
endmodule
