/*
 * ALU class
 * Handles Instruction 
 */

#ifndef __ALU__
#define __ALU__
#include "VM.h"
#include <cstdint>

class ALU {
	public:
		// R-type functions
		ALU();
		void ADD(VM& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
		void SUB(VM& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
		void OR (VM& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
		void XOR(VM& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
};

#endif
