`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/28 22:45:33
// Design Name: 
// Module Name: Pipe_EXE_MEM
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


module regs_EX_MEM(
    input clk,
    input rst,
    
    input dm_w_signal_ex,
    input write_ex,
    input is_lw_ex,
    input is_jal_ex,
    input is_mul_ex,
    input [4:0] w_addr_ex,
    input [31:0] alu_ex,
    input [31:0] mul_ex,
    input [31:0] npc_ex,
    input [31:0] dm_wdata_ex,
    
    output reg dm_w_signal_mem = 1'b0,
    output reg write_mem = 1'b0,
    output reg is_lw_mem = 1'b0,
    output reg is_jal_mem = 1'b0,
    output reg is_mul_mem = 1'b0,
    output reg [4:0] w_addr_mem = 5'b0,
    output reg [31:0] alu_mem = 32'b0,
    output reg [31:0] mul_mem = 32'b0,
    output reg [31:0] npc_mem = 32'b0,
    output reg [31:0] dm_wdata_mem = 32'b0
    );
    always @(posedge rst or posedge clk) 
    begin
        if(rst) 
        begin
            write_mem <= 1'b0;
            alu_mem <= 32'b0;
            w_addr_mem <= 5'b0;
            dm_wdata_mem <= 32'b0;
            dm_w_signal_mem <= 1'b0;
            npc_mem <= 32'b0;
            is_lw_mem <= 32'b0;
            is_jal_mem <= 32'b0;
            is_mul_mem <= 32'b0;
            mul_mem <= 32'b0;
        end 
        else begin
            write_mem <= write_ex;
            alu_mem <= alu_ex;
            mul_mem <= mul_ex;
            w_addr_mem <= w_addr_ex;
            dm_wdata_mem <= dm_wdata_ex;
            dm_w_signal_mem <= dm_w_signal_ex;
            npc_mem <= npc_ex;
            is_lw_mem <= is_lw_ex;
            is_jal_mem <= is_jal_ex;
            is_mul_mem <= is_mul_ex;
        end
    end
endmodule
