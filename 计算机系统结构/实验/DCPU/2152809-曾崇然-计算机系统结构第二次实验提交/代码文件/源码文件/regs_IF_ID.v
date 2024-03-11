`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/28 22:34:16
// Design Name: 
// Module Name: Pipe_IF_ID
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


module regs_IF_ID(
    input clk,
    input rst,
    input [31:0] npc_if,
    input [31:0] instr_if,
    output reg [31:0] npc_id = 32'b0,
    output reg [31:0] instr_id = 32'b0
    );
    
    always @(posedge clk or posedge rst)
    begin
        if(rst) 
        begin
            instr_id <= 32'b0;   
            npc_id <= 32'b0;
        end 
        else 
        begin
            instr_id <= instr_if; 
            npc_id <= npc_if;
        end
    end
endmodule

