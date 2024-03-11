`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/28 22:31:58
// Design Name: 
// Module Name: pcpu
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


module dcpu(
    input clk,
    input rst,
    input [31:0] instr,
    input [4:0] raddr,
    output [31:0] pc,
    output [31:0] odata
    );
        
//IF阶段
    wire is_jump;   
    wire is_stall;      
    wire [31:0] npc_if;
    wire [31:0] pc_id;  
    wire [31:0] pc_if;  
    wire [31:0] instr_if;
    assign npc_if   = pc + 32'd4;
    assign pc_if    = (is_stall) ? pc : (is_jump) ? pc_id : npc_if;
    assign instr_if  = (is_stall) ? 32'b0 : instr;
    PC_reg PC_reg_inst(clk,rst,pc_if,pc);
    
//IF和ID之间的寄存器
    wire [31:0] instr_id;
    wire [31:0] npc_id;

    regs_IF_ID regs_IF_ID_inst(clk, rst, npc_if, instr_if, npc_id, instr_id);
    
//ID阶段
    //指令解码
    wire [5:0] op,func;
    wire [4:0] rs,rt,rd,shamt;
    wire [15:0] immediate;
    wire [25:0] index;
    wire [31:0] shamt_id;      
    wire [31:0] uimmediate_id;  
    wire [31:0] simmediate_id;    
    wire [31:0] offset; 
    assign func     = instr_id[5:0];
    assign shamt       = instr_id[10:6];
    assign immediate    = instr_id[15:0];
    assign index    = instr_id[25:0];
    assign op       = instr_id[31:26];
    assign rs       = instr_id[25:21];
    assign rt       = instr_id[20:16];
    assign rd       = instr_id[15:11];
    assign shamt_id     = {27'b0, shamt};
    assign uimmediate_id   = {16'b0, immediate};
    assign simmediate_id   = {{16{immediate[15]}}, immediate};
    assign offset = {{14{immediate[15]}}, immediate, 2'b0};

    //选择
    wire [31:0] rs_wire;  
    wire [31:0] rt_wire;  
    wire [1:0] mux_pc;      
    wire [31:0]  pc_offset;     
    wire [31:0]  pc_index;   
    wire [31:0] pc_rs;     
    assign pc_rs  = rs_wire;
    assign  pc_offset  = pc + offset;
    assign  pc_index  = {npc_if[31:28], index, 2'b0};
    assign pc_id = (mux_pc[1]) ?  pc_offset : (mux_pc[0]) ? pc_rs :  pc_index;

    //先写后读的专用路径
    wire write_ex;    
    wire write_mem;      
    wire [4:0] w_addr_ex; 
    wire [4:0] w_addr_mem;  
    wire is_lw_ex;
    wire is_jal_ex;
    wire is_mul_ex;
    wire is_lw_mem;
    wire is_jal_mem;
    wire is_mul_mem;
    wire [31:0] alu_ex;
    wire [31:0] mul_ex;
    wire [31:0] npc_ex;
    wire [31:0] alu_mem;
    wire [31:0] mul_mem;
    wire [31:0] npc_mem;
    wire conflict_lw;         
    wire [31:0] rs_mux;
    wire [31:0] rt_mux;

    mux mux_inst(rs, rt, rs_wire, rt_wire, npc_ex, mul_ex, alu_ex, w_addr_ex, write_ex, is_lw_ex, is_jal_ex, is_mul_ex,
            npc_mem, mul_mem, alu_mem, w_addr_mem, write_mem, is_lw_mem, is_jal_mem, is_mul_mem, rs_mux, rt_mux, conflict_lw);

    //ID段产生控制信号
    wire dm_w_signal_id;        
    wire write_id;       
    wire is_lw_id;
    wire is_jal_id;
    wire is_mul_id;
    wire [3:0] aluc_id;    
    wire [4:0] w_addr_id;    
    wire mux_alu1_id;           
    wire [1:0] mux_alu2_id;   
    wire [1:0] mux_w_addr_id;   
    wire [1:0] mux_wdata_id;   
    assign w_addr_id = (mux_w_addr_id[1]) ? 5'd31 : (mux_w_addr_id[0]) ? rd : rt;
    controller controller_inst(op, func, rs_mux, rt_mux, is_jump, dm_w_signal_id, write_id, aluc_id, mux_pc, mux_alu1_id, mux_alu2_id, mux_w_addr_id, is_lw_id, is_jal_id, is_mul_id);

    //判断有无冲突
    conflict_judge conflict_judge_inst(instr, is_lw_id, is_lw_ex, is_lw_mem, write_id, write_ex, write_mem, w_addr_id, w_addr_ex, w_addr_mem, is_stall);

//ID和EX段之间的寄存器
    wire [31:0] shamt_ex;
    wire [31:0] simmediate_ex;
    wire [31:0] uimmediate_ex;
    wire [31:0] rs_wire_ex;
    wire [31:0] rt_wire_ex;
    wire [3:0] aluc_ex;
    wire [31:0] dm_wdata_ex;
    wire dm_w_signal_ex;
    wire mux_alu1_ex;
    wire [1:0] mux_alu2_ex;
    wire [1:0] mux_wdata_ex;
    wire dm_w_id_real;
    assign dm_w_id_real = dm_w_signal_id && (~conflict_lw);

    regs_ID_EX regs_ID_EX_inst(clk,rst, dm_w_id_real, write_id, is_lw_id, is_jal_id, is_mul_id, mux_alu1_id,
                            mux_alu2_id, aluc_id, npc_id, w_addr_id, shamt_id, simmediate_id, uimmediate_id,
                            rs_mux, rt_mux, rt_mux, dm_w_signal_ex, write_ex, is_lw_ex, is_jal_ex, 
                            is_mul_ex, mux_alu1_ex, mux_alu2_ex, aluc_ex, npc_ex, w_addr_ex,
                            shamt_ex, simmediate_ex, uimmediate_ex, rs_wire_ex, rt_wire_ex, dm_wdata_ex);
    
//EX阶段
    wire [31:0] alu1;
    wire [31:0] alu2;
    assign alu1 = mux_alu1_ex ? shamt_ex : rs_wire_ex;
    assign alu2 = (mux_alu2_ex[1]) ? rt_wire_ex : (mux_alu2_ex[0]) ? uimmediate_ex : simmediate_ex;
    alu alu_inst(alu1,alu2,aluc_ex,alu_ex);

    wire [63:0] mul_out;
    assign mul_out = alu1 * alu2;
    assign mul_ex = mul_out[31:0];
    
//EX和MEM阶段之间的寄存器
    wire dm_w_signal_mem;
    wire [1:0] mux_wdata_mem;
    wire [31:0] dm_wdata_mem;

    regs_EX_MEM regs_EX_MEM_inst(clk, rst, dm_w_signal_ex, write_ex, is_lw_ex, is_jal_ex, is_mul_ex, w_addr_ex,
                              npc_ex, alu_ex, mul_ex,dm_wdata_ex,dm_w_signal_mem,write_mem,is_lw_mem, is_jal_mem, 
                              is_mul_mem, w_addr_mem, npc_mem, alu_mem, mul_mem, dm_wdata_mem);

//MEM阶段
    wire dm_w;
    wire [31:0] dm_addr;
    wire [31:0] dm_rdata;
    wire [31:0] dm_wdata;
    assign dm_addr = alu_mem;
    assign dm_wdata = dm_wdata_mem;
    assign dm_w = dm_w_signal_mem;
    dmem dmem_inst(~clk,rst,dm_w,dm_addr,dm_wdata,dm_rdata);
    
//MEM和WB阶段之间的寄存器
    wire write_wb;
    wire is_lw_wb;
    wire is_jal_wb;
    wire is_mul_wb;
    wire [4:0] w_addr_wb;
    wire [31:0] alu_wb;
    wire [31:0] mul_wb;
    wire [31:0] npc_wb;
    wire [31:0] dm_rdata_wb;
    wire [1:0] mux_wdata_wb;

    regs_MEM_WB regs_MEM_WB_inst(clk, rst, write_mem, is_lw_mem, is_jal_mem, is_mul_mem, w_addr_mem, alu_mem,
                            mul_mem, npc_mem, dm_rdata, write_wb, is_lw_wb, is_jal_wb, is_mul_wb,
                            w_addr_wb, alu_wb, mul_wb, npc_wb, dm_rdata_wb);
    
//WB阶段
    wire [31:0] wdata_wb;
    assign wdata_wb = (is_lw_wb) ? dm_rdata_wb : (is_jal_wb) ? npc_wb : (is_mul_wb) ? mul_wb : alu_wb;
    regfiles regfiles_inst(clk,rst,write_wb,rs,rt,w_addr_wb,raddr,wdata_wb,rs_wire,rt_wire,odata);
endmodule

