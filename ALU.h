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
    void AND (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
    void SLL (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
    void SRL (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
    void SRA (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
    void SLT (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
    void SLTU(Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
    // I-type functions (excluding load ops held in Memory.h, with S-type functions)
	void ADDI (Registers& mstate, uint8_t rd, uint8_t rs1, int32_t imm);
	void XORI (Registers& mstate, uint8_t rd, uint8_t rs1, int32_t imm);
	void ORI  (Registers& mstate, uint8_t rd, uint8_t rs1, int32_t imm);
	void ANDI (Registers& mstate, uint8_t rd, uint8_t rs1, int32_t imm);
	void SLLI (Registers& mstate, uint8_t rd, uint8_t rs1, int32_t imm);
	void SRLI (Registers& mstate, uint8_t rd, uint8_t rs1, int32_t imm);
	void SRAI (Registers& mstate, uint8_t rd, uint8_t rs1, int32_t imm);
	void SLTI (Registers& mstate, uint8_t rd, uint8_t rs1, int32_t imm);
	void SLTIU(Registers& mstate, uint8_t rd, uint8_t rs1, int32_t imm);
	void JALR (Registers& mstate, uint8_t rd, uint8_t rs1, int32_t imm);
	// J-type function
	void JAL  (Registers& mstate, uint8_t rd, int32_t imm);
	// B-type functions
	bool BEQ  (Registers& mstate, uint8_t rs1, uint8_t rs2, int32_t imm);
	bool BNE  (Registers& mstate, uint8_t rs1, uint8_t rs2, int32_t imm);
	bool BLT  (Registers& mstate, uint8_t rs1, uint8_t rs2, int32_t imm);
	bool BGE  (Registers& mstate, uint8_t rs1, uint8_t rs2, int32_t imm);
	bool BLTU (Registers& mstate, uint8_t rs1, uint8_t rs2, int32_t imm);
	bool BGEU (Registers& mstate, uint8_t rs1, uint8_t rs2, int32_t imm);
	// U-type functions
	void LUI  (Registers& mstate, uint8_t rd,  uint32_t imm);
	void AUIPC(Registers& mstate, uint8_t rd,  uint32_t imm);
    // M-extension functions
    void MUL  (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
    void MULH (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
    void MULSU(Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
    void MULU (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
    void DIV  (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
    void DIVU (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
    void REM  (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
    void REMU (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
};

#endif
