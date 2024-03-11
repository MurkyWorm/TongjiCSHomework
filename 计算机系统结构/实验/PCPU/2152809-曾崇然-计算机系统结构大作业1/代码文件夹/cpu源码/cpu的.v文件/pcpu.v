`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/25 21:56:56
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
`define idle 1'b0//CPU待机状态
`define exec 1'b1//CPU运行状态

//定义指令的操作码
`define NOP   4'b0000
`define HALT  4'b0001
`define ADD   4'b0010
`define ADDI  4'b0011
`define SUB   4'b0100
`define SUBI  4'b0101
`define SRL   4'b0110
`define CMP   4'b0111
`define JUMP  4'b1000
`define BN    4'b1001
`define BNN   4'b1010
`define BZ    4'b1011
`define BNZ   4'b1100
`define LOAD  4'b1101
`define STORE 4'b1110

module pcpu(
    input clk,//时钟
    input enable,//使能信号，高电平有效
    input reset,//复位信号，高电平有效
    input start,//CPU启动信号，高电平有效
    input [15:0] instruction,//输入的指令
    input [15:0] datain,//输入的数据
    output reg [7:0] i_addr,//指令地址
    output [7:0] d_addr,//数据地址
    output reg wena,//数据写入信号，高电平有效
    output [15:0] dataout//输出的数据
    );
    
    reg cpu_state;//CPU状态
    reg next_cpu_state;//CPU的下一个状态
    
    reg [15:0] id_input, ex_input, mem_input, wb_input;//各阶段从上一个阶段拿到的指令
    
    wire is_branch;//是否进行跳转的标志位
    
    reg [15:0] src_regA, src_regB;//两个源操作数寄存器
    reg [15:0] dst_regC1, dst_regC2;//两个目标寄存器，两个保证流水线不断
    reg [15:0] store_reg1, store_reg2;//用于store指令的两个寄存器，两个保证流水线不断
    
    reg [15:0] general_reg[15:0];//通用寄存器堆
    
    reg zf, nf, cf;//运算的标志位
    reg [15:0] ALU_result;//运算器的运算结果
    reg cf_buf;//存储溢出位
    
    //********************CPU状态切换*********************//
    //每次时钟上升沿切换到下一个状态，若遇到复位信号则待机
    always @ (posedge clk)
    begin
        if (reset)
            cpu_state <= `idle;
        else
            cpu_state <= next_cpu_state;
    end
    //根据当前状态和输入确定下一个状态
    always @ (*)
    begin
        if (cpu_state == `idle)
        begin
            if ((enable == 1'b1) && (start == 1'b1))
                next_cpu_state <= `exec;
            else
                next_cpu_state <= `idle;
        end
        else
        begin
            if ((enable == 1'b0) || (wb_input[15:12] == `HALT))
                next_cpu_state <= `idle;
            else
                next_cpu_state <= `exec;
        end
    end
    
    //**********************IF阶段************************//
    always @ (posedge clk or posedge reset)
    begin
        if (reset)
        begin
            id_input <= {`NOP, 12'b0000_0000_0000};
            i_addr <= 8'b0000_0000;
        end//复位
        else if (cpu_state == `exec)
        begin
            id_input <= instruction;
            if (is_branch)
                i_addr <= dst_regC1[7:0];
            else
                i_addr <= i_addr + 1;
        end//根据跳转标志位来决定下一条要取的指令
    end
    
    //**********************ID阶段************************//
    always @ (posedge clk or posedge reset)
    begin
        if (reset)
        begin
            ex_input <= {`NOP, 12'b0000_0000_0000};
            src_regA <= 16'b0000_0000_0000_0000;
            src_regB <= 16'b0000_0000_0000_0000;
            store_reg1 <= 16'b0000_0000_0000_0000;
        end//复位
        else if (cpu_state == `exec)
        begin
            ex_input <= id_input;
            if (id_input[15:12] == `STORE)
                store_reg1 <= general_reg[id_input[11:8]];
            else
                store_reg1 <= store_reg1;//根据指令类型置store_reg1寄存器
                
            if (id_input[15:12] == `JUMP)
                src_regA <= 16'b0000_0000_0000_0000;
            else if (id_input[15:12] == `ADDI || id_input[15:12] == `SUBI || id_input[15:12] == `BN || id_input[15:12] == `BNN || id_input[15:12] == `BZ || id_input[15:12] == `BNZ)
                src_regA <= general_reg[id_input[11:8]];
            else if (id_input[15:12] == `ADD || id_input[15:12] == `SUB || id_input[15:12] == `SUB || id_input[15:12] == `SRL || id_input[15:12] == `CMP ||  id_input[15:12] == `LOAD ||  id_input[15:12] == `STORE)
                src_regA <= general_reg[id_input[7:4]];
            else
                src_regA <= src_regA;//根据指令类型置源操作数寄存器A
                
            if (id_input[15:12] == `SRL || id_input[15:12] == `LOAD || id_input[15:12] == `STORE)
                src_regB <= {12'b0000_0000_0000, id_input[3:0]};
            else if (id_input[15:12] == `ADDI || id_input[15:12] == `SUBI || id_input[15:12] == `JUMP || id_input[15:12] == `BN || id_input[15:12] == `BNN || id_input[15:12] == `BZ || id_input[15:12] == `BNZ)
                src_regB <= {8'b0000_0000, id_input[7:0]};
            else if (id_input[15:12] == `ADD || id_input[15:12] == `SUB || id_input[15:12] == `CMP)
                src_regB <= general_reg[id_input[3:0]];
            else
                src_regB <= src_regB;//根据指令类型置源操作数寄存器B
        end
    end
    
    //**********************EX阶段************************//
    //设置标志位并传递store要存的值
    always @ (posedge clk or posedge reset)
    begin
        if (reset)
        begin
            mem_input <= {`NOP, 12'b0000_0000_0000};
            dst_regC1 <= 16'b0000_0000_0000_0000;
            store_reg2 <= 16'b0000_0000_0000_0000;
            wena <= 1'b0;
            zf <= 1'b0;
            nf <= 1'b0;
            cf <= 1'b0;
        end//复位
        else if (cpu_state == `exec)
        begin
            dst_regC1 <= ALU_result;
            mem_input <= ex_input;
            if (ex_input[15:12] == `ADD || ex_input[15:12] == `ADDI || ex_input[15:12] == `SUB || ex_input[15:12] == `SUBI || ex_input[15:12] == `SRL || ex_input[15:12] == `CMP)
            begin
                cf <= cf_buf;
                if (ALU_result == 16'b0000_0000_0000_0000)
                    zf <= 1'b1;
                else
                    zf <= 1'b0;
                if (ALU_result[15] == 1'b1)
                    nf <= 1'b1;
                else
                    nf <=1'b0;
            end
            else
            begin
                zf <= zf;
                nf <= nf;
                cf <= cf;
            end
            if (ex_input[15:12] == `STORE)
            begin
                wena <= 1'b1;
                store_reg2 <= store_reg1;
            end
            else
            begin
                wena <= 1'b0;
                store_reg2 <= store_reg1;
            end
        end
    end
    //根据指令的类型进行计算操作
    always @ (*)
    begin
        if (ex_input[15:12] == `SUB || ex_input[15:12] == `SUBI || ex_input[15:12] == `CMP)
            {cf_buf, ALU_result} <= src_regA - src_regB;
        else if (ex_input[15:12] == `SRL)
            {ALU_result[15:0], cf_buf} <= {src_regA[15:0], cf} >> src_regB[3:0];
            //{cf_buf, ALU_result[15:0]} <= 16'b0000_0000_0000_0000;
        else
            {cf_buf, ALU_result} <= src_regA + src_regB;
    end
    
    //**********************MEM阶段************************//
    assign d_addr = dst_regC1[7:0];
    assign dataout = store_reg2;
    assign is_branch = ((mem_input[15:12] == `JUMP)
                     || ((mem_input[15:12] == `BN) && (nf == 1'b1)) 
                     || ((mem_input[15:12] == `BNN) && (nf == 1'b0))
                     || ((mem_input[15:12] == `BZ) && (zf == 1'b1))
                     || ((mem_input[15:12] == `BNZ) && (zf == 1'b0)));
    always @ (posedge clk or posedge reset)
    begin
        if (reset)
        begin
            wb_input <= {`NOP, 12'b0000_0000_0000_0000};
            dst_regC2 <= 16'b0000_0000_0000_0000;
        end
        else if (cpu_state == `exec)
        begin
            wb_input <= mem_input;
            if (mem_input[15:12] == `LOAD)
                dst_regC2 <= datain;
            else
                dst_regC2 <= dst_regC1;
        end
    end
    
    //**********************WB阶段************************//
    always @ (posedge clk or posedge reset)
    begin
        if (reset)
        begin
            general_reg[0] <= 16'b0000000000000000;
            general_reg[1] <= 16'b0000000000000000;
            general_reg[2] <= 16'b0000000000000000;
            general_reg[3] <= 16'b0000000000000000;              
            general_reg[4] <= 16'b0000000000000000;
            general_reg[5] <= 16'b0000000000000000;
            general_reg[6] <= 16'b0000000000000000;
            general_reg[7] <= 16'b0000000000000000;
            general_reg[8] <= 16'b0000000000000000;
            general_reg[9] <= 16'b0000000000000000;
            general_reg[10] <= 16'b0000000000000000;
            general_reg[11] <= 16'b0000000000000000;              
            general_reg[12] <= 16'b0000000000000000;
            general_reg[13] <= 16'b0000000000000000;
            general_reg[14] <= 16'b0000000000000000;
            general_reg[15] <= 16'b0000000000000000;
        end
        else if (cpu_state == `exec)
        begin
            if (wb_input[15:12] == `ADD || wb_input[15:12] == `ADDI || wb_input[15:12] == `SUB || wb_input[15:12] == `SUBI ||wb_input[15:12] == `SRL || wb_input[15:12] == `LOAD)
                general_reg[wb_input[11:8]] <= dst_regC2;
        end
    end
endmodule
