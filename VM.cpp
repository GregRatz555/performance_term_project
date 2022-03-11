#include "VM.h"
#include <iostream>
#include <cstdint>

VM::VM(){
	init_registers();
}

void VM::init_registers() {
	for (int r=0; r<32; r++) {reg[r] = 0x0000;}
	pc = 0x0000;
}

uint8_t VM::set_reg(uint8_t rd, uint32_t value){
	// Safe way of setting registers
	// Register 0 must be 0, it is always 0
	// Returns success state
	// Could be replaced in decode step
	if (rd > 31){
		std::cerr << "Nonexistant register referenced";
		std::cerr << "At pc = " << pc;
		return 1;
	}
	if (rd != 0) reg[rd] = value;
	return 0;
}

uint32_t VM::get_reg(uint8_t rd){
	// Safe way of getting register values
	// Register 0 must be 0, it is always 0
	// returns register value
	if (rd > 31) {
		std::cerr << "Fatal: Nonexistant register referenced";
		std::cerr << "At pc = " << pc;
		exit(1); // TODO get better error system
	}
	if (rd == 0) return 0;
	return reg[rd];
}

void VM::dump_reg(){
	// Prints all register states
	for (int r=0; r<32; r++) {
		std::cout << "REG[" << r << "]:\t" << reg[r] << std::endl;
	}
}
