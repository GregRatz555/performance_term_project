/*
 * ALU class
 * Handles Instruction 
 */

#ifndef __ALU__
#define __ALU__

#include <cstdint>

#include "Registers.h"

class ALU {
  public:
    ALU();
    // R-type functions
    void ADD (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
    void SUB (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
    void OR  (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
    void XOR (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
    void SLL (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
    void SRL (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
    void SRA (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
    void SLT (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
    void SLTU(Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
    // I-type functions (excluding memory ops in Memory.h)
	void ADDI (Registers& mstate, uint8_t rd, uint8_t rs1, uint16_t imm);
	void XORI (Registers& mstate, uint8_t rd, uint8_t rs1, uint16_t imm);
	void ORI  (Registers& mstate, uint8_t rd, uint8_t rs1, uint16_t imm);
	void ANDI (Registers& mstate, uint8_t rd, uint8_t rs1, uint16_t imm);
	void SLLI (Registers& mstate, uint8_t rd, uint8_t rs1, uint16_t imm);
	void SRLI (Registers& mstate, uint8_t rd, uint8_t rs1, uint16_t imm);
	void SRAI (Registers& mstate, uint8_t rd, uint8_t rs1, uint16_t imm);
	void SLTI (Registers& mstate, uint8_t rd, uint8_t rs1, uint16_t imm);
	void SLTIU(Registers& mstate, uint8_t rd, uint8_t rs1, uint16_t imm);
	// B-type functions
	void BEQ (Registers& mstate, uint8_t rs1, uint8_t rs2, int16_t imm);
	void BNE (Registers& mstate, uint8_t rs1, uint8_t rs2, int16_t imm);
	void BLT (Registers& mstate, uint8_t rs1, uint8_t rs2, int16_t imm);
	void BGE (Registers& mstate, uint8_t rs1, uint8_t rs2, int16_t imm);
	void BLTU(Registers& mstate, uint8_t rs1, uint8_t rs2, int16_t imm);
	void BGEU(Registers& mstate, uint8_t rs1, uint8_t rs2, int16_t imm);
	
};

#endif
