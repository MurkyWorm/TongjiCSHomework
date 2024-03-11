#include <iostream>
#include <map>
#include <string.h>
#include <fstream>
using namespace std;

int main() {
	//opCode·­Òë
	map<string, string>opCode;
	opCode["NOP"] = "0";
	opCode["HALT"] = "1";
	opCode["ADD"] = "2";
	opCode["ADDI"] = "3";
	opCode["SUB"] = "4";
	opCode["SUBI"] = "5";
	opCode["SRL"] = "6";
	opCode["CMP"] = "7";
	opCode["JUMP"] = "8";
	opCode["BN"] = "9";
	opCode["BNN"] = "a";
	opCode["BZ"] = "b";
	opCode["BNZ"] = "c";
	opCode["LOAD"] = "d";
	opCode["STORE"] = "e";
	//¼Ä´æÆ÷·­Òë
	map<string, string>regs;
	regs["r0"] = "0";
	regs["r1"] = "1";
	regs["r2"] = "2";
	regs["r3"] = "3";
	regs["r4"] = "4";
	regs["r5"] = "5";
	regs["r6"] = "6";
	regs["r7"] = "7";
	regs["r8"] = "8";
	regs["r9"] = "9";
	regs["r10"] = "a";
	regs["r11"] = "b";
	regs["r12"] = "c";
	regs["r13"] = "d";
	regs["r14"] = "e";
	regs["r15"] = "f";
	
	ifstream complication;
	complication.open("stumbEggsComplicationClear.txt", ios::in);
	if (!complication) {
		cout << "can't open complication file!" << endl;
		exit(-1);
	}
	ofstream machine;
	machine.open("stumbEggsMachine.coe", ios::out);
	if (!machine) {
		cout << "can't open machine file!" << endl;
		exit(-1);
	}
	ofstream machineLook;
	machineLook.open("stumbEggsMachineLook.coe", ios::out);
	if (!machineLook) {
		cout << "can't open machineLook file!" << endl;
		exit(-1);
	}
	machine << "memory_initialization_radix = 16;" << endl;
	machine << "memory_initialization_vector =" << endl;
	machineLook << "memory_initialization_radix = 16;" << endl;
	machineLook << "memory_initialization_vector =" << endl;
	int num;
	complication >> num;
	for (int i = 0; i <= num; i++) {
		int id;
		string op_code;
		string reg;
		string val;
		complication >> id;
		complication >> op_code;
		machine << opCode[op_code];
		machineLook << i << "    ";
		machineLook << opCode[op_code];
		if (op_code == "NOP") {
			machine << "000";
			machineLook << "000";
		}
		else if (op_code == "HALT") {
			machine << "000";
			machineLook << "000";
		}
		else if (op_code == "ADD") {
			complication >> reg;
			machine << regs[reg];
			machineLook << regs[reg];
			complication >> reg;
			machine << regs[reg];
			machineLook << regs[reg];
			complication >> reg;
			machine << regs[reg];
			machineLook << regs[reg];
		}
		else if (op_code == "ADDI") {
			complication >> reg;
			machine << regs[reg];
			machineLook << regs[reg];
			complication >> val;
			machine << val;
			machineLook << val;
			complication >> val;
			machine << val;
			machineLook << val;
		}
		else if (op_code == "SUB") {
			complication >> reg;
			machine << regs[reg];
			machineLook << regs[reg];
			complication >> reg;
			machine << regs[reg];
			machineLook << regs[reg];
			complication >> reg;
			machine << regs[reg];
			machineLook << regs[reg];
		}
		else if (op_code == "SUBI") {
			complication >> reg;
			machine << regs[reg];
			machineLook << regs[reg];
			complication >> val;
			machine << val;
			machineLook << val;
			complication >> val;
			machine << val;
			machineLook << val;
		}
		else if (op_code == "SRL") {
			complication >> reg;
			machine << regs[reg];
			machineLook << regs[reg];
			complication >> reg;
			machine << regs[reg];
			machineLook << regs[reg];
			complication >> val;
			machine << val;
			machineLook << val;
		}
		else if (op_code == "CMP") {
			machine << "0";
			machineLook << "0";
			complication >> reg;
			machine << regs[reg];
			machineLook << regs[reg];
			complication >> reg;
			machine << regs[reg];
			machineLook << regs[reg];
		}
		else if (op_code == "JUMP") {
			machine << "0";
			machineLook << "0";
			complication >> val;
			machine << val;
			machineLook << val;
			complication >> val;
			machine << val;
			machineLook << val;
		}
		else if (op_code == "BN") {
			complication >> reg;
			machine << regs[reg];
			machineLook << regs[reg];
			complication >> val;
			machine << val;
			machineLook << val;
			complication >> val;
			machine << val;
			machineLook << val;
		}
		else if (op_code == "BNN") {
			complication >> reg;
			machine << regs[reg];
			machineLook << regs[reg];
			complication >> val;
			machine << val;
			machineLook << val;
			complication >> val;
			machine << val;
			machineLook << val;
		}
		else if (op_code == "BZ") {
			complication >> reg;
			machine << regs[reg];
			machineLook << regs[reg];
			complication >> val;
			machine << val;
			machineLook << val;
			complication >> val;
			machine << val;
			machineLook << val;
		}
		else if (op_code == "BNZ") {
			complication >> reg;
			machine << regs[reg];
			machineLook << regs[reg];
			complication >> val;
			machine << val;
			machineLook << val;
			complication >> val;
			machine << val;
			machineLook << val;
		}
		else if (op_code == "LOAD") {
			complication >> reg;
			machine << regs[reg];
			machineLook << regs[reg];
			complication >> reg;
			machine << regs[reg];
			machineLook << regs[reg];
			complication >> val;
			machine << val;
			machineLook << val;
		}
		else if (op_code == "STORE") {
			complication >> reg;
			machine << regs[reg];
			machineLook << regs[reg];
			complication >> reg;
			machine << regs[reg];
			machineLook << regs[reg];
			complication >> val;
			machine << val;
			machineLook << val;
		}
		machine << endl;
		machineLook << endl;
	}
	complication.close();
	machine.close();
	machineLook.close();
}