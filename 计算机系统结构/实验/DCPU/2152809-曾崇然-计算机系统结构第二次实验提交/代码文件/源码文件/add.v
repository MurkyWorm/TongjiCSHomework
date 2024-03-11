`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/28 22:40:45
// Design Name: 
// Module Name: adder
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


module cla4(
	input [3:0] gg, pp,
	input data_in,
	output ogg,	
	output oper,	
	output [4:1] data_out
	);
	assign data_out[1] = gg[0]|(pp[0]&data_in); 
	assign data_out[2] = gg[1]|(pp[1]&gg[0])|(pp[1]&pp[0]&data_in); 
	assign data_out[3] = gg[2]|(pp[2]&gg[1])|(pp[2]&pp[1]&gg[0])|(pp[2]&pp[1]&pp[0]&data_in); 
	assign data_out[4] = gg[3]|(pp[3]&gg[2])|(pp[3]&pp[2]&gg[1])|(pp[3]&pp[2]&pp[1]&gg[0])
					|(pp[3]&pp[2]&pp[1]&pp[0]&data_in); 
	assign ogg = gg[3]|(pp[3]&gg[2])|(pp[3]&pp[2]&gg[1])|(pp[3]&pp[2]&pp[1]&gg[0]);
	assign oper = pp[3]&pp[2]&pp[1]&pp[0];
endmodule

module add1(
	input add1, add2,
	input c,
	output gg,	
	output pp,	
	output data_out
	);
	assign gg = add1 & add2;
	assign pp = add1 | add2;
	assign data_out = add1 ^ add2 ^ c;
endmodule

module add4(
	input [3:0] add1,add2,
	input data_in,
	output ogg,	
	output oper,	
	output [3:0] s
	);
	wire [3:0] gg, pp;
	wire [4:1] c;
	add1 add_1(add1[0], add2[0], data_in, gg[0], pp[0], s[0]);
	add1 add_2(add1[1], add2[1], c[1], gg[1], pp[1], s[1]);
	add1 add_3(add1[2], add2[2], c[2], gg[2], pp[2], s[2]);
	add1 add_4(add1[3], add2[3], c[3], gg[3], pp[3], s[3]);
	cla4 cla4(gg, pp, data_in, ogg, oper, c);
endmodule

module add16(
	input [15:0] add1,add2,
	input data_in,
	output ogg,	
	output oper,	
	output [15:0] s
	);
	wire [3:0] gg,pp;
	wire [4:1] c;
	add4 add_1(add1[3:0], add2[3:0], data_in, gg[0], pp[0], s[3:0]);
	add4 add_2(add1[7:4], add2[7:4], c[1], gg[1], pp[1], s[7:4]);
	add4 add_3(add1[11:8], add2[11:8], c[2], gg[2], pp[2], s[11:8]);
	add4 add_4(add1[15:12], add2[15:12], c[3], gg[3], pp[3], s[15:12]);
	cla4 cla4(gg, pp, data_in, ogg, oper, c);
endmodule

module add32(
	input [31:0] add1,add2,
	input data_in,
	output [31:0] res,
	output data_out
	);
	wire temp;
	wire [1:0] gg, pp;
	assign temp = gg[0]|(pp[0]&data_in);
	assign data_out = gg[1]|(pp[1]&gg[0])|(pp[1]&pp[0]&data_in);
	add16 add_1(add1[15:0], add2[15:0], data_in, gg[0], pp[0], res[15:0]);
	add16 add_2(add1[31:16], add2[31:16], temp, gg[1], pp[1], res[31:16]);
endmodule

module neg32(
	input [31:0] data_in,
	input s,
	output [31:0] data_out
	);
	assign data_out[0] = s ^ data_in[0];
	assign data_out[1] = s ^ data_in[1];
	assign data_out[2] = s ^ data_in[2];
	assign data_out[3] = s ^ data_in[3];
	assign data_out[4] = s ^ data_in[4];
	assign data_out[5] = s ^ data_in[5];
	assign data_out[6] = s ^ data_in[6];
	assign data_out[7] = s ^ data_in[7];
	assign data_out[8] = s ^ data_in[8];
	assign data_out[9] = s ^ data_in[9];
	assign data_out[10] = s ^ data_in[10];
	assign data_out[11] = s ^ data_in[11];
	assign data_out[12] = s ^ data_in[12];
	assign data_out[13] = s ^ data_in[13];
	assign data_out[14] = s ^ data_in[14];
	assign data_out[15] = s ^ data_in[15];
	assign data_out[16] = s ^ data_in[16];
	assign data_out[17] = s ^ data_in[17];
	assign data_out[18] = s ^ data_in[18];
	assign data_out[19] = s ^ data_in[19];
	assign data_out[20] = s ^ data_in[20];
	assign data_out[21] = s ^ data_in[21];
	assign data_out[22] = s ^ data_in[22];
	assign data_out[23] = s ^ data_in[23];
	assign data_out[24] = s ^ data_in[24];
	assign data_out[25] = s ^ data_in[25];
	assign data_out[26] = s ^ data_in[26];
	assign data_out[27] = s ^ data_in[27];
	assign data_out[28] = s ^ data_in[28];
	assign data_out[29] = s ^ data_in[29];
	assign data_out[30] = s ^ data_in[30];
	assign data_out[31] = s ^ data_in[31];
endmodule

module add(
	input [31:0] add1,
	input [31:0] add2,
	input aluc,
	output [31:0] res
	);
	wire [31:0] b_real;
	wire c_in;
	wire c_out;
	assign c_in = aluc ? 1: 0;
	neg32 neg32(add2, aluc, b_real);
	add32 add32(add1, add2, c_in, res, c_out);
endmodule
