`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/09 11:05:45
// Design Name: 
// Module Name: ext_other
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


module ext_other(
    input [31 : 0] data_in,
    input [1 : 0] instr,
    output reg [31 : 0] data_out
    );
    always @ (*)
    begin
        if (instr == 0)
        begin
            data_out = {{24{data_in[7]}}, data_in[7 : 0]};
        end
        else if (instr == 1)
        begin
            data_out = {{24{1'b0}}, data_in[7 : 0]};
        end
        else if (instr == 2)
        begin
            data_out = {{16{data_in[7]}}, data_in[15 : 0]};
        end
        else
        begin
            data_out = {{16{1'b0}}, data_in[15 : 0]};
        end
    end
endmodule
