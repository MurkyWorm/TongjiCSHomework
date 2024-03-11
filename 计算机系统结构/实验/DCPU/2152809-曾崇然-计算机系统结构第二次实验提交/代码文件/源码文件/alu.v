`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/28 22:39:45
// Design Name: 
// Module Name: alu
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


module alu(
    input [31:0] alu1,
	input [31:0] alu2,
	input [3:0] aluc,
	output reg [31:0] result
    );
	// ¼Ó¼õ·¨
    wire [31:0] result0;
    add add_inst(alu1, alu2, aluc[0], result0);

    // lui¼°slt
    wire [31:0] result1;
    luislt luislt_inst(alu1, alu2, aluc[1:0], result1);

    // result×îÖÕÊä³ö
    always @(*) 
    begin
        case(aluc[3:2])
        2'b00: 
        begin
            result = result0; 
        end
        2'b10: 
        begin
            result = result1; 
        end
        2'b01: 
        begin
            case(aluc[1:0])
            2'b00: 
            begin
                result = alu1 & alu2; 
            end
            2'b01: 
            begin
                result = alu1 | alu2; 
            end
            2'b10: 
            begin
                result = alu1 ^ alu2; 
            end
            default: 
            begin
                result = ~(alu1 | alu2); 
            end
            endcase 
        end
        2'b11: 
        begin 
            case(aluc[1:0])
            2'b00: 
            begin  
                result = alu1[0]? {alu2[31], alu2[31:1]}: alu2;
                result = alu1[1]? {{2{result[31]}}, result[31:2]}: result;
                result = alu1[2]? {{4{result[31]}}, result[31:4]}: result;
                result = alu1[3]? {{8{result[31]}}, result[31:8]}: result;
                result = alu1[4]? {{16{result[31]}}, result[31:16]}: result; 
            end 
            2'b01: 
            begin    //Âß¼­ÓÒÒÆ
                result = alu1[0]? {1'b0, alu2[31:1]}: alu2;
                result = alu1[1]? {2'b0, result[31:2]}: result;
                result = alu1[2]? {4'b0, result[31:4]}: result;
                result = alu1[3]? {8'b0, result[31:8]}: result;
                result = alu1[4]? {16'b0, result[31:16]}: result; 
            end
            default: 
            begin    //×óÒÆ
                result = alu1[0]? {alu2[30:0], 1'b0}: alu2;
                result = alu1[1]? {result[29:0], 2'b0}: result;
                result = alu1[2]? {result[27:0], 4'b0}: result;
                result = alu1[3]? {result[23:0], 8'b0}: result;
                result = alu1[4]? {result[15:0], 16'b0}: result; 
            end
            endcase 
        end
        default: 
        begin
            result = 32'b0; 
        end
        endcase
    end
endmodule