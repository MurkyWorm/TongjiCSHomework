`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/28 22:43:26
// Design Name: 
// Module Name: luislt
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


module luislt(
	input [31:0] alu1,
    input [31:0] alu2,
    input [1:0] aluc,
    output reg [31:0] res
    );
	reg [2:0] cmp;
    reg res_low = 1'b0;
    wire [31:0] res_lui, res_slt;
    wire [32:0] alur1 = {1'b0, alu1};
    wire [32:0] alur2 = {1'b0, alu2};
    assign res_lui = {alu2[15:0], 16'b0};
    assign res_slt[31:1] = 0;
    assign res_slt[0] = res_low;

    always @(alur1 or alur2) 
    begin
        if(alur1 > alur2) 
        begin
            cmp = 3'b100; 
        end 
        else if(alur1 == alur2) 
        begin
            cmp = 3'b010; 
        end 
        else 
        begin
            cmp = 3'b001; 
        end
    end

    always @(*) 
    begin
        if(aluc[0] == 1'b1) 
        begin
            case({alu1[31], alu2[31]})
            2'b00: 
            begin
                res_low = cmp[0]; 
            end
            2'b01: 
            begin
                res_low = 1'b0; 
            end
            2'b10: 
            begin
                res_low = 1'b1; 
            end
            2'b11: 
            begin
                res_low = cmp[0];    
            end
            endcase 
        end 
        else 
        begin
            res_low = cmp[0]; 
        end
    end

    always @(aluc or res_lui or res_slt) 
    begin
        if(aluc[1]) 
        begin
            res = res_slt; 
        end 
        else 
        begin
            res = res_lui; 
        end
    end
endmodule
