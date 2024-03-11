`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/09 10:42:16
// Design Name: 
// Module Name: clz
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


module clz(
    input [31 : 0] a,
    output reg [31 : 0] r
    );
    integer i;
    reg [31 : 0] temp;
    reg found;
    always @ (*)
    begin
        temp = 32;
        found = 0;
        for (i = 31; i >= 0 && found == 0; i = i - 1) 
        begin
            if (a[i] == 1)
            begin
                temp = 31 - i;
                found = 1;
            end
        end
        r = temp;
    end
endmodule
