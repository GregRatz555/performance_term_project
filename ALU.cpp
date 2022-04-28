#include "ALU.h"

ALU::ALU(){
}

// R-Type Instructions
void ALU::ADD(Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  mstate.set(rd, static_cast<int32_t>(mstate.get(rs1)) + static_cast<int32_t>(mstate.get(rs2)));
}

void ALU::SUB(Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  mstate.set(rd, static_cast<int32_t>(mstate.get(rs1)) - static_cast<int32_t>(mstate.get(rs2)));
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
  mstate.set(rd, static_cast<uint32_t>(mstate.get(rs1)) >> mstate.get(rs2));
}

void ALU::SRA(Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  mstate.set(rd, static_cast<int32_t>(mstate.get(rs1)) >> mstate.get(rs2));
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
  imm &= 0b11111;
  mstate.set(rd, mstate.get(rs1) << imm);
}

void ALU::SRLI(Registers& mstate, uint8_t rd, uint8_t rs1, int32_t imm){
  imm &= 0b11111;
  mstate.set(rd, mstate.get(rs1) >> imm);
}

void ALU::SRAI(Registers& mstate, uint8_t rd, uint8_t rs1, int32_t imm){
  imm &= 0x000F;
  mstate.set(rd, static_cast<int32_t>(mstate.get(rs1)) >> imm);
}

void ALU::SLTI(Registers& mstate, uint8_t rd, uint8_t rs1, int32_t imm){
  mstate.set(rd, ((int32_t)mstate.get(rs1) < imm) ? 1 : 0);
}

void ALU::SLTIU(Registers& mstate, uint8_t rd, uint8_t rs1, uint32_t imm){
  mstate.set(rd, (mstate.get(rs1) < imm) ? 1 : 0);
}

bool ALU::BEQ(Registers& mstate, uint8_t rs1, uint8_t rs2, int32_t imm){
	if (mstate.get(rs1) == mstate.get(rs2)) {
		mstate.set_pc(static_cast<int32_t>(mstate.get_pc()) + imm);
    return false;
	}
  return true;
}

bool ALU::BNE(Registers& mstate, uint8_t rs1, uint8_t rs2, int32_t imm){
	if (mstate.get(rs1) != mstate.get(rs2)) {
		mstate.set_pc(static_cast<int32_t>(mstate.get_pc()) + imm);
    return false;
	}
  return true;
}

bool ALU::BLT(Registers& mstate, uint8_t rs1, uint8_t rs2, int32_t imm){
  const int32_t lhs = mstate.get(rs1);
  const int32_t rhs = mstate.get(rs2);
	if (lhs < rhs) {
		mstate.set_pc(static_cast<int32_t>(mstate.get_pc()) + imm);
    return false;
	}
  return true;
}

bool ALU::BGE(Registers& mstate, uint8_t rs1, uint8_t rs2, int32_t imm){
  const int32_t lhs = mstate.get(rs1);
  const int32_t rhs = mstate.get(rs2);
	if (lhs >= rhs) {
		mstate.set_pc(static_cast<int32_t>(mstate.get_pc()) + imm);
    return false;
	}
  return true;
}

bool ALU::BLTU(Registers& mstate, uint8_t rs1, uint8_t rs2, int32_t imm){
  const uint32_t lhs = mstate.get(rs1);
  const uint32_t rhs = mstate.get(rs2);
	if (lhs < rhs) {
		mstate.set_pc(static_cast<int32_t>(mstate.get_pc()) + imm);
    return false;
	}
  return true;
}

bool ALU::BGEU(Registers& mstate, uint8_t rs1, uint8_t rs2, int32_t imm){
  const uint32_t lhs = mstate.get(rs1);
  const uint32_t rhs = mstate.get(rs2);
	if (lhs >= rhs) {
		mstate.set_pc(static_cast<int32_t>(mstate.get_pc()) + imm);
    return false;
	}
  return true;
}
