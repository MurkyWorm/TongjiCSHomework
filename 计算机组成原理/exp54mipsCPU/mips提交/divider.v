`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/05 16:27:38
// Design Name: 
// Module Name: divider
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


module divider(
    input [31 : 0] a,
    input [31 : 0] b,
    input instr,
    output reg [31 : 0] lo,
    output reg [31 : 0] hi
    );
    always @ (*)
    begin
        if (instr)
        begin
            lo = a / b;
            hi = a % b;
        end
        else
        begin
            lo = $signed(a) / $signed(b);
            hi = $signed(a) % $signed(b);
        end
    end
endmodule
