#include "VM.h"
#include <stdint.h>

VM::VM(){
	init_registers();
}

//inline void VM::init_registers() {
void VM::init_registers() {
	for (int r=0; r<32; r++) {reg[r] = 0x0000;}
	pc = 0x0000;
}
//
