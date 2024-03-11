`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/09 11:26:39
// Design Name: 
// Module Name: controller
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
    input [31 : 0] instruction,
    input zero,
    input negative,
    output reg pcreg_ena,
    output reg d_ram_wena,
    output reg d_ram_ena,
    output reg ext5_s,
    output reg ext16_s,
    output reg ext18_s,
    output reg rf_we,
    output reg [4 : 0] rf_waddr,
    output reg [4 : 0] rf_raddr1,
    output reg [4 : 0] rf_raddr2,
    output reg [3 : 0] aluc,
    output reg M1,
    output reg M2,
    output [1 : 0] M3,
    output reg [1 : 0] M4,
    output reg M5,
    output [1 : 0] M6,
    output reg [2 : 0] M7,
    output reg [1 : 0] M8,
    output reg [1 : 0] M9,
    output reg [1 : 0] eo_instr,
    output reg [2 : 0] cp0_instr,
    output reg cp0_ena,
    output reg [4 : 0] cp0_cause,
    output reg div_instr,
    output reg mul_instr,
    output reg hi_ena,
    output reg lo_ena,
    output reg [1 : 0] d_ram_instr
    );
    reg [53 : 0] op;
    assign M3 = (op[16] || op[33] || op[34] || op[49] || op[52]) ? 2'b00 : ((op[29] || op[30]) ? 2'b01 : (op[24] ? {{1'b1}, {zero}} : (op[25] ? {{1'b1}, {~zero}} : (op[51] ? {{1'b1}, {~negative}} : 2'b10))));//
    assign M6 = op[33] ? 2'b10 : ((op[49] || op[52]) ? 2'b01 : (op[50] ? {1'b0, zero} : 2'b00));
    always @ (instruction)
    begin
        if (instruction[31 : 26] == 6'b000000)
        begin
            if (instruction[5 : 0] == 6'b100000)
            begin
                op = 54'b000000000000000000000000000000000000000000000000000001;
                aluc = 4'b0010;
            end
            else if (instruction[5 : 0] == 6'b100001)
            begin
                op = 54'b000000000000000000000000000000000000000000000000000010;
                aluc = 4'b0000;
            end
            else if (instruction[5 : 0] == 6'b100010)
            begin
                op = 54'b000000000000000000000000000000000000000000000000000100;
                aluc = 4'b0011;
            end
            else if (instruction[5 : 0] == 6'b100011)
            begin
                op = 54'b000000000000000000000000000000000000000000000000001000;
                aluc = 4'b0001;
            end
            else if (instruction[5 : 0] == 6'b100100)
            begin
                op = 54'b000000000000000000000000000000000000000000000000010000;
                aluc = 4'b0100;
            end
            else if (instruction[5 : 0] == 6'b100101)
            begin
                op = 54'b000000000000000000000000000000000000000000000000100000;
                aluc = 4'b0101;
            end
            else if (instruction[5 : 0] == 6'b100110)
            begin
                op = 54'b000000000000000000000000000000000000000000000001000000;
                aluc = 4'b0110;
            end
            else if (instruction[5 : 0] == 6'b100111)
            begin
                op = 54'b000000000000000000000000000000000000000000000010000000;
                aluc = 4'b0111;
            end
            else if (instruction[5 : 0] == 6'b101010)
            begin
                op = 54'b000000000000000000000000000000000000000000000100000000;
                aluc = 4'b1011;
            end
            else if (instruction[5 : 0] == 6'b101011)
            begin
                op = 54'b000000000000000000000000000000000000000000001000000000;
                aluc = 4'b1010;
            end
            else if (instruction[5 : 0] == 6'b000000)
            begin
                op = 54'b000000000000000000000000000000000000000000010000000000;
                aluc = 4'b1110;
            end
            else if (instruction[5 : 0] == 6'b000010)
            begin
                op = 54'b000000000000000000000000000000000000000000100000000000;
                aluc = 4'b1101;
            end
            else if (instruction[5 : 0] == 6'b000011)
            begin
                op = 54'b000000000000000000000000000000000000000001000000000000;
                aluc = 4'b1100;
            end
            else if (instruction[5 : 0] == 6'b000100)
            begin
                op = 54'b000000000000000000000000000000000000000010000000000000;
                aluc = 4'b1110;
            end
            else if (instruction[5 : 0] == 6'b000110)
            begin
                op = 54'b000000000000000000000000000000000000000100000000000000;
                aluc = 4'b1101;
            end
            else if (instruction[5 : 0] == 6'b000111)
            begin
                op = 54'b000000000000000000000000000000000000001000000000000000;
                aluc = 4'b1100;
            end
            else if (instruction[5 : 0] == 6'b001000)
            begin
                op = 54'b000000000000000000000000000000000000010000000000000000;
                aluc = 0;
            end
            else if (instruction[5 : 0] == 6'b011011)
            begin
                op = 54'b000000000000000000000100000000000000000000000000000000;
                aluc = 0;
            end
            else if (instruction[5 : 0] == 6'b001001)
            begin
                op = 54'b000000000000000000010000000000000000000000000000000000;
                aluc = 0;
            end
            else if (instruction[5 : 0] == 6'b010000)
            begin
                op = 54'b000000000001000000000000000000000000000000000000000000;
                aluc = 0;
            end
            else if (instruction[5 : 0] == 6'b010010)
            begin
                op = 54'b000000000010000000000000000000000000000000000000000000;
                aluc = 0;
            end
            else if (instruction[5 : 0] == 6'b010001)
            begin
                op = 54'b000000001000000000000000000000000000000000000000000000;
                aluc = 0;
            end
            else if (instruction[5 : 0] == 6'b010011)
            begin
                op = 54'b000000010000000000000000000000000000000000000000000000;
                aluc = 0;
            end
            else if (instruction[5 : 0] == 6'b011001)
            begin
                op = 54'b000001000000000000000000000000000000000000000000000000;
                aluc = 0;
            end
            else if (instruction[5 : 0] == 6'b001100)
            begin
                op = 54'b000010000000000000000000000000000000000000000000000000;
                aluc = 0;
            end
            else if (instruction[5 : 0] == 6'b110100)
            begin
                op = 54'b000100000000000000000000000000000000000000000000000000;
                aluc = 4'b0011;
            end
            else if (instruction[5 : 0] == 6'b001101)
            begin
                op = 54'b010000000000000000000000000000000000000000000000000000;
                aluc = 0;
            end
            else if (instruction[5 : 0] == 6'b011010)
            begin
                op = 54'b100000000000000000000000000000000000000000000000000000;
                aluc = 0;
            end
        end
        else if (instruction[31 : 26] == 6'b000010)
        begin
            op = 54'b000000000000000000000000100000000000000000000000000000;
            aluc = 0;
        end
        else if (instruction[31 : 26] == 6'b000011)
        begin
            op = 54'b000000000000000000000001000000000000000000000000000000;
            aluc = 0;
        end
        else if (instruction[31 : 26] == 6'b001000)
        begin
            op = 54'b000000000000000000000000000000000000100000000000000000;
            aluc = 4'b0010;
        end
        else if (instruction[31 : 26] == 6'b001001)
        begin
            op = 54'b000000000000000000000000000000000001000000000000000000;
            aluc = 4'b0000;
        end
        else if (instruction[31 : 26] == 6'b001100)
        begin
            op = 54'b000000000000000000000000000000000010000000000000000000;
            aluc = 4'b0100;
        end
        else if (instruction[31 : 26] == 6'b001101)
        begin
            op = 54'b000000000000000000000000000000000100000000000000000000;
            aluc = 4'b0101;
        end
        else if (instruction[31 : 26] == 6'b001110)
        begin
            op = 54'b000000000000000000000000000000001000000000000000000000;
            aluc = 4'b0110;
        end
        else if (instruction[31 : 26] == 6'b100011)
        begin
            op = 54'b000000000000000000000000000000010000000000000000000000;
            aluc = 4'b0000;
        end
        else if (instruction[31 : 26] == 6'b101011)
        begin
            op = 54'b000000000000000000000000000000100000000000000000000000;
            aluc = 4'b0000;
        end
        else if (instruction[31 : 26] == 6'b000100)
        begin
            op = 54'b000000000000000000000000000001000000000000000000000000;
            aluc = 4'b0011;
        end
        else if (instruction[31 : 26] == 6'b000101)
        begin
            op = 54'b000000000000000000000000000010000000000000000000000000;
            aluc = 4'b0011;
        end
        else if (instruction[31 : 26] == 6'b001010)
        begin
            op = 54'b000000000000000000000000000100000000000000000000000000;
            aluc = 4'b1011;
        end  
        else if (instruction[31 : 26] == 6'b001011)
        begin
            op = 54'b000000000000000000000000001000000000000000000000000000;
            aluc = 4'b1010;
        end  
        else if (instruction[31 : 26] == 6'b001111)
        begin
            op = 54'b000000000000000000000000010000000000000000000000000000;
            aluc = 4'b1000;
        end  
        else if (instruction[31 : 26] == 6'b011100)
        begin
            if (instruction[5 : 0] == 6'b100000)
            begin
                op = 54'b000000000000000000000010000000000000000000000000000000;
                aluc = 0;
            end
            else if (instruction[5 : 0] == 6'b000010)
            begin
                op = 54'b000000100000000000000000000000000000000000000000000000;
                aluc = 0;
            end
        end 
        else if (instruction[31 : 26] == 6'b010000)
        begin
            if (instruction[5 : 0] == 6'b011000)
            begin
                op = 54'b000000000000000000001000000000000000000000000000000000;
                aluc = 0;
            end
            else if (instruction[5 : 0] == 6'b000000)
            begin
                if (instruction[31 : 20] == 12'b010000000000)
                begin
                    op = 54'b000000000000100000000000000000000000000000000000000000;
                    aluc = 0;
                end
                else if (instruction[31 : 20] == 12'b010000001000)
                begin
                    op = 54'b000000000100000000000000000000000000000000000000000000;
                    aluc = 0;
                end
            end
        end
        else if (instruction[31 : 26] == 6'b100000)
        begin
            op = 54'b000000000000000000100000000000000000000000000000000000;
            aluc = 4'b0000;
        end
        else if (instruction[31 : 26] == 6'b100100)
        begin
            op = 54'b000000000000000001000000000000000000000000000000000000;
            aluc = 4'b0000;
        end
        else if (instruction[31 : 26] == 6'b100101)
        begin
            op = 54'b000000000000000010000000000000000000000000000000000000;
            aluc = 4'b0000;
        end
        else if (instruction[31 : 26] == 6'b101000)
        begin
            op = 54'b000000000000000100000000000000000000000000000000000000;
            aluc = 4'b0000;
        end
        else if (instruction[31 : 26] == 6'b101001)
        begin
            op = 54'b000000000000001000000000000000000000000000000000000000;
            aluc = 4'b0000;
        end
        else if (instruction[31 : 26] == 6'b100001)
        begin
            op = 54'b000000000000010000000000000000000000000000000000000000;
            aluc = 4'b0000;
        end
        else if (instruction[31 : 26] == 6'b000001)
        begin
            op = 54'b001000000000000000000000000000000000000000000000000000;
            aluc = 4'b0011;
        end
        pcreg_ena = 1;//
        d_ram_wena = op[23] || op[38] || op[39];//
        d_ram_ena = op[22] || op[23] || op[35] || op[36] || op[37] || op[38] || op[39] || op[40];//
        ext5_s = 0;//
        ext16_s = op[17] || op[18] || op[22] || op[23] || op[26] || op[27] || op[35] || op[36] || op[37] || op[38] || op[39] || op[40];//
        ext18_s = op[24] || op[25] || op[51];//
        rf_we = ~(op[16] || op[23] || op[24] || op[25] || op[29] || op[32] || op[33] || op[38] || op[39] || op[44] || op[45] || op[46] || op[48] || op[49] || op[50] || op[51] || op[52] || op[53]);//
        if (op[17] || op[18] || op[19] || op[20] || op[21] || op[22] || op[26] || op[27] || op[28] || op[35] || op[36] || op[37] || op[40] || op[41])
        begin
            rf_waddr = instruction[20 : 16];
        end
        else if (op[16] || op[23] || op[24] || op[25] || op[29] || op[32] || op[33] || op[38] || op[39] || op[44] || op[45] || op[46] || op[48] || op[49] || op[50] || op[51] || op[52] || op[53])
        begin
            rf_waddr = 0;
        end
        else if (op[30])
        begin
            rf_waddr = 5'b11111;
        end
        else
        begin
            rf_waddr = instruction[15 : 11];
        end//
        if (op[10] || op[11] || op[12] || op[28] || op[29] || op[30] || op[33] || op[42] || op[43] || op[49] || op[52])
        begin
            rf_raddr1 = 0;
        end
        else if(op[41])
        begin
            rf_raddr1 = instruction[15 : 11];
        end
        else if (op[44])
        begin
            rf_raddr1 = instruction[20 : 16];
        end
        else
        begin
            rf_raddr1 = instruction[25 : 21];
        end//
        if (op[16] || op[17] || op[18] || op[19] || op[20] || op[21] || op[22] || op[26] || op[27] || op[28] || op[29] || op[30] || op[31] || op[33] || op[34] || op[35] || op[36] || op[37] || op[40] || op[41] || op[42] || op[43] || op[45] || op[46] || op[49] || op[52])
        begin
            rf_raddr2 = 0;
        end
        else if (op[44])
        begin
            rf_raddr2 = instruction[15 : 11];
        end
        else
        begin
            rf_raddr2 = instruction[20 : 16];
        end//
        M1 = op[17] || op[18] || op[19] || op[20] || op[21] || op[22] || op[23] || op[26] || op[27] || op[28] || op[35] || op[36] || op[37] || op[38] || op[39] || op[40];//
        M2 = ~(op[10] || op[11] || op[12] || op[16] || op[28] || op[29] || op[30] || op[31] || op[32] || op[33] || op[34] || op[41] || op[42] || op[43] || op[44] || op[45] || op[46] || op[47] || op[48] || op[49] || op[52] || op[53]);//
        if (op[16] || op[22] || op[23] || op[24] || op[25] || op[29] || op[32] || op[33] || op[35] || op[36] || op[37] || op[38] || op[39] || op[40] || op[41] || op[42] || op[43] || op[44] || op[45] || op[46] || op[47] || op[48] || op[49] || op[50] || op[51] || op[52] || op[53])
        begin
            M4 = 2'b00;
        end
        else if (op[30] || op[34])
        begin
            M4 = 2'b10;
        end
        else if (op[31])
        begin
            M4 = 2'b11;
        end
        else
        begin
            M4 = 2'b01;
        end//
        M5 = op[51];//
        if (op[35] || op[36] || op[37] || op[40])
        begin
            M7 = 3'b001;
        end
        else if (op[41])
        begin
            M7 = 3'b010;
        end
        else if (op[42])
        begin
            M7 = 3'b011;
        end
        else if (op[43])
        begin
            M7 = 3'b100;
        end
        else if (op[47])
        begin
            M7 = 3'b101;
        end
        else
        begin
            M7 = 3'b000;
        end//
        if (op[45])
        begin
            M8 = 2'b01;
        end
        else if (op[48])
        begin
            M8 = 2'b10;
        end
        else
        begin
            M8 = 2'b00;
        end//
        if (op[46])
        begin
            M9 = 2'b01;
        end
        else if (op[48])
        begin
            M9 = 2'b10;
        end
        else
        begin
            M9 = 2'b00;
        end
        if (op[36])
        begin
            eo_instr = 2'b01;
        end
        else if (op[37])
        begin
            eo_instr = 2'b11;
        end
        else if (op[40])
        begin
            eo_instr = 2'b10;
        end
        else
        begin
            eo_instr = 2'b00;
        end//
        if (op[33])
        begin
            cp0_instr = 3'b001;
        end
        else if (op[41])
        begin
            cp0_instr = 3'b100;
        end
        else if (op[44])
        begin
            cp0_instr = 3'b010;
        end
        else
        begin
            cp0_instr = 3'b000;
        end//
        cp0_ena = op[33] || op[41] || op[44] || op[49] || op[52];//
        if (op[49])
        begin
            cp0_cause = 5'b01000;
        end
        else if (op[50])
        begin
            cp0_cause = 5'b01101;
        end
        else if (op[52])
        begin
            cp0_cause = 5'b01001;
        end
        else
        begin
            cp0_cause = 5'b00000;
        end//
        div_instr = op[32];//
        mul_instr = op[48];//
        hi_ena = op[32] || op[45] || op[48] || op[53];//
        lo_ena = op[32] || op[46] || op[48] || op[53];//
        if (op[38])
        begin
            d_ram_instr = 2'b01;
        end
        else if (op[39])
        begin
            d_ram_instr = 2'b10;
        end
        else
        begin
            d_ram_instr = 2'b00;
        end//
        if (instruction == 32'hffffffff)
        begin
            pcreg_ena = 0;
            rf_we = 0;
        end
    end
endmodule
