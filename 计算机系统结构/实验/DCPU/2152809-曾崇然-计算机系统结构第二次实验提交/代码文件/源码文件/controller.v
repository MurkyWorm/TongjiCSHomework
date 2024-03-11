`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/28 22:36:00
// Design Name: 
// Module Name: control
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


module controller(
    input [5:0] operation,
    input [5:0] funct,
    input [31:0] rs_wire,
    input [31:0] rt_wire,

    output is_jump,
    output dm_w_signal_id,
    output write_id,
    output [3:0] aluc_id,

    output [1:0] mux_pc, 
    output mux_alu1_id,
    output [1:0] mux_alu2_id, 
    output [1:0] mux_waddr_id,
    
    output is_lw_id,
    output is_jal_id,
    output is_mul_id
    );
    wire r_type = ~(operation[5]|operation[4]|operation[3]|operation[2]|operation[1]|operation[0]);
    wire ADD = r_type&funct[5]&~funct[4]&~funct[3]&~funct[2]&~funct[1]&~funct[0];
    wire ADDU = r_type&funct[5]&~funct[4]&~funct[3]&~funct[2]&~funct[1]&funct[0];
    wire SUB = r_type&funct[5]&~funct[4]&~funct[3]&~funct[2]&funct[1]&~funct[0];
    wire SUBU = r_type&funct[5]&~funct[4]&~funct[3]&~funct[2]&funct[1]&funct[0];
    wire AND = r_type&funct[5]&~funct[4]&~funct[3]&funct[2]&~funct[1]&~funct[0];
    wire OR = r_type&funct[5]&~funct[4]&~funct[3]&funct[2]&~funct[1]&funct[0];
    wire XOR = r_type&funct[5]&~funct[4]&~funct[3]&funct[2]&funct[1]&~funct[0];
    wire NOR = r_type&funct[5]&~funct[4]&~funct[3]&funct[2]&funct[1]&funct[0];
    wire SLT = r_type&funct[5]&~funct[4]&funct[3]&~funct[2]&funct[1]&~funct[0];
    wire SLTU = r_type&funct[5]&~funct[4]&funct[3]&~funct[2]&funct[1]&funct[0];
    wire SLL = r_type&~funct[5]&~funct[4]&~funct[3]&~funct[2]&~funct[1]&~funct[0];
    wire SRL = r_type&~funct[5]&~funct[4]&~funct[3]&~funct[2]&funct[1]&~funct[0];
    wire SRA = r_type&~funct[5]&~funct[4]&~funct[3]&~funct[2]&funct[1]&funct[0];
    wire SLLV = r_type&~funct[5]&~funct[4]&~funct[3]&funct[2]&~funct[1]&~funct[0];
    wire SRLV = r_type&~funct[5]&~funct[4]&~funct[3]&funct[2]&funct[1]&~funct[0];
    wire SRAV = r_type&~funct[5]&~funct[4]&~funct[3]&funct[2]&funct[1]&funct[0];
    wire JR = r_type&~funct[5]&~funct[4]&funct[3]&~funct[2]&~funct[1]&~funct[0];
    wire ADDI = ~operation[5]&~operation[4]&operation[3]&~operation[2]&~operation[1]&~operation[0];
    wire ADDIU = ~operation[5]&~operation[4]&operation[3]&~operation[2]&~operation[1]&operation[0];
    wire ANDI = ~operation[5]&~operation[4]&operation[3]&operation[2]&~operation[1]&~operation[0];
    wire ORI = ~operation[5]&~operation[4]&operation[3]&operation[2]&~operation[1]&operation[0];
    wire XORI = ~operation[5]&~operation[4]&operation[3]&operation[2]&operation[1]&~operation[0];
    wire LUI = ~operation[5]&~operation[4]&operation[3]&operation[2]&operation[1]&operation[0];
    wire LW = operation[5]&~operation[4]&~operation[3]&~operation[2]&operation[1]&operation[0];
    wire SW = operation[5]&~operation[4]&operation[3]&~operation[2]&operation[1]&operation[0];
    wire BEQ = ~operation[5]&~operation[4]&~operation[3]&operation[2]&~operation[1]&~operation[0];
    wire BNE = ~operation[5]&~operation[4]&~operation[3]&operation[2]&~operation[1]&operation[0];
    wire SLTI = ~operation[5]&~operation[4]&operation[3]&~operation[2]&operation[1]&~operation[0];
    wire SLTIU = ~operation[5]&~operation[4]&operation[3]&~operation[2]&operation[1]&operation[0];
    wire J = ~operation[5]&~operation[4]&~operation[3]&~operation[2]&operation[1]&~operation[0];
    wire JAL = ~operation[5]&~operation[4]&~operation[3]&~operation[2]&operation[1]&operation[0];
    wire MUL = (operation == 6'b011100 && funct == 6'b000010);

    assign is_lw_id = LW;
    assign is_jal_id = JAL;
    assign is_mul_id = MUL;

    assign dm_w_signal_id = SW;
    assign write_id = ~(JR|SW|BEQ|BNE|J);
    assign is_jump = JR|J|JAL|(BEQ&(rs_wire == rt_wire))|(BNE&(rs_wire != rt_wire));
    
    assign aluc_id[3] = LUI|SLL|SLLV|SLT|SLTI|SLTIU|SLTU|SRA|SRAV|SRL|SRLV;
    assign aluc_id[2] = AND|ANDI|NOR|OR|ORI|SLL|SLLV|SRA|SRAV|SRL|SRLV|XOR|XORI;
    assign aluc_id[1] = ADD|ADDI|BEQ|BNE|LW|NOR|SLL|SLLV|SLT|SLTI|SLTIU|SLTU|SUB|SW|XOR|XORI;
    assign aluc_id[0] = BEQ|BNE|NOR|OR|ORI|SLT|SLTI|SRL|SRLV|SUB|SUBU;

    assign mux_pc = (J|JAL)?2'b00:(JR)?2'b01:(BNE|BEQ)?2'b11:2'bxx;
    assign mux_alu1_id = SLL|SRA|SRL;
    assign mux_alu2_id[1] = ~(ADDI|ADDIU|LUI|LW|SLTI|SW|ANDI|ORI|SLTIU|XORI);
    assign mux_alu2_id[0] = ANDI|ORI|SLTIU|XORI;
    assign mux_waddr_id[1] = JAL;
    assign mux_waddr_id[0] = ~(ADDI|ADDIU|ANDI|LUI|LW|ORI|SLTI|SLTIU|XORI|JAL);
endmodule
