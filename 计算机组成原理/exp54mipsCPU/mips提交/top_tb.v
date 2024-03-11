`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/09 19:03:35
// Design Name: 
// Module Name: top_tb
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


module top_tb();
    integer result;
    reg clk_in;
    reg reset;
    wire [31:0] inst;
    wire [31:0] pc;
    sccomp_dataflow sccomp_dataflow_inst(clk_in, reset, inst, pc);
    initial
    begin
        result = $fopen("result.txt", "w"); 
        clk_in = 0;
        reset = 0;
    end
    always
    begin
        #5 clk_in = ~clk_in;
        if (clk_in == 0)
        begin
            $fdisplay(result, "pc: %h", pc);
            $fdisplay(result, "instr: %h", inst);
            $fdisplay(result, "regfile0: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[0]);
            $fdisplay(result, "regfile1: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[1]);
            $fdisplay(result, "regfile2: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[2]);
            $fdisplay(result, "regfile3: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[3]);
            $fdisplay(result, "regfile4: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[4]);
            $fdisplay(result, "regfile5: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[5]);
            $fdisplay(result, "regfile6: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[6]);
            $fdisplay(result, "regfile7: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[7]);
            $fdisplay(result, "regfile8: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[8]);
            $fdisplay(result, "regfile9: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[9]);
            $fdisplay(result, "regfile10: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[10]);
            $fdisplay(result, "regfile11: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[11]);
            $fdisplay(result, "regfile12: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[12]);
            $fdisplay(result, "regfile13: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[13]);
            $fdisplay(result, "regfile14: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[14]);
            $fdisplay(result, "regfile15: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[15]);
            $fdisplay(result, "regfile16: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[16]);
            $fdisplay(result, "regfile17: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[17]);
            $fdisplay(result, "regfile18: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[18]);
            $fdisplay(result, "regfile19: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[19]);
            $fdisplay(result, "regfile20: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[20]);
            $fdisplay(result, "regfile21: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[21]);
            $fdisplay(result, "regfile22: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[22]);
            $fdisplay(result, "regfile23: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[23]);
            $fdisplay(result, "regfile24: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[24]);
            $fdisplay(result, "regfile25: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[25]);
            $fdisplay(result, "regfile26: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[26]);
            $fdisplay(result, "regfile27: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[27]);
            $fdisplay(result, "regfile28: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[28]);
            $fdisplay(result, "regfile29: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[29]);
            $fdisplay(result, "regfile30: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[30]);
            $fdisplay(result, "regfile31: %h", sccomp_dataflow_inst.sccpu.cpu_ref.array_reg[31]);
        end
    end
endmodule
