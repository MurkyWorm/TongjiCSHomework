`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/08 22:58:56
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
    input [31 : 0] a, // 32 位输入，操作数 1
    input [31 : 0] b, // 32 位输入，操作数 2
    input [3 : 0] aluc, // 4 位输入，控制 alu 的操作
    output reg [31 : 0] r, // 32 位输出，有 a b 经过 aluc 指定的操作生成
    output reg zero, // 0 标志位
    output reg carry, // 进位标志位
    output reg negative, // 负数标志位
    output reg overflow //溢出标志位
    );
    reg [31 : 0] results [13 : 0];
    reg zeros [13 : 0];
    reg carrys [13 : 0];
    reg negatives [13 : 0];
    reg overflows [13 : 0];
    always @ (*)
    begin
        //无符号加法
        results[0] = a + b;
        if (results[0] == 32'h00000000)
        begin
            zeros[0] = 1;
        end
        else
        begin
            zeros[0] = 0;
        end
        if ($unsigned(results[0]) < $unsigned(a) || $unsigned(results[0]) < $unsigned(b))
        begin
            carrys[0] = 1;
        end
        else
        begin
            carrys[0] = 0;
        end
        if (results[0][31] == 1)
        begin
            negatives[0] = 1;
        end
        else
        begin
            negatives[0] = 0;
        end
        //有符号加法
        results[1] = a + b;
        if (results[1] == 32'h000000)
        begin
            zeros[1] = 1;
        end
        else
        begin
            zeros[1] = 0;
        end
        if (results[1][31] == 1)
        begin
            negatives[1] = 1;
        end
        else
        begin
            negatives[1] = 0;
        end
        if (a[31] == 1 && b[31] == 1 && results[1][31] == 0)
        begin
            overflows[1] = 1;
        end
        else if (a[31] == 0 && b[31] == 0 && results[1][31] ==1)
        begin
            overflows[1] = 1;
        end
        else
        begin
            overflows[1] = 0;
        end
        //无符号减法
        results[2] = a - b;
        if (results[2] == 32'h00000000)
        begin
            zeros[2] = 1;
        end
        else
        begin
            zeros[2] = 0;
        end
        if ($unsigned(a) < $unsigned(b))
        begin
            carrys[2] = 1;
        end
        else
        begin
            carrys[2] = 0;
        end
        if (results[2][31] == 1)
        begin
            negatives[2] = 1;
        end
        else
        begin
            negatives[2] = 0;
        end
        //有符号减法
        results[3] = a - b;
        if (results[3] == 32'h00000000)
        begin
            zeros[3] = 1;
        end
        else
        begin
            zeros[3] = 0;
        end
        if (results[3][31] == 1)
        begin
            negatives[3] = 1;
        end
        else
        begin
            negatives[3] = 0;
        end
        if (a[31] == 0 && b[31] == 1 && results[3][31] == 1)
        begin
            overflows[3] = 1;
        end
        else if (a[31] == 1 && b[31] == 0 && results[3][31] == 0)
        begin
            overflows[3] = 1;
        end
        else
        begin
            overflows[3] = 0;
        end
        //与运算
        results[4] = a & b;
        if (results[4] == 32'h00000000)
        begin
            zeros[4] = 1;
        end
        else
        begin
            zeros[4] = 0;
        end
        if (results[4][31] == 1)
        begin
            negatives[4] = 1;
        end
        else
        begin
            negatives[4] = 0;
        end
        //或运算
        results[5] = a | b;
        if (results[5] == 32'h00000000)
        begin
            zeros[5] = 1;
        end
        else
        begin
            zeros[5] = 0;
        end
        if (results[5][31] == 1)
        begin
            negatives[5] = 1;
        end
        else
        begin
            negatives[5] = 0;
        end
        //异或运算
        results[6] = a ^ b;
        if (results[6] == 32'h00000000)
        begin
            zeros[6] = 1;
        end
        else
        begin
            zeros[6] = 0;
        end
        if (results[6][31] == 1)
        begin
            negatives[6] = 1;
        end
        else
        begin
            negatives[6] = 0;
        end
        //或非运算
        results[7] = ~(a | b);
        if (results[7] == 32'h00000000)
        begin
            zeros[7] = 1;
        end
        else
        begin
            zeros[7] = 0;
        end
        if (results[7][31] == 1)
        begin
            negatives[7] = 1;
        end
        else
        begin
            negatives[7] = 0;
        end
        //lui运算
        results[8] = {b[15 : 0], 16'b0};
        if (results[8] == 32'h00000000)
        begin
            zeros[8] = 1;
        end
        else
        begin
            zeros[8] = 0;
        end
        carrys[8] = b[16];
        if (results[8][31] == 1)
        begin
            negatives[8] = 1;
        end
        else
        begin
            negatives[8] = 0;
        end
        //有符号比较
        results[9] = ($signed(a) < $signed(b)) ? 1 : 0;
        if (results[9] == 32'h00000000)
        begin
            zeros[9] = 1;
        end
        else
        begin
            zeros[9] = 0;
        end
        negatives[9] = 0;
        //无符号比较
        if ($unsigned(a) < $unsigned(b))
        begin
            results[10] = 1;
        end
        else
        begin
            results[10] = 0;
        end
        if (results[10] == 32'h00000000)
        begin
            zeros[10] = 1;
        end
        else
        begin
            zeros[10] = 0;
        end
        negatives[10] = 0;
        //算术右移
        results[11] = $signed(b) >>> a;
        if (results[11] == 0)
        begin
            zeros[11] = 1;
        end
        else
        begin
            zeros[11] = 0;
        end
        if (a != 0)
        begin
            if ($signed(a) <= 32)
            begin
                carrys[11] = b[a - 1];
            end
            else
            begin
                carrys[11] = b[31];
            end
        end
        if (results[11][31] == 1)
        begin
            negatives[11] = 1;
        end
        else
        begin
            negatives[11] = 0;
        end
        //逻辑左移/算术左移
        results[12] = b << a;
        if (results[12] == 32'h00000000)
        begin
            zeros[12] = 1;
        end
        else
        begin
            zeros[12] = 0;
        end
        if (a != 0)
        begin
            if ($signed(a) <= 32)
            begin
                carrys[12] = b[32 - a];
            end
            else
            begin
                carrys[12] = 0;
            end
        end
        if (results[12][31] == 1)
        begin
            negatives[12] = 1;
        end
        else
        begin
            negatives[12] = 0;
        end
        //逻辑右移
        results[13] = b >> a;
        if (results[13] == 32'h00000000)
        begin
            zeros[13] = 1;
        end
        else
        begin
            zeros[13] = 0;
        end
        if (a != 0)
        begin
            if ($signed(a) <= 32)
            begin
                carrys[13] = b[a - 1];
            end
            else
            begin
                carrys[13] = 0;
            end
        end
        if (results[13][31] == 1)
        begin
            negatives[13] = 1;
        end
        else
        begin
            negatives[13] = 0;
        end
        if (aluc == 4'b0000)//无符号加
        begin
            r = results[0];
            zero = zeros[0];
            carry = carrys[0];
            negative = negatives[0];
            overflow = overflows[0];
        end
        else if (aluc == 4'b0010)//有符号加
        begin
            r = results[1];
            zero = zeros[1];
            carry = carrys[1];
            negative = negatives[1];
            overflow = overflows[1];
        end
        else if (aluc == 4'b0001)//无符号减
        begin
            r = results[2];
            zero = zeros[2];
            carry = carrys[2];
            negative = negatives[2];
            overflow = overflows[2];
        end
        else if (aluc == 4'b0011)//有符号减
        begin
            r = results[3];
            zero = zeros[3];
            carry = carrys[3];
            negative = negatives[3];
            overflow = overflows[3];
        end
        else if (aluc == 4'b0100)//and
        begin
            r = results[4];
            zero = zeros[4];
            carry = carrys[4];
            negative = negatives[4];
            overflow = overflows[4];
        end
        else if (aluc == 4'b0101)//or
        begin
            r = results[5];
            zero = zeros[5];
            carry = carrys[5];
            negative = negatives[5];
            overflow = overflows[5];
        end
        else if (aluc == 4'b0110)//xor
        begin
            r = results[6];
            zero = zeros[6];
            carry = carrys[6];
            negative = negatives[6];
            overflow = overflows[6];
        end
        else if (aluc == 4'b0111)//nor
        begin
            r = results[7];
            zero = zeros[7];
            carry = carrys[7];
            negative = negatives[7];
            overflow = overflows[7];
        end
        else if (aluc == 4'b1000 || aluc == 4'b1001)//lui
        begin
            r = results[8];
            zero = zeros[8];
            carry = carrys[8];
            negative = negatives[8];
            overflow = overflows[8];
        end
        else if (aluc == 4'b1011)//slt
        begin
            r = results[9];
            zero = zeros[9];
            carry = carrys[9];
            negative = negatives[9];
            overflow = overflows[9];
        end
        else if (aluc == 4'b1010)//sltu
        begin
            r = results[10];
            zero = zeros[10];
            carry = carrys[10];
            negative = negatives[10];
            overflow = overflows[10];
        end
        else if (aluc == 4'b1100)//sra
        begin
            r = results[11];
            zero = zeros[11];
            carry = carrys[11];
            negative = negatives[11];
            overflow = overflows[11];
        end
        else if (aluc == 4'b1110 || aluc == 4'b1111)//sll
        begin
            r = results[12];
            zero = zeros[12];
            carry = carrys[12];
            negative = negatives[12];
            overflow = overflows[12];
        end
        else//srl
        begin
            r = results[13];
            zero = zeros[13];
            carry = carrys[13];
            negative = negatives[13];
            overflow = overflows[13];
        end
    end
endmodule
