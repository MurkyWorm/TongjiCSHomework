`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/28 22:36:58
// Design Name: 
// Module Name: conflict
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


module conflict_judge(
    input [31:0] instr,
    input is_lw_id,
    input is_lw_ex,
    input is_lw_mem,
    input write_id,
    input write_ex,
    input write_mem,
    input [4:0] w_addr_id,
    input [4:0] w_addr_ex,
    input [4:0] w_addr_mem,
    output is_stall
    );
    
    wire [4:0] rs;
    wire [4:0] rt;
    
    assign rs = instr[25:21];
    assign rt = instr[20:16];

    assign is_stall =  (((is_lw_id && write_id && w_addr_id != 5'b0)&&((rs==w_addr_id)||(rt==w_addr_id)))||
                       ((is_lw_ex && write_ex && w_addr_ex != 5'b0)&&((rs==w_addr_ex)||(rt==w_addr_ex)))||
                       ((is_lw_mem && write_mem && w_addr_mem != 5'b0)&&((rs==w_addr_mem)||(rt==w_addr_mem))));
endmodule
