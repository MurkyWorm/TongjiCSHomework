`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/09 18:58:19
// Design Name: 
// Module Name: sccomp_dataflow
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


module sccomp_dataflow(
    input clk_in,
    input reset, 
    output [31:0] inst, 
    output [31:0] pc
    );
    wire [31 : 0] dmem_out;
    wire dmem_ena;
    wire dmem_wena;
    wire [31 : 0] dmem_addr;
    wire [31 : 0] dmem_in;
    wire [1 : 0] d_ram_instr;
    wire [31 : 0] instruction;
    reg [25:0] cnt;
    
    assign inst = instruction;
    
    cpu sccpu(clk_in, reset, instruction, dmem_out, pc, dmem_ena, dmem_wena, dmem_addr, dmem_in, d_ram_instr);
    imem im(pc[12 : 2], instruction);
    ram dmem(clk_in, dmem_ena, dmem_wena, d_ram_instr, dmem_addr[12 : 0], dmem_in, dmem_out);
endmodule
