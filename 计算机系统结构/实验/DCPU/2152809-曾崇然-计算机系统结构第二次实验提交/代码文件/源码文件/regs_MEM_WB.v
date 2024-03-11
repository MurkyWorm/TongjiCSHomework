`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/28 22:47:15
// Design Name: 
// Module Name: Pipe_MEM_WB
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


module regs_MEM_WB(
    input clk,
    input rst,
    
    input write_me,
    input is_lw_me,
    input is_jal_me,
    input is_mul_me,
    input [4:0] w_addr_me,
    input [31:0] alu_me,
    input [31:0] mul_me,
    input [31:0] npc_me,
    input [31:0] dm_rdata_me,
    
    output reg write_w = 1'b0,
    output reg is_lw_w = 1'b0,
    output reg is_jal_w = 1'b0,
    output reg is_mul_w = 1'b0,
    output reg [4:0] w_addr_w = 5'b0,
    output reg [31:0] alu_w = 32'b0,
    output reg [31:0] mul_w = 32'b0,
    output reg [31:0] npc_w = 32'b0,
    output reg [31:0] dm_rdata_w = 32'b0
    );
    
    always @(posedge rst or posedge clk) 
    begin
        if(rst) 
        begin
            write_w <= 1'b0;
            alu_w <= 32'b0;
            mul_w <= 32'b0;
            dm_rdata_w <= 32'b0;
            is_lw_w <= 32'b0;
            is_jal_w <= 32'b0;
            is_mul_w <= 32'b0;
            w_addr_w <= 5'b0;
            npc_w <= 32'b0;
        end 
        else 
        begin
            write_w <= write_me;
            alu_w <= alu_me;
            mul_w <= mul_me;
            npc_w <= npc_me;
            is_lw_w <= is_lw_me;
            is_jal_w <= is_jal_me;
            is_mul_w <= is_mul_me;
            dm_rdata_w <= dm_rdata_me;
            w_addr_w <= w_addr_me;
        end
    end
endmodule
