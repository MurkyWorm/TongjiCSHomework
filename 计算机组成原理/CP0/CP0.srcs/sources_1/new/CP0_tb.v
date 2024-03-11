`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/05 09:57:24
// Design Name: 
// Module Name: CP0_tb
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


module CP0_tb();
    reg clk;
    reg rst;
    reg exc;
    reg mfc0;
    reg mtc0;
    reg eret;
    reg [31:0] pc;
    reg [4:0] Rd;
    reg [4:0] cause;
    reg [31:0] wdata;
    wire [31:0] rdata;
    wire [31:0] status;
    wire [31:0] exc_addr;
    
    CP0 CP0_inst(clk, rst, exc, mfc0, mtc0, eret, pc, Rd, cause, wdata, rdata, status, exc_addr);
    
    parameter SYSCALL = 5'b01000,
               BREAK   = 5'b01001,
               TEQ     = 5'b01101;
    initial
    begin
        clk = 0;
    end
    always
    begin
        #5 clk = ~clk;
    end
    initial
    begin
        rst = 1;
        exc = 1;
        mfc0 = 0;
        mtc0 = 0;
        eret = 0;
        
        #10 rst = 0;
        #7 Rd = 12;
        wdata = 32'h0000000f;
        exc = 1;
        mtc0 = 1;
        
        #17 exc = 1;
        cause = BREAK;
        mfc0 = 0;
        mtc0 = 0;
        pc = 32'h40000004;
        
        #7 exc = 1;
        cause = 0;
        mfc0 = 0;
        mtc0 = 0;
        eret = 1;
        
        #7 mfc0 = 1;
        #10 Rd = 13;
    end
endmodule
