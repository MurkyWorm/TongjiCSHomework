`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/28 22:38:27
// Design Name: 
// Module Name: Pipe_ID_EXE
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


module regs_ID_EX(
    input clk,
    input rst,
    
    input dm_w_signal_id,
    input write_id,
    input is_lw_id,
    input is_jal_id,
    input is_mul_id,
    input mux_alu1_id,
    input [1:0] mux_alu2_id,
    input [3:0] aluc_id,
    input [31:0] npc_id,
    input [4:0] w_addr_id,
    input [31:0] shamt_id,
    input [31:0] simmediate_id,
    input [31:0] uimmediate_id,
    input [31:0] rs_wire_id,
    input [31:0] rt_wire_id,
    input [31:0] dm_wdata_id,
    
    output reg dm_w_signal_ex = 1'b0,
    output reg write_ex = 1'b0,
    output reg is_lw_ex = 1'b0,
    output reg is_jal_ex = 1'b0,
    output reg is_mul_ex = 1'b0,
    output reg mux_alu1_ex = 1'b0,
    output reg [1:0] mux_alu2_ex = 2'b0,
    output reg [3:0] aluc_ex = 4'b0,
    output reg [31:0] npc_ex = 32'b0,
    output reg [4:0] w_addr_ex = 5'b0,
    output reg [31:0] shamt_ex = 32'b0,
    output reg [31:0] simmediate_ex = 32'b0,
    output reg [31:0] uimmediate_ex = 32'b0,
    output reg [31:0] rs_wire_ex = 32'b0,
    output reg [31:0] rt_wire_ex = 32'b0,
    output reg [31:0] dm_wdata_ex = 32'b0
    );
    always @(posedge rst or posedge clk) 
    begin
        if(rst) 
        begin
            rs_wire_ex <= 32'b0;
            shamt_ex <= 32'b0;
            simmediate_ex <= 32'b0;
            uimmediate_ex <= 32'b0;
            rt_wire_ex <= 32'b0;
            mux_alu1_ex <= 1'b0;
            mux_alu2_ex <= 2'b0;
            aluc_ex <= 4'b0;
            write_ex <= 'b0;
            w_addr_ex <= 5'b0;
            dm_wdata_ex <= 32'b0;
            dm_w_signal_ex <= 1'b0;
            npc_ex <= 32'b0;
            is_lw_ex <= 32'b0;
            is_jal_ex <= 32'b0;
            is_mul_ex <= 32'b0;
        end 
        else 
        begin
            rs_wire_ex <= rs_wire_id;
            shamt_ex <= shamt_id;
            simmediate_ex <= simmediate_id;
            uimmediate_ex <= uimmediate_id;
            rt_wire_ex <= rt_wire_id;
            mux_alu1_ex <= mux_alu1_id;
            mux_alu2_ex <= mux_alu2_id;
            aluc_ex <= aluc_id;
            write_ex <= write_id;
            w_addr_ex <= w_addr_id;
            dm_wdata_ex <= dm_wdata_id;
            dm_w_signal_ex <= dm_w_signal_id;
            npc_ex <= npc_id;
            is_lw_ex <= is_lw_id;
            is_jal_ex <= is_jal_id;
            is_mul_ex <= is_mul_id;
        end
    end
endmodule