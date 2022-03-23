#include "ALU.h"

ALU::ALU(){
}

// R-Type Instructions
void ALU::ADD(Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  mstate.set(rd, mstate.get(rs1) + mstate.get(rs2));
}

void ALU::SUB(Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  mstate.set(rd, mstate.get(rs1) - mstate.get(rs2));
}

void ALU::OR (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  mstate.set(rd, mstate.get(rs1) | mstate.get(rs2));
}

void ALU::XOR(Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  mstate.set(rd, mstate.get(rs1) ^ mstate.get(rs2));
}

void ALU::AND(Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  mstate.set(rd, mstate.get(rs1) & mstate.get(rs2));
}

void ALU::SLL(Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  mstate.set(rd, mstate.get(rs1) << mstate.get(rs2));
}

void ALU::SRL(Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  mstate.set(rd, mstate.get(rs1) >> mstate.get(rs2));
}

void ALU::SRA(Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  mstate.set(rd, mstate.get(rs1) >> mstate.get(rs2));
}

void ALU::SLT(Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  mstate.set(rd, ((int32_t)mstate.get(rs1) < (int32_t)mstate.get(rs2)) ? 1 : 0);
}
 
void ALU::SLTU(Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  mstate.set(rd, ((uint32_t)mstate.get(rs1) < (uint32_t)mstate.get(rs2)) ? 1 : 0);
}

void ALU::ADDI(Registers& mstate, uint8_t rd, uint8_t rs1, int32_t imm){
  mstate.set(rd, mstate.get(rs1) + imm);
}

void ALU::XORI(Registers& mstate, uint8_t rd, uint8_t rs1, int32_t imm){
  mstate.set(rd, mstate.get(rs1) ^ imm);
}

void ALU::ORI(Registers& mstate, uint8_t rd, uint8_t rs1, int32_t imm){
  mstate.set(rd, mstate.get(rs1) | imm);
}

void ALU::ANDI(Registers& mstate, uint8_t rd, uint8_t rs1, int32_t imm){
  mstate.set(rd, mstate.get(rs1) & imm);
}

void ALU::SLLI(Registers& mstate, uint8_t rd, uint8_t rs1, int32_t imm){
  imm &= 0x000F;
  mstate.set(rd, mstate.get(rs1) << imm);
}

void ALU::SRLI(Registers& mstate, uint8_t rd, uint8_t rs1, int32_t imm){
  imm &= 0x000F;
  mstate.set(rd, mstate.get(rs1) >> imm);
}

void ALU::SRAI(Registers& mstate, uint8_t rd, uint8_t rs1, int32_t imm){
  imm &= 0x000F;
  mstate.set(rd, mstate.get(rs1) >> imm);
}

void ALU::SLTI(Registers& mstate, uint8_t rd, uint8_t rs1, int32_t imm){
  mstate.set(rd, ((int32_t)mstate.get(rs1) < imm) ? 1 : 0);
}

void ALU::SLTIU(Registers& mstate, uint8_t rd, uint8_t rs1, int32_t imm){
  mstate.set(rd, ((uint32_t)mstate.get(rs1) < imm) ? 1 : 0);
}

void ALU::BEQ(Registers& mstate, uint8_t rs1, uint8_t rs2, int32_t imm){
	if (mstate.get(rs1) == mstate.get(rs2)) {
		mstate.set_pc(mstate.get_pc() + imm);
	}
}

void ALU::BNE(Registers& mstate, uint8_t rs1, uint8_t rs2, int32_t imm){
	if (mstate.get(rs1) != mstate.get(rs2)) {
		mstate.set_pc(mstate.get_pc() + imm);
	}
}

void ALU::BLT(Registers& mstate, uint8_t rs1, uint8_t rs2, int32_t imm){
	if ((int32_t)mstate.get(rs1) < (int32_t)mstate.get(rs2)) {
		mstate.set_pc(mstate.get_pc() + imm);
	}
}

void ALU::BGE(Registers& mstate, uint8_t rs1, uint8_t rs2, int32_t imm){
	if ((int32_t)mstate.get(rs1) >= (int32_t)mstate.get(rs2)) {
		mstate.set_pc(mstate.get_pc() + imm);
	}
}

void ALU::BLTU(Registers& mstate, uint8_t rs1, uint8_t rs2, int32_t imm){
	if (mstate.get(rs1) < mstate.get(rs2)) {
		mstate.set_pc(mstate.get_pc() + imm);
	}
}

void ALU::BGEU(Registers& mstate, uint8_t rs1, uint8_t rs2, int32_t imm){
	if (mstate.get(rs1) >= mstate.get(rs2)) {
		mstate.set_pc(mstate.get_pc() + imm);
	}
}
