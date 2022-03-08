/*
 * CPU class
 * Handles Instruction 
 * Possibly should be renamed ALU
 */

#ifndef __CPU__
#define __CPU__

class CPU {
	public:
		// R-type functions
		CPU();
		void INSR_ADD(VM* mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
		void INSR_SUB(VM* mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
		void INSR_OR (VM* mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
		void INSR_XOR(VM* mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
};

#endif
