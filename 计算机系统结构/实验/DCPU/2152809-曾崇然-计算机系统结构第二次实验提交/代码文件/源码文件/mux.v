`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/28 22:34:56
// Design Name: 
// Module Name: mux
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


module mux(
    input [4:0] rs,
    input [4:0] rt,
    input [31:0] rs_wire,
    input [31:0] rt_wire,

    input [31:0] npc_ex,
    input [31:0] mul_ex,
    input [31:0] alu_ex,
    input [4:0] w_addr_ex,
    input write_ex,
    input is_lw_ex,
    input is_jal_ex,
    input is_mul_ex,

    input [31:0] npc_mem,
    input [31:0] mul_mem,
    input [31:0] alu_mem,
    input [4:0] w_addr_mem,
    input write_mem,
    input is_lw_mem,
    input is_jal_mem,
    input is_mul_mem,

    output reg [31:0] rs_mux = 32'b0,
    output reg [31:0] rt_mux = 32'b0,
    output reg conflict_lw = 1'b0
    );
    reg conflict_lw_rs = 1'b0;
    reg conflict_lw_rt = 1'b0;

    always @(*) 
    begin
        if(conflict_lw_rs || conflict_lw_rt)
        begin
            conflict_lw = 1'b1;
        end
        else 
        begin
            conflict_lw = 1'b0; 
        end
    end

    always @(*) 
    begin
        if(write_ex && w_addr_ex == rs && rs != 5'b0) 
        begin
            if(is_jal_ex) 
            begin
                conflict_lw_rs = 1'b0;
                rs_mux = npc_ex;   
            end
            else if(is_mul_ex) 
            begin
                conflict_lw_rs = 1'b0;  
                rs_mux = mul_ex;   
            end
            else if(is_lw_ex) 
            begin
                conflict_lw_rs = 1'b1;  
                rs_mux = 32'b0;     
            end
            else 
            begin
                conflict_lw_rs = 1'b0;  
                rs_mux = alu_ex;   
            end
        end
        else 
        begin
            if(write_mem && w_addr_mem == rs && rs != 5'b0)
            begin
                if(is_jal_mem) 
                begin
                    conflict_lw_rs = 1'b0;
                    rs_mux = npc_mem;   
                end
                else if(is_mul_mem) 
                begin
                    conflict_lw_rs = 1'b0;  
                    rs_mux = mul_mem;   
                end
                else if(is_lw_mem) 
                begin
                    conflict_lw_rs = 1'b1;  
                    rs_mux = 32'b0;     
                end
                else 
                begin
                    conflict_lw_rs = 1'b0;  
                    rs_mux = alu_mem;   
                end
            end
            else 
            begin
                conflict_lw_rs = 1'b0;  
                rs_mux = rs_wire;       
            end
        end
    end

    always @(*) 
    begin
        if(write_ex && w_addr_ex == rt && rt != 5'b0) 
        begin
            if(is_jal_ex) 
            begin
                conflict_lw_rt = 1'b0;  
                rt_mux = npc_ex;   
            end
            else if(is_mul_ex) 
            begin
                conflict_lw_rt = 1'b0;  
                rt_mux = mul_ex;   
            end
            else if(is_lw_ex) 
            begin
                conflict_lw_rt = 1'b1;  
                rt_mux = 32'b0;     
            end
            else 
            begin
                conflict_lw_rt = 1'b0;  
                rt_mux = alu_ex;   
            end
        end
        else 
        begin
            if(write_mem && w_addr_mem == rt && rt != 5'b0)
            begin
                if(is_jal_mem) 
                begin
                    conflict_lw_rt = 1'b0;  
                    rt_mux = npc_mem;   
                end
                else if(is_mul_mem) 
                begin
                    conflict_lw_rt = 1'b0;  
                    rt_mux = mul_mem;   
                end
                else if(is_lw_mem) 
                begin
                    conflict_lw_rt = 1'b1;  
                    rt_mux = 32'b0;     
                end
                else begin
                    conflict_lw_rt = 1'b0;  
                    rt_mux = alu_mem;   
                end
            end
            else 
            begin
                conflict_lw_rt = 1'b0;  
                rt_mux = rt_wire;       
            end
        end
    end
endmodule
