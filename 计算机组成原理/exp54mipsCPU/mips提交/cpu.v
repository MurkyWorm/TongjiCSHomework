`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/09 17:57:52
// Design Name: 
// Module Name: cpu
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


module cpu(
    input clk,
    input reset,
    input [31 : 0] inst,
    input [31 : 0] dmem_out,
    output [31 : 0] pc,
    output dmem_ena,
    output dmem_wena,
    output [31 : 0] dmem_addr,
    output [31 : 0] dmem_in,
    output [1 : 0] d_ram_instr
    );
    wire [31 : 0] vpc;
    wire [31 : 0] valu;
    wire zero;
    wire carry;
    wire negative;
    wire overflow;
    wire [31 : 0] vreg1;
    wire [31 : 0] vreg2;
    
    wire [31 : 0] vconcat;
    wire [31 : 0] vaddj;
    wire [31 : 0] vnpc;
    wire [31 : 0] vpc_8;
    wire [31 : 0] vext18;
    wire [31 : 0] vext16;
    wire [31 : 0] vext5;
    wire [31 : 0] vclz;
    wire [31 : 0] vcp0_addr;
    wire [31 : 0] vcp0_sta;
    wire [31 : 0] vcp0_rdata;
    wire [31 : 0] vhi;
    wire [31 : 0] vlo;
    wire [31 : 0] vmul1;
    wire [31 : 0] vmul2;
    wire [31 : 0] vdivider1;
    wire [31 : 0] vdivider2;
    wire [31 : 0] veo;
    wire [31 : 0] vmid;
    
    wire [31 : 0] vmux_1;
    wire [31 : 0] vmux_2;
    wire [31 : 0] vmux_3;
    wire [31 : 0] vmux_4;
    wire [31 : 0] vmux_5;
    wire [31 : 0] vmux_6;
    wire [31 : 0] vmux_7;
    wire [31 : 0] vmux_8;
    wire [31 : 0] vmux_9;
    
    wire pcreg_ena;
    wire ext5_s;
    wire ext16_s;
    wire ext18_s;
    wire reg_we;
    wire [4 : 0] reg_waddr;
    wire [4 : 0] reg_raddr1;
    wire [4 : 0] reg_raddr2;
    wire [3 : 0] aluc;
    wire M1;
    wire M2;
    wire [1 : 0] M3;
    wire [1 : 0] M4;
    wire M5;
    wire [1 : 0] M6;
    wire [2 : 0] M7;
    wire [1 : 0] M8;
    wire [1 : 0] M9;
    wire [1 : 0] eo_instr;
    wire [2 : 0] cp0_instr;
    wire cp0_ena;
    wire [4 : 0] cp0_cause;
    wire div_instr;
    wire mul_instr;
    wire hi_ena;
    wire lo_ena;
    
    assign pc = vpc;
    assign dmem_addr = valu;
    assign dmem_in = vreg2;
    
    controller cpu54controller_inst(inst, zero, negative, pcreg_ena, dmem_wena, dmem_ena, ext5_s, ext16_s, ext18_s, reg_we, reg_waddr, reg_raddr1, reg_raddr2, aluc, 
                                    M1, M2, M3, M4, M5, M6, M7, M8, M9, eo_instr, cp0_instr, cp0_ena, cp0_cause, div_instr, mul_instr, hi_ena, lo_ena, d_ram_instr);
    
    single_reg pcreg_inst(clk, reset, pcreg_ena, vmux_6, vpc);
    single_reg2 mid(clk, reset, 1, vreg1, vmid);
    single_reg2 hi(clk, reset, hi_ena, vmux_8, vhi);
    single_reg2 lo(clk, reset, lo_ena, vmux_9, vlo);
    
    alu alu_inst(vmux_2, vmux_5, aluc, valu, zero, carry, negative, overflow);
    clz clz_inst(vreg1, vclz);
    divider divider_inst(vreg1, vreg2, div_instr, vdivider2, vdivider1);
    mul mul_inst(vreg1, vreg2, mul_instr, vmul2, vmul1);
    
    regfile cpu_ref(clk, reset, reg_we, reg_raddr1, reg_raddr2, reg_waddr, vmux_7, vreg1, vreg2);
    cp0 cp0_inst(clk, rst, cp0_ena, cp0_instr[2], cp0_instr[1], cp0_instr[0], vnpc, vreg1[4 : 0], cp0_cause, vreg2, vcp0_rdata, vcp0_sta, vcp0_addr);
    
    concatenator concat(inst[25 : 0], vpc[31 : 28], vconcat);
    add addj(vnpc, vext18, vaddj);
    add npc(vpc, 4, vnpc);
    add pc_8(vpc, 4, vpc_8);
    ext #(.WIDTH(5)) ext5(inst[10 : 6], ext5_s, vext5);
    ext #(.WIDTH(16)) ext16(inst[15 : 0], ext16_s, vext16);
    ext #(.WIDTH(18)) ext18({{inst[15 : 0]}, {2'b00}}, ext18_s, vext18);
    ext_other ext_other_inst(dmem_out, eo_instr, veo);
    
    mux2 mux_1(vreg2, vext16, M1, vmux_1);
    mux2 mux_2(vext5, vreg1, M2, vmux_2);
    mux4 mux_3(vmid, vconcat, vnpc, vaddj, M3, vmux_3);
    mux4 mux_4(dmem_out, valu, vpc_8, vclz, M4, vmux_4);
    mux2 mux_5(vmux_1, 0, M5, vmux_5);
    mux4 mux_6(vmux_3, 32'h00400078, vcp0_addr, 0, M6, vmux_6);
    mux8 mux_7(vmux_4, veo, vcp0_rdata, vhi, vlo, vmul2, 0, 0, M7, vmux_7);
    mux4 mux_8(vdivider1, vreg1, vmul1, 0, M8, vmux_8);
    mux4 mux_9(vdivider2, vreg1, vmul2, 0, M9, vmux_9);
endmodule
