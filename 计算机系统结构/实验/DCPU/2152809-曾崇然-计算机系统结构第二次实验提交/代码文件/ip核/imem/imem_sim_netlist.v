// Copyright 1986-2016 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2016.2 (win64) Build 1577090 Thu Jun  2 16:32:40 MDT 2016
// Date        : Sun Dec 31 09:34:03 2023
// Host        : jing running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim
//               D:/Computer_System_Structure/DCPU/DCPU.srcs/sources_1/ip/imem/imem_sim_netlist.v
// Design      : imem
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "imem,dist_mem_gen_v8_0_10,{}" *) (* downgradeipidentifiedwarnings = "yes" *) (* x_core_info = "dist_mem_gen_v8_0_10,Vivado 2016.2" *) 
(* NotValidForBitStream *)
module imem
   (a,
    spo);
  input [10:0]a;
  output [31:0]spo;

  wire [10:0]a;
  wire [31:0]spo;
  wire [31:0]NLW_U0_dpo_UNCONNECTED;
  wire [31:0]NLW_U0_qdpo_UNCONNECTED;
  wire [31:0]NLW_U0_qspo_UNCONNECTED;

  (* C_FAMILY = "artix7" *) 
  (* C_HAS_D = "0" *) 
  (* C_HAS_DPO = "0" *) 
  (* C_HAS_DPRA = "0" *) 
  (* C_HAS_I_CE = "0" *) 
  (* C_HAS_QDPO = "0" *) 
  (* C_HAS_QDPO_CE = "0" *) 
  (* C_HAS_QDPO_CLK = "0" *) 
  (* C_HAS_QDPO_RST = "0" *) 
  (* C_HAS_QDPO_SRST = "0" *) 
  (* C_HAS_WE = "0" *) 
  (* C_MEM_TYPE = "0" *) 
  (* C_PIPELINE_STAGES = "0" *) 
  (* C_QCE_JOINED = "0" *) 
  (* C_QUALIFY_WE = "0" *) 
  (* C_REG_DPRA_INPUT = "0" *) 
  (* KEEP_HIERARCHY = "true" *) 
  (* c_addr_width = "11" *) 
  (* c_default_data = "0" *) 
  (* c_depth = "2048" *) 
  (* c_elaboration_dir = "./" *) 
  (* c_has_clk = "0" *) 
  (* c_has_qspo = "0" *) 
  (* c_has_qspo_ce = "0" *) 
  (* c_has_qspo_rst = "0" *) 
  (* c_has_qspo_srst = "0" *) 
  (* c_has_spo = "1" *) 
  (* c_mem_init_file = "imem.mif" *) 
  (* c_parser_type = "1" *) 
  (* c_read_mif = "1" *) 
  (* c_reg_a_d_inputs = "0" *) 
  (* c_sync_enable = "1" *) 
  (* c_width = "32" *) 
  imem_dist_mem_gen_v8_0_10 U0
       (.a(a),
        .clk(1'b0),
        .d({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .dpo(NLW_U0_dpo_UNCONNECTED[31:0]),
        .dpra({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .i_ce(1'b1),
        .qdpo(NLW_U0_qdpo_UNCONNECTED[31:0]),
        .qdpo_ce(1'b1),
        .qdpo_clk(1'b0),
        .qdpo_rst(1'b0),
        .qdpo_srst(1'b0),
        .qspo(NLW_U0_qspo_UNCONNECTED[31:0]),
        .qspo_ce(1'b1),
        .qspo_rst(1'b0),
        .qspo_srst(1'b0),
        .spo(spo),
        .we(1'b0));
endmodule

(* C_ADDR_WIDTH = "11" *) (* C_DEFAULT_DATA = "0" *) (* C_DEPTH = "2048" *) 
(* C_ELABORATION_DIR = "./" *) (* C_FAMILY = "artix7" *) (* C_HAS_CLK = "0" *) 
(* C_HAS_D = "0" *) (* C_HAS_DPO = "0" *) (* C_HAS_DPRA = "0" *) 
(* C_HAS_I_CE = "0" *) (* C_HAS_QDPO = "0" *) (* C_HAS_QDPO_CE = "0" *) 
(* C_HAS_QDPO_CLK = "0" *) (* C_HAS_QDPO_RST = "0" *) (* C_HAS_QDPO_SRST = "0" *) 
(* C_HAS_QSPO = "0" *) (* C_HAS_QSPO_CE = "0" *) (* C_HAS_QSPO_RST = "0" *) 
(* C_HAS_QSPO_SRST = "0" *) (* C_HAS_SPO = "1" *) (* C_HAS_WE = "0" *) 
(* C_MEM_INIT_FILE = "imem.mif" *) (* C_MEM_TYPE = "0" *) (* C_PARSER_TYPE = "1" *) 
(* C_PIPELINE_STAGES = "0" *) (* C_QCE_JOINED = "0" *) (* C_QUALIFY_WE = "0" *) 
(* C_READ_MIF = "1" *) (* C_REG_A_D_INPUTS = "0" *) (* C_REG_DPRA_INPUT = "0" *) 
(* C_SYNC_ENABLE = "1" *) (* C_WIDTH = "32" *) (* ORIG_REF_NAME = "dist_mem_gen_v8_0_10" *) 
module imem_dist_mem_gen_v8_0_10
   (a,
    d,
    dpra,
    clk,
    we,
    i_ce,
    qspo_ce,
    qdpo_ce,
    qdpo_clk,
    qspo_rst,
    qdpo_rst,
    qspo_srst,
    qdpo_srst,
    spo,
    dpo,
    qspo,
    qdpo);
  input [10:0]a;
  input [31:0]d;
  input [10:0]dpra;
  input clk;
  input we;
  input i_ce;
  input qspo_ce;
  input qdpo_ce;
  input qdpo_clk;
  input qspo_rst;
  input qdpo_rst;
  input qspo_srst;
  input qdpo_srst;
  output [31:0]spo;
  output [31:0]dpo;
  output [31:0]qspo;
  output [31:0]qdpo;

  wire \<const0> ;
  wire [10:0]a;
  wire [31:0]\^spo ;

  assign dpo[31] = \<const0> ;
  assign dpo[30] = \<const0> ;
  assign dpo[29] = \<const0> ;
  assign dpo[28] = \<const0> ;
  assign dpo[27] = \<const0> ;
  assign dpo[26] = \<const0> ;
  assign dpo[25] = \<const0> ;
  assign dpo[24] = \<const0> ;
  assign dpo[23] = \<const0> ;
  assign dpo[22] = \<const0> ;
  assign dpo[21] = \<const0> ;
  assign dpo[20] = \<const0> ;
  assign dpo[19] = \<const0> ;
  assign dpo[18] = \<const0> ;
  assign dpo[17] = \<const0> ;
  assign dpo[16] = \<const0> ;
  assign dpo[15] = \<const0> ;
  assign dpo[14] = \<const0> ;
  assign dpo[13] = \<const0> ;
  assign dpo[12] = \<const0> ;
  assign dpo[11] = \<const0> ;
  assign dpo[10] = \<const0> ;
  assign dpo[9] = \<const0> ;
  assign dpo[8] = \<const0> ;
  assign dpo[7] = \<const0> ;
  assign dpo[6] = \<const0> ;
  assign dpo[5] = \<const0> ;
  assign dpo[4] = \<const0> ;
  assign dpo[3] = \<const0> ;
  assign dpo[2] = \<const0> ;
  assign dpo[1] = \<const0> ;
  assign dpo[0] = \<const0> ;
  assign qdpo[31] = \<const0> ;
  assign qdpo[30] = \<const0> ;
  assign qdpo[29] = \<const0> ;
  assign qdpo[28] = \<const0> ;
  assign qdpo[27] = \<const0> ;
  assign qdpo[26] = \<const0> ;
  assign qdpo[25] = \<const0> ;
  assign qdpo[24] = \<const0> ;
  assign qdpo[23] = \<const0> ;
  assign qdpo[22] = \<const0> ;
  assign qdpo[21] = \<const0> ;
  assign qdpo[20] = \<const0> ;
  assign qdpo[19] = \<const0> ;
  assign qdpo[18] = \<const0> ;
  assign qdpo[17] = \<const0> ;
  assign qdpo[16] = \<const0> ;
  assign qdpo[15] = \<const0> ;
  assign qdpo[14] = \<const0> ;
  assign qdpo[13] = \<const0> ;
  assign qdpo[12] = \<const0> ;
  assign qdpo[11] = \<const0> ;
  assign qdpo[10] = \<const0> ;
  assign qdpo[9] = \<const0> ;
  assign qdpo[8] = \<const0> ;
  assign qdpo[7] = \<const0> ;
  assign qdpo[6] = \<const0> ;
  assign qdpo[5] = \<const0> ;
  assign qdpo[4] = \<const0> ;
  assign qdpo[3] = \<const0> ;
  assign qdpo[2] = \<const0> ;
  assign qdpo[1] = \<const0> ;
  assign qdpo[0] = \<const0> ;
  assign qspo[31] = \<const0> ;
  assign qspo[30] = \<const0> ;
  assign qspo[29] = \<const0> ;
  assign qspo[28] = \<const0> ;
  assign qspo[27] = \<const0> ;
  assign qspo[26] = \<const0> ;
  assign qspo[25] = \<const0> ;
  assign qspo[24] = \<const0> ;
  assign qspo[23] = \<const0> ;
  assign qspo[22] = \<const0> ;
  assign qspo[21] = \<const0> ;
  assign qspo[20] = \<const0> ;
  assign qspo[19] = \<const0> ;
  assign qspo[18] = \<const0> ;
  assign qspo[17] = \<const0> ;
  assign qspo[16] = \<const0> ;
  assign qspo[15] = \<const0> ;
  assign qspo[14] = \<const0> ;
  assign qspo[13] = \<const0> ;
  assign qspo[12] = \<const0> ;
  assign qspo[11] = \<const0> ;
  assign qspo[10] = \<const0> ;
  assign qspo[9] = \<const0> ;
  assign qspo[8] = \<const0> ;
  assign qspo[7] = \<const0> ;
  assign qspo[6] = \<const0> ;
  assign qspo[5] = \<const0> ;
  assign qspo[4] = \<const0> ;
  assign qspo[3] = \<const0> ;
  assign qspo[2] = \<const0> ;
  assign qspo[1] = \<const0> ;
  assign qspo[0] = \<const0> ;
  assign spo[31:26] = \^spo [31:26];
  assign spo[25] = \<const0> ;
  assign spo[24:10] = \^spo [24:10];
  assign spo[9] = \^spo [10];
  assign spo[8] = \^spo [10];
  assign spo[7:0] = \^spo [7:0];
  GND GND
       (.G(\<const0> ));
  imem_dist_mem_gen_v8_0_10_synth \synth_options.dist_mem_inst 
       (.a(a),
        .spo({\^spo [31:26],\^spo [24:10],\^spo [7:0]}));
endmodule

(* ORIG_REF_NAME = "dist_mem_gen_v8_0_10_synth" *) 
module imem_dist_mem_gen_v8_0_10_synth
   (spo,
    a);
  output [28:0]spo;
  input [10:0]a;

  wire [10:0]a;
  wire [28:0]spo;

  imem_rom \gen_rom.rom_inst 
       (.a(a),
        .spo(spo));
endmodule

(* ORIG_REF_NAME = "rom" *) 
module imem_rom
   (spo,
    a);
  output [28:0]spo;
  input [10:0]a;

  wire [10:0]a;
  wire [28:0]spo;
  wire \spo[0]_INST_0_i_1_n_0 ;
  wire \spo[0]_INST_0_i_2_n_0 ;
  wire \spo[0]_INST_0_i_3_n_0 ;
  wire \spo[11]_INST_0_i_1_n_0 ;
  wire \spo[11]_INST_0_i_2_n_0 ;
  wire \spo[11]_INST_0_i_3_n_0 ;
  wire \spo[12]_INST_0_i_1_n_0 ;
  wire \spo[12]_INST_0_i_2_n_0 ;
  wire \spo[12]_INST_0_i_3_n_0 ;
  wire \spo[13]_INST_0_i_1_n_0 ;
  wire \spo[13]_INST_0_i_2_n_0 ;
  wire \spo[14]_INST_0_i_1_n_0 ;
  wire \spo[14]_INST_0_i_2_n_0 ;
  wire \spo[15]_INST_0_i_1_n_0 ;
  wire \spo[16]_INST_0_i_1_n_0 ;
  wire \spo[16]_INST_0_i_2_n_0 ;
  wire \spo[16]_INST_0_i_3_n_0 ;
  wire \spo[17]_INST_0_i_1_n_0 ;
  wire \spo[17]_INST_0_i_2_n_0 ;
  wire \spo[17]_INST_0_i_3_n_0 ;
  wire \spo[18]_INST_0_i_1_n_0 ;
  wire \spo[18]_INST_0_i_2_n_0 ;
  wire \spo[18]_INST_0_i_3_n_0 ;
  wire \spo[19]_INST_0_i_1_n_0 ;
  wire \spo[19]_INST_0_i_2_n_0 ;
  wire \spo[19]_INST_0_i_3_n_0 ;
  wire \spo[1]_INST_0_i_1_n_0 ;
  wire \spo[1]_INST_0_i_2_n_0 ;
  wire \spo[20]_INST_0_i_1_n_0 ;
  wire \spo[20]_INST_0_i_2_n_0 ;
  wire \spo[20]_INST_0_i_3_n_0 ;
  wire \spo[21]_INST_0_i_1_n_0 ;
  wire \spo[21]_INST_0_i_2_n_0 ;
  wire \spo[21]_INST_0_i_3_n_0 ;
  wire \spo[22]_INST_0_i_1_n_0 ;
  wire \spo[22]_INST_0_i_2_n_0 ;
  wire \spo[23]_INST_0_i_1_n_0 ;
  wire \spo[23]_INST_0_i_2_n_0 ;
  wire \spo[23]_INST_0_i_3_n_0 ;
  wire \spo[24]_INST_0_i_1_n_0 ;
  wire \spo[24]_INST_0_i_2_n_0 ;
  wire \spo[26]_INST_0_i_1_n_0 ;
  wire \spo[26]_INST_0_i_2_n_0 ;
  wire \spo[27]_INST_0_i_1_n_0 ;
  wire \spo[27]_INST_0_i_2_n_0 ;
  wire \spo[27]_INST_0_i_3_n_0 ;
  wire \spo[28]_INST_0_i_1_n_0 ;
  wire \spo[28]_INST_0_i_2_n_0 ;
  wire \spo[28]_INST_0_i_3_n_0 ;
  wire \spo[29]_INST_0_i_1_n_0 ;
  wire \spo[29]_INST_0_i_2_n_0 ;
  wire \spo[29]_INST_0_i_3_n_0 ;
  wire \spo[2]_INST_0_i_1_n_0 ;
  wire \spo[2]_INST_0_i_2_n_0 ;
  wire \spo[30]_INST_0_i_1_n_0 ;
  wire \spo[30]_INST_0_i_2_n_0 ;
  wire \spo[31]_INST_0_i_1_n_0 ;
  wire \spo[31]_INST_0_i_2_n_0 ;
  wire \spo[31]_INST_0_i_3_n_0 ;
  wire \spo[31]_INST_0_i_4_n_0 ;
  wire \spo[31]_INST_0_i_5_n_0 ;
  wire \spo[3]_INST_0_i_1_n_0 ;
  wire \spo[4]_INST_0_i_1_n_0 ;
  wire \spo[5]_INST_0_i_1_n_0 ;
  wire \spo[5]_INST_0_i_2_n_0 ;
  wire \spo[5]_INST_0_i_3_n_0 ;
  wire \spo[6]_INST_0_i_1_n_0 ;
  wire \spo[6]_INST_0_i_2_n_0 ;
  wire \spo[7]_INST_0_i_1_n_0 ;
  wire \spo[7]_INST_0_i_2_n_0 ;

  LUT5 #(
    .INIT(32'hB8BBB888)) 
    \spo[0]_INST_0 
       (.I0(\spo[0]_INST_0_i_1_n_0 ),
        .I1(a[5]),
        .I2(\spo[0]_INST_0_i_2_n_0 ),
        .I3(a[3]),
        .I4(\spo[0]_INST_0_i_3_n_0 ),
        .O(spo[0]));
  LUT6 #(
    .INIT(64'h49D4000025190000)) 
    \spo[0]_INST_0_i_1 
       (.I0(a[3]),
        .I1(a[0]),
        .I2(a[4]),
        .I3(a[2]),
        .I4(\spo[31]_INST_0_i_4_n_0 ),
        .I5(a[1]),
        .O(\spo[0]_INST_0_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT5 #(
    .INIT(32'h0300E000)) 
    \spo[0]_INST_0_i_2 
       (.I0(a[0]),
        .I1(a[4]),
        .I2(a[1]),
        .I3(\spo[31]_INST_0_i_4_n_0 ),
        .I4(a[2]),
        .O(\spo[0]_INST_0_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h027A0000051A0000)) 
    \spo[0]_INST_0_i_3 
       (.I0(a[0]),
        .I1(a[2]),
        .I2(a[4]),
        .I3(a[6]),
        .I4(\spo[31]_INST_0_i_5_n_0 ),
        .I5(a[1]),
        .O(\spo[0]_INST_0_i_3_n_0 ));
  LUT5 #(
    .INIT(32'hB8BBB888)) 
    \spo[11]_INST_0 
       (.I0(\spo[11]_INST_0_i_1_n_0 ),
        .I1(a[5]),
        .I2(\spo[11]_INST_0_i_2_n_0 ),
        .I3(a[3]),
        .I4(\spo[11]_INST_0_i_3_n_0 ),
        .O(spo[9]));
  LUT6 #(
    .INIT(64'h6600400010000900)) 
    \spo[11]_INST_0_i_1 
       (.I0(a[3]),
        .I1(a[0]),
        .I2(a[1]),
        .I3(\spo[31]_INST_0_i_4_n_0 ),
        .I4(a[2]),
        .I5(a[4]),
        .O(\spo[11]_INST_0_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT5 #(
    .INIT(32'h60800080)) 
    \spo[11]_INST_0_i_2 
       (.I0(a[0]),
        .I1(a[2]),
        .I2(\spo[31]_INST_0_i_4_n_0 ),
        .I3(a[1]),
        .I4(a[4]),
        .O(\spo[11]_INST_0_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h0860000005100000)) 
    \spo[11]_INST_0_i_3 
       (.I0(a[0]),
        .I1(a[2]),
        .I2(a[4]),
        .I3(a[6]),
        .I4(\spo[31]_INST_0_i_5_n_0 ),
        .I5(a[1]),
        .O(\spo[11]_INST_0_i_3_n_0 ));
  LUT5 #(
    .INIT(32'hB8BBB888)) 
    \spo[12]_INST_0 
       (.I0(\spo[12]_INST_0_i_1_n_0 ),
        .I1(a[5]),
        .I2(\spo[12]_INST_0_i_2_n_0 ),
        .I3(a[3]),
        .I4(\spo[12]_INST_0_i_3_n_0 ),
        .O(spo[10]));
  LUT6 #(
    .INIT(64'hA500000000420000)) 
    \spo[12]_INST_0_i_1 
       (.I0(a[3]),
        .I1(a[2]),
        .I2(a[0]),
        .I3(a[1]),
        .I4(\spo[31]_INST_0_i_4_n_0 ),
        .I5(a[4]),
        .O(\spo[12]_INST_0_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT5 #(
    .INIT(32'hE9004C00)) 
    \spo[12]_INST_0_i_2 
       (.I0(a[0]),
        .I1(a[4]),
        .I2(a[1]),
        .I3(\spo[31]_INST_0_i_4_n_0 ),
        .I4(a[2]),
        .O(\spo[12]_INST_0_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h2000080030004000)) 
    \spo[12]_INST_0_i_3 
       (.I0(a[0]),
        .I1(a[4]),
        .I2(a[1]),
        .I3(\spo[31]_INST_0_i_5_n_0 ),
        .I4(a[6]),
        .I5(a[2]),
        .O(\spo[12]_INST_0_i_3_n_0 ));
  LUT4 #(
    .INIT(16'h00E2)) 
    \spo[13]_INST_0 
       (.I0(\spo[13]_INST_0_i_1_n_0 ),
        .I1(a[3]),
        .I2(\spo[13]_INST_0_i_2_n_0 ),
        .I3(a[5]),
        .O(spo[11]));
  LUT6 #(
    .INIT(64'h0000000090000000)) 
    \spo[13]_INST_0_i_1 
       (.I0(a[0]),
        .I1(a[2]),
        .I2(a[6]),
        .I3(\spo[31]_INST_0_i_5_n_0 ),
        .I4(a[1]),
        .I5(a[4]),
        .O(\spo[13]_INST_0_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT5 #(
    .INIT(32'h60300000)) 
    \spo[13]_INST_0_i_2 
       (.I0(a[0]),
        .I1(a[1]),
        .I2(\spo[31]_INST_0_i_4_n_0 ),
        .I3(a[2]),
        .I4(a[4]),
        .O(\spo[13]_INST_0_i_2_n_0 ));
  MUXF7 \spo[14]_INST_0 
       (.I0(\spo[14]_INST_0_i_1_n_0 ),
        .I1(\spo[14]_INST_0_i_2_n_0 ),
        .O(spo[12]),
        .S(a[5]));
  LUT6 #(
    .INIT(64'h8008800830030000)) 
    \spo[14]_INST_0_i_1 
       (.I0(\spo[3]_INST_0_i_1_n_0 ),
        .I1(a[3]),
        .I2(a[0]),
        .I3(a[2]),
        .I4(\spo[15]_INST_0_i_1_n_0 ),
        .I5(a[4]),
        .O(\spo[14]_INST_0_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h00408000)) 
    \spo[14]_INST_0_i_2 
       (.I0(a[3]),
        .I1(a[4]),
        .I2(\spo[31]_INST_0_i_4_n_0 ),
        .I3(a[1]),
        .I4(a[0]),
        .O(\spo[14]_INST_0_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000004100)) 
    \spo[15]_INST_0 
       (.I0(a[3]),
        .I1(a[0]),
        .I2(a[2]),
        .I3(\spo[15]_INST_0_i_1_n_0 ),
        .I4(a[4]),
        .I5(a[5]),
        .O(spo[13]));
  LUT6 #(
    .INIT(64'h0000000200000000)) 
    \spo[15]_INST_0_i_1 
       (.I0(a[6]),
        .I1(a[7]),
        .I2(a[8]),
        .I3(a[9]),
        .I4(a[10]),
        .I5(a[1]),
        .O(\spo[15]_INST_0_i_1_n_0 ));
  LUT5 #(
    .INIT(32'hB8BBB888)) 
    \spo[16]_INST_0 
       (.I0(\spo[16]_INST_0_i_1_n_0 ),
        .I1(a[5]),
        .I2(\spo[16]_INST_0_i_2_n_0 ),
        .I3(a[3]),
        .I4(\spo[16]_INST_0_i_3_n_0 ),
        .O(spo[14]));
  LUT6 #(
    .INIT(64'hB0B0007080606060)) 
    \spo[16]_INST_0_i_1 
       (.I0(a[3]),
        .I1(a[0]),
        .I2(\spo[31]_INST_0_i_4_n_0 ),
        .I3(a[2]),
        .I4(a[1]),
        .I5(a[4]),
        .O(\spo[16]_INST_0_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT5 #(
    .INIT(32'hE1006200)) 
    \spo[16]_INST_0_i_2 
       (.I0(a[0]),
        .I1(a[4]),
        .I2(a[1]),
        .I3(\spo[31]_INST_0_i_4_n_0 ),
        .I4(a[2]),
        .O(\spo[16]_INST_0_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h2000AA0032006A00)) 
    \spo[16]_INST_0_i_3 
       (.I0(a[0]),
        .I1(a[4]),
        .I2(a[1]),
        .I3(\spo[31]_INST_0_i_5_n_0 ),
        .I4(a[6]),
        .I5(a[2]),
        .O(\spo[16]_INST_0_i_3_n_0 ));
  LUT5 #(
    .INIT(32'hB8BBB888)) 
    \spo[17]_INST_0 
       (.I0(\spo[17]_INST_0_i_1_n_0 ),
        .I1(a[5]),
        .I2(\spo[17]_INST_0_i_2_n_0 ),
        .I3(a[3]),
        .I4(\spo[17]_INST_0_i_3_n_0 ),
        .O(spo[15]));
  LUT6 #(
    .INIT(64'h2400240061003400)) 
    \spo[17]_INST_0_i_1 
       (.I0(a[3]),
        .I1(a[0]),
        .I2(a[1]),
        .I3(\spo[31]_INST_0_i_4_n_0 ),
        .I4(a[2]),
        .I5(a[4]),
        .O(\spo[17]_INST_0_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT5 #(
    .INIT(32'h5000CB00)) 
    \spo[17]_INST_0_i_2 
       (.I0(a[0]),
        .I1(a[4]),
        .I2(a[2]),
        .I3(\spo[31]_INST_0_i_4_n_0 ),
        .I4(a[1]),
        .O(\spo[17]_INST_0_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h0000040088000F00)) 
    \spo[17]_INST_0_i_3 
       (.I0(a[2]),
        .I1(a[0]),
        .I2(a[1]),
        .I3(\spo[31]_INST_0_i_5_n_0 ),
        .I4(a[6]),
        .I5(a[4]),
        .O(\spo[17]_INST_0_i_3_n_0 ));
  LUT5 #(
    .INIT(32'hB8BBB888)) 
    \spo[18]_INST_0 
       (.I0(\spo[18]_INST_0_i_1_n_0 ),
        .I1(a[5]),
        .I2(\spo[18]_INST_0_i_2_n_0 ),
        .I3(a[3]),
        .I4(\spo[18]_INST_0_i_3_n_0 ),
        .O(spo[16]));
  LUT6 #(
    .INIT(64'h6600640050002D00)) 
    \spo[18]_INST_0_i_1 
       (.I0(a[3]),
        .I1(a[0]),
        .I2(a[1]),
        .I3(\spo[31]_INST_0_i_4_n_0 ),
        .I4(a[2]),
        .I5(a[4]),
        .O(\spo[18]_INST_0_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h4C00BC00)) 
    \spo[18]_INST_0_i_2 
       (.I0(a[0]),
        .I1(a[4]),
        .I2(a[1]),
        .I3(\spo[31]_INST_0_i_4_n_0 ),
        .I4(a[2]),
        .O(\spo[18]_INST_0_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h1031000083700000)) 
    \spo[18]_INST_0_i_3 
       (.I0(a[0]),
        .I1(a[4]),
        .I2(a[2]),
        .I3(a[1]),
        .I4(\spo[31]_INST_0_i_5_n_0 ),
        .I5(a[6]),
        .O(\spo[18]_INST_0_i_3_n_0 ));
  LUT5 #(
    .INIT(32'hB8BBB888)) 
    \spo[19]_INST_0 
       (.I0(\spo[19]_INST_0_i_1_n_0 ),
        .I1(a[5]),
        .I2(\spo[19]_INST_0_i_2_n_0 ),
        .I3(a[3]),
        .I4(\spo[19]_INST_0_i_3_n_0 ),
        .O(spo[17]));
  LUT6 #(
    .INIT(64'h4B42339900000000)) 
    \spo[19]_INST_0_i_1 
       (.I0(a[3]),
        .I1(a[0]),
        .I2(a[1]),
        .I3(a[2]),
        .I4(a[4]),
        .I5(\spo[31]_INST_0_i_4_n_0 ),
        .O(\spo[19]_INST_0_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h6000BF00)) 
    \spo[19]_INST_0_i_2 
       (.I0(a[0]),
        .I1(a[1]),
        .I2(a[4]),
        .I3(\spo[31]_INST_0_i_4_n_0 ),
        .I4(a[2]),
        .O(\spo[19]_INST_0_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h00000000F040C0C0)) 
    \spo[19]_INST_0_i_3 
       (.I0(a[0]),
        .I1(a[6]),
        .I2(\spo[31]_INST_0_i_5_n_0 ),
        .I3(a[2]),
        .I4(a[1]),
        .I5(a[4]),
        .O(\spo[19]_INST_0_i_3_n_0 ));
  MUXF7 \spo[1]_INST_0 
       (.I0(\spo[1]_INST_0_i_1_n_0 ),
        .I1(\spo[1]_INST_0_i_2_n_0 ),
        .O(spo[1]),
        .S(a[5]));
  LUT6 #(
    .INIT(64'hA800200000004800)) 
    \spo[1]_INST_0_i_1 
       (.I0(a[3]),
        .I1(a[4]),
        .I2(a[1]),
        .I3(\spo[31]_INST_0_i_4_n_0 ),
        .I4(a[2]),
        .I5(a[0]),
        .O(\spo[1]_INST_0_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h2B0048000000C000)) 
    \spo[1]_INST_0_i_2 
       (.I0(a[3]),
        .I1(a[0]),
        .I2(a[2]),
        .I3(\spo[31]_INST_0_i_4_n_0 ),
        .I4(a[1]),
        .I5(a[4]),
        .O(\spo[1]_INST_0_i_2_n_0 ));
  MUXF7 \spo[20]_INST_0 
       (.I0(\spo[20]_INST_0_i_1_n_0 ),
        .I1(\spo[20]_INST_0_i_2_n_0 ),
        .O(spo[18]),
        .S(a[5]));
  LUT6 #(
    .INIT(64'h0000000000000080)) 
    \spo[20]_INST_0_i_1 
       (.I0(a[0]),
        .I1(a[2]),
        .I2(\spo[20]_INST_0_i_3_n_0 ),
        .I3(a[1]),
        .I4(a[4]),
        .I5(a[3]),
        .O(\spo[20]_INST_0_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0200080000000000)) 
    \spo[20]_INST_0_i_2 
       (.I0(a[0]),
        .I1(a[4]),
        .I2(a[1]),
        .I3(\spo[31]_INST_0_i_4_n_0 ),
        .I4(a[2]),
        .I5(a[3]),
        .O(\spo[20]_INST_0_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT5 #(
    .INIT(32'h00010000)) 
    \spo[20]_INST_0_i_3 
       (.I0(a[10]),
        .I1(a[9]),
        .I2(a[8]),
        .I3(a[7]),
        .I4(a[6]),
        .O(\spo[20]_INST_0_i_3_n_0 ));
  LUT5 #(
    .INIT(32'hB8BBB888)) 
    \spo[21]_INST_0 
       (.I0(\spo[21]_INST_0_i_1_n_0 ),
        .I1(a[5]),
        .I2(\spo[21]_INST_0_i_2_n_0 ),
        .I3(a[3]),
        .I4(\spo[21]_INST_0_i_3_n_0 ),
        .O(spo[19]));
  LUT6 #(
    .INIT(64'h45420000B32D0000)) 
    \spo[21]_INST_0_i_1 
       (.I0(a[3]),
        .I1(a[0]),
        .I2(a[4]),
        .I3(a[2]),
        .I4(\spo[31]_INST_0_i_4_n_0 ),
        .I5(a[1]),
        .O(\spo[21]_INST_0_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT5 #(
    .INIT(32'h5E008000)) 
    \spo[21]_INST_0_i_2 
       (.I0(a[0]),
        .I1(a[4]),
        .I2(a[1]),
        .I3(\spo[31]_INST_0_i_4_n_0 ),
        .I4(a[2]),
        .O(\spo[21]_INST_0_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h00E000000F700000)) 
    \spo[21]_INST_0_i_3 
       (.I0(a[0]),
        .I1(a[2]),
        .I2(a[4]),
        .I3(a[6]),
        .I4(\spo[31]_INST_0_i_5_n_0 ),
        .I5(a[1]),
        .O(\spo[21]_INST_0_i_3_n_0 ));
  MUXF7 \spo[22]_INST_0 
       (.I0(\spo[22]_INST_0_i_1_n_0 ),
        .I1(\spo[22]_INST_0_i_2_n_0 ),
        .O(spo[20]),
        .S(a[5]));
  LUT6 #(
    .INIT(64'h0020800000000000)) 
    \spo[22]_INST_0_i_1 
       (.I0(a[4]),
        .I1(a[1]),
        .I2(\spo[31]_INST_0_i_4_n_0 ),
        .I3(a[2]),
        .I4(a[0]),
        .I5(a[3]),
        .O(\spo[22]_INST_0_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0400030008004000)) 
    \spo[22]_INST_0_i_2 
       (.I0(a[0]),
        .I1(a[3]),
        .I2(a[2]),
        .I3(\spo[31]_INST_0_i_4_n_0 ),
        .I4(a[1]),
        .I5(a[4]),
        .O(\spo[22]_INST_0_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hB8BBB888)) 
    \spo[23]_INST_0 
       (.I0(\spo[23]_INST_0_i_1_n_0 ),
        .I1(a[5]),
        .I2(\spo[23]_INST_0_i_2_n_0 ),
        .I3(a[3]),
        .I4(\spo[23]_INST_0_i_3_n_0 ),
        .O(spo[21]));
  LUT6 #(
    .INIT(64'h0200040029002000)) 
    \spo[23]_INST_0_i_1 
       (.I0(a[3]),
        .I1(a[0]),
        .I2(a[2]),
        .I3(\spo[31]_INST_0_i_4_n_0 ),
        .I4(a[1]),
        .I5(a[4]),
        .O(\spo[23]_INST_0_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT5 #(
    .INIT(32'h40A00000)) 
    \spo[23]_INST_0_i_2 
       (.I0(a[0]),
        .I1(a[2]),
        .I2(\spo[31]_INST_0_i_4_n_0 ),
        .I3(a[1]),
        .I4(a[4]),
        .O(\spo[23]_INST_0_i_2_n_0 ));
  LUT5 #(
    .INIT(32'h00008000)) 
    \spo[23]_INST_0_i_3 
       (.I0(a[2]),
        .I1(a[6]),
        .I2(\spo[31]_INST_0_i_5_n_0 ),
        .I3(a[1]),
        .I4(a[4]),
        .O(\spo[23]_INST_0_i_3_n_0 ));
  MUXF7 \spo[24]_INST_0 
       (.I0(\spo[24]_INST_0_i_1_n_0 ),
        .I1(\spo[24]_INST_0_i_2_n_0 ),
        .O(spo[22]),
        .S(a[5]));
  LUT6 #(
    .INIT(64'h8000800030330000)) 
    \spo[24]_INST_0_i_1 
       (.I0(\spo[3]_INST_0_i_1_n_0 ),
        .I1(a[3]),
        .I2(a[2]),
        .I3(a[0]),
        .I4(\spo[15]_INST_0_i_1_n_0 ),
        .I5(a[4]),
        .O(\spo[24]_INST_0_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h2240000001100000)) 
    \spo[24]_INST_0_i_2 
       (.I0(a[3]),
        .I1(a[0]),
        .I2(a[4]),
        .I3(a[1]),
        .I4(\spo[31]_INST_0_i_4_n_0 ),
        .I5(a[2]),
        .O(\spo[24]_INST_0_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hB8BBB888)) 
    \spo[26]_INST_0 
       (.I0(\spo[26]_INST_0_i_1_n_0 ),
        .I1(a[5]),
        .I2(\spo[27]_INST_0_i_2_n_0 ),
        .I3(a[3]),
        .I4(\spo[26]_INST_0_i_2_n_0 ),
        .O(spo[23]));
  LUT6 #(
    .INIT(64'h9495000092360000)) 
    \spo[26]_INST_0_i_1 
       (.I0(a[3]),
        .I1(a[0]),
        .I2(a[4]),
        .I3(a[1]),
        .I4(\spo[31]_INST_0_i_4_n_0 ),
        .I5(a[2]),
        .O(\spo[26]_INST_0_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h00B00060A000A000)) 
    \spo[26]_INST_0_i_2 
       (.I0(a[0]),
        .I1(a[1]),
        .I2(\spo[31]_INST_0_i_5_n_0 ),
        .I3(a[6]),
        .I4(a[2]),
        .I5(a[4]),
        .O(\spo[26]_INST_0_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hB8BBB888)) 
    \spo[27]_INST_0 
       (.I0(\spo[27]_INST_0_i_1_n_0 ),
        .I1(a[5]),
        .I2(\spo[27]_INST_0_i_2_n_0 ),
        .I3(a[3]),
        .I4(\spo[27]_INST_0_i_3_n_0 ),
        .O(spo[24]));
  LUT6 #(
    .INIT(64'h969C000093A60000)) 
    \spo[27]_INST_0_i_1 
       (.I0(a[3]),
        .I1(a[0]),
        .I2(a[4]),
        .I3(a[1]),
        .I4(\spo[31]_INST_0_i_4_n_0 ),
        .I5(a[2]),
        .O(\spo[27]_INST_0_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT5 #(
    .INIT(32'h9D004000)) 
    \spo[27]_INST_0_i_2 
       (.I0(a[0]),
        .I1(a[1]),
        .I2(a[4]),
        .I3(\spo[31]_INST_0_i_4_n_0 ),
        .I4(a[2]),
        .O(\spo[27]_INST_0_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h00B000602000A000)) 
    \spo[27]_INST_0_i_3 
       (.I0(a[0]),
        .I1(a[1]),
        .I2(\spo[31]_INST_0_i_5_n_0 ),
        .I3(a[6]),
        .I4(a[2]),
        .I5(a[4]),
        .O(\spo[27]_INST_0_i_3_n_0 ));
  LUT5 #(
    .INIT(32'hB8BBB888)) 
    \spo[28]_INST_0 
       (.I0(\spo[28]_INST_0_i_1_n_0 ),
        .I1(a[5]),
        .I2(\spo[28]_INST_0_i_2_n_0 ),
        .I3(a[3]),
        .I4(\spo[28]_INST_0_i_3_n_0 ),
        .O(spo[25]));
  LUT6 #(
    .INIT(64'hB0450000B0120000)) 
    \spo[28]_INST_0_i_1 
       (.I0(a[3]),
        .I1(a[0]),
        .I2(a[4]),
        .I3(a[1]),
        .I4(\spo[31]_INST_0_i_4_n_0 ),
        .I5(a[2]),
        .O(\spo[28]_INST_0_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT5 #(
    .INIT(32'hA9004000)) 
    \spo[28]_INST_0_i_2 
       (.I0(a[0]),
        .I1(a[4]),
        .I2(a[1]),
        .I3(\spo[31]_INST_0_i_4_n_0 ),
        .I4(a[2]),
        .O(\spo[28]_INST_0_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h01000800A0000000)) 
    \spo[28]_INST_0_i_3 
       (.I0(a[0]),
        .I1(a[2]),
        .I2(a[6]),
        .I3(\spo[31]_INST_0_i_5_n_0 ),
        .I4(a[1]),
        .I5(a[4]),
        .O(\spo[28]_INST_0_i_3_n_0 ));
  LUT5 #(
    .INIT(32'hB8BBB888)) 
    \spo[29]_INST_0 
       (.I0(\spo[29]_INST_0_i_1_n_0 ),
        .I1(a[5]),
        .I2(\spo[29]_INST_0_i_2_n_0 ),
        .I3(a[3]),
        .I4(\spo[29]_INST_0_i_3_n_0 ),
        .O(spo[26]));
  LUT6 #(
    .INIT(64'hBED60000BF260000)) 
    \spo[29]_INST_0_i_1 
       (.I0(a[3]),
        .I1(a[0]),
        .I2(a[4]),
        .I3(a[1]),
        .I4(\spo[31]_INST_0_i_4_n_0 ),
        .I5(a[2]),
        .O(\spo[29]_INST_0_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT5 #(
    .INIT(32'h9CF70000)) 
    \spo[29]_INST_0_i_2 
       (.I0(a[0]),
        .I1(a[2]),
        .I2(a[1]),
        .I3(a[4]),
        .I4(\spo[31]_INST_0_i_4_n_0 ),
        .O(\spo[29]_INST_0_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h12220000BF7B0000)) 
    \spo[29]_INST_0_i_3 
       (.I0(a[0]),
        .I1(a[4]),
        .I2(a[1]),
        .I3(a[2]),
        .I4(\spo[31]_INST_0_i_5_n_0 ),
        .I5(a[6]),
        .O(\spo[29]_INST_0_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h88B8BBBB88B88888)) 
    \spo[2]_INST_0 
       (.I0(\spo[2]_INST_0_i_1_n_0 ),
        .I1(a[5]),
        .I2(\spo[4]_INST_0_i_1_n_0 ),
        .I3(a[0]),
        .I4(a[3]),
        .I5(\spo[2]_INST_0_i_2_n_0 ),
        .O(spo[2]));
  LUT6 #(
    .INIT(64'h8000000040000200)) 
    \spo[2]_INST_0_i_1 
       (.I0(a[3]),
        .I1(a[4]),
        .I2(a[1]),
        .I3(\spo[31]_INST_0_i_4_n_0 ),
        .I4(a[2]),
        .I5(a[0]),
        .O(\spo[2]_INST_0_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000080060000000)) 
    \spo[2]_INST_0_i_2 
       (.I0(a[0]),
        .I1(a[2]),
        .I2(a[6]),
        .I3(\spo[31]_INST_0_i_5_n_0 ),
        .I4(a[1]),
        .I5(a[4]),
        .O(\spo[2]_INST_0_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h38080000C0000000)) 
    \spo[30]_INST_0 
       (.I0(\spo[30]_INST_0_i_1_n_0 ),
        .I1(a[5]),
        .I2(a[0]),
        .I3(\spo[30]_INST_0_i_2_n_0 ),
        .I4(a[4]),
        .I5(a[3]),
        .O(spo[27]));
  LUT6 #(
    .INIT(64'h0000000100000000)) 
    \spo[30]_INST_0_i_1 
       (.I0(a[6]),
        .I1(a[7]),
        .I2(a[8]),
        .I3(a[9]),
        .I4(a[10]),
        .I5(a[1]),
        .O(\spo[30]_INST_0_i_1_n_0 ));
  LUT3 #(
    .INIT(8'h40)) 
    \spo[30]_INST_0_i_2 
       (.I0(a[1]),
        .I1(\spo[31]_INST_0_i_4_n_0 ),
        .I2(a[2]),
        .O(\spo[30]_INST_0_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h88B8BBBB88B88888)) 
    \spo[31]_INST_0 
       (.I0(\spo[31]_INST_0_i_1_n_0 ),
        .I1(a[5]),
        .I2(\spo[31]_INST_0_i_2_n_0 ),
        .I3(a[0]),
        .I4(a[3]),
        .I5(\spo[31]_INST_0_i_3_n_0 ),
        .O(spo[28]));
  LUT6 #(
    .INIT(64'h0000920042000400)) 
    \spo[31]_INST_0_i_1 
       (.I0(a[3]),
        .I1(a[0]),
        .I2(a[2]),
        .I3(\spo[31]_INST_0_i_4_n_0 ),
        .I4(a[1]),
        .I5(a[4]),
        .O(\spo[31]_INST_0_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT4 #(
    .INIT(16'h6000)) 
    \spo[31]_INST_0_i_2 
       (.I0(a[4]),
        .I1(a[1]),
        .I2(\spo[31]_INST_0_i_4_n_0 ),
        .I3(a[2]),
        .O(\spo[31]_INST_0_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h080006000000A000)) 
    \spo[31]_INST_0_i_3 
       (.I0(a[0]),
        .I1(a[2]),
        .I2(a[6]),
        .I3(\spo[31]_INST_0_i_5_n_0 ),
        .I4(a[1]),
        .I5(a[4]),
        .O(\spo[31]_INST_0_i_3_n_0 ));
  LUT5 #(
    .INIT(32'h00000001)) 
    \spo[31]_INST_0_i_4 
       (.I0(a[10]),
        .I1(a[9]),
        .I2(a[8]),
        .I3(a[7]),
        .I4(a[6]),
        .O(\spo[31]_INST_0_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT4 #(
    .INIT(16'h0001)) 
    \spo[31]_INST_0_i_5 
       (.I0(a[7]),
        .I1(a[8]),
        .I2(a[9]),
        .I3(a[10]),
        .O(\spo[31]_INST_0_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h0000104000000000)) 
    \spo[3]_INST_0 
       (.I0(a[3]),
        .I1(a[2]),
        .I2(\spo[3]_INST_0_i_1_n_0 ),
        .I3(a[4]),
        .I4(a[0]),
        .I5(a[5]),
        .O(spo[3]));
  LUT6 #(
    .INIT(64'h0000000000000001)) 
    \spo[3]_INST_0_i_1 
       (.I0(a[6]),
        .I1(a[7]),
        .I2(a[8]),
        .I3(a[9]),
        .I4(a[10]),
        .I5(a[1]),
        .O(\spo[3]_INST_0_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h3033300000880088)) 
    \spo[4]_INST_0 
       (.I0(\spo[4]_INST_0_i_1_n_0 ),
        .I1(a[5]),
        .I2(\spo[6]_INST_0_i_2_n_0 ),
        .I3(a[3]),
        .I4(\spo[23]_INST_0_i_3_n_0 ),
        .I5(a[0]),
        .O(spo[4]));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT4 #(
    .INIT(16'h0040)) 
    \spo[4]_INST_0_i_1 
       (.I0(a[2]),
        .I1(\spo[31]_INST_0_i_4_n_0 ),
        .I2(a[1]),
        .I3(a[4]),
        .O(\spo[4]_INST_0_i_1_n_0 ));
  LUT5 #(
    .INIT(32'hB8BBB888)) 
    \spo[5]_INST_0 
       (.I0(\spo[5]_INST_0_i_1_n_0 ),
        .I1(a[5]),
        .I2(\spo[5]_INST_0_i_2_n_0 ),
        .I3(a[3]),
        .I4(\spo[5]_INST_0_i_3_n_0 ),
        .O(spo[5]));
  LUT6 #(
    .INIT(64'h4200440030000900)) 
    \spo[5]_INST_0_i_1 
       (.I0(a[3]),
        .I1(a[0]),
        .I2(a[1]),
        .I3(\spo[31]_INST_0_i_4_n_0 ),
        .I4(a[2]),
        .I5(a[4]),
        .O(\spo[5]_INST_0_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT5 #(
    .INIT(32'h602000A0)) 
    \spo[5]_INST_0_i_2 
       (.I0(a[0]),
        .I1(a[2]),
        .I2(\spo[31]_INST_0_i_4_n_0 ),
        .I3(a[1]),
        .I4(a[4]),
        .O(\spo[5]_INST_0_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h0111000040840000)) 
    \spo[5]_INST_0_i_3 
       (.I0(a[0]),
        .I1(a[4]),
        .I2(a[1]),
        .I3(a[2]),
        .I4(\spo[31]_INST_0_i_5_n_0 ),
        .I5(a[6]),
        .O(\spo[5]_INST_0_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hB8BBB88888888888)) 
    \spo[6]_INST_0 
       (.I0(\spo[6]_INST_0_i_1_n_0 ),
        .I1(a[5]),
        .I2(\spo[6]_INST_0_i_2_n_0 ),
        .I3(a[3]),
        .I4(\spo[23]_INST_0_i_3_n_0 ),
        .I5(a[0]),
        .O(spo[6]));
  LUT6 #(
    .INIT(64'h0200080000001000)) 
    \spo[6]_INST_0_i_1 
       (.I0(a[3]),
        .I1(a[4]),
        .I2(a[1]),
        .I3(\spo[31]_INST_0_i_4_n_0 ),
        .I4(a[2]),
        .I5(a[0]),
        .O(\spo[6]_INST_0_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT4 #(
    .INIT(16'h0004)) 
    \spo[6]_INST_0_i_2 
       (.I0(a[2]),
        .I1(\spo[31]_INST_0_i_4_n_0 ),
        .I2(a[1]),
        .I3(a[4]),
        .O(\spo[6]_INST_0_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h0400FFFF04000000)) 
    \spo[7]_INST_0 
       (.I0(a[0]),
        .I1(\spo[7]_INST_0_i_1_n_0 ),
        .I2(a[4]),
        .I3(a[3]),
        .I4(a[5]),
        .I5(\spo[7]_INST_0_i_2_n_0 ),
        .O(spo[7]));
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT3 #(
    .INIT(8'h80)) 
    \spo[7]_INST_0_i_1 
       (.I0(a[1]),
        .I1(\spo[31]_INST_0_i_4_n_0 ),
        .I2(a[2]),
        .O(\spo[7]_INST_0_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0300080800008080)) 
    \spo[7]_INST_0_i_2 
       (.I0(\spo[3]_INST_0_i_1_n_0 ),
        .I1(a[3]),
        .I2(a[4]),
        .I3(\spo[15]_INST_0_i_1_n_0 ),
        .I4(a[2]),
        .I5(a[0]),
        .O(\spo[7]_INST_0_i_2_n_0 ));
  LUT4 #(
    .INIT(16'h0040)) 
    \spo[8]_INST_0 
       (.I0(a[3]),
        .I1(\spo[23]_INST_0_i_3_n_0 ),
        .I2(a[0]),
        .I3(a[5]),
        .O(spo[8]));
endmodule
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    tri1 p_up_tmp;
    tri (weak1, strong0) PLL_LOCKG = p_up_tmp;

    wire PROGB_GLBL;
    wire CCLKO_GLBL;
    wire FCSBO_GLBL;
    wire [3:0] DO_GLBL;
    wire [3:0] DI_GLBL;
   
    reg GSR_int;
    reg GTS_int;
    reg PRLD_int;

//--------   JTAG Globals --------------
    wire JTAG_TDO_GLBL;
    wire JTAG_TCK_GLBL;
    wire JTAG_TDI_GLBL;
    wire JTAG_TMS_GLBL;
    wire JTAG_TRST_GLBL;

    reg JTAG_CAPTURE_GLBL;
    reg JTAG_RESET_GLBL;
    reg JTAG_SHIFT_GLBL;
    reg JTAG_UPDATE_GLBL;
    reg JTAG_RUNTEST_GLBL;

    reg JTAG_SEL1_GLBL = 0;
    reg JTAG_SEL2_GLBL = 0 ;
    reg JTAG_SEL3_GLBL = 0;
    reg JTAG_SEL4_GLBL = 0;

    reg JTAG_USER_TDO1_GLBL = 1'bz;
    reg JTAG_USER_TDO2_GLBL = 1'bz;
    reg JTAG_USER_TDO3_GLBL = 1'bz;
    reg JTAG_USER_TDO4_GLBL = 1'bz;

    assign (weak1, weak0) GSR = GSR_int;
    assign (weak1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;

    initial begin
	GSR_int = 1'b1;
	PRLD_int = 1'b1;
	#(ROC_WIDTH)
	GSR_int = 1'b0;
	PRLD_int = 1'b0;
    end

    initial begin
	GTS_int = 1'b1;
	#(TOC_WIDTH)
	GTS_int = 1'b0;
    end

endmodule
`endif
