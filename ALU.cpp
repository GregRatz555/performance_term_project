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

void ALU::JALR(Registers& mstate, uint8_t rd, uint8_t rs1, int32_t imm){
    mstate.set(rd, mstate.get_pc() + 4);
    mstate.set_pc(mstate.get(rs1) + imm);
}

// J-type function

void ALU::JAL  (Registers& mstate, uint8_t rd, int32_t imm){
    mstate.set(rd, mstate.get_pc() + 4);
    mstate.set_pc(mstate.get_pc() + imm);
}

//B-type functions

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
	if ((int32_t)mstate.get(rs1) < (int32_t)mstate.get(rs2)) {
		mstate.set_pc(static_cast<int32_t>(mstate.get_pc()) + imm);
    return false;
	}
  return true;
}

bool ALU::BGE(Registers& mstate, uint8_t rs1, uint8_t rs2, int32_t imm){
	if ((int32_t)mstate.get(rs1) >= (int32_t)mstate.get(rs2)) {
		mstate.set_pc(static_cast<int32_t>(mstate.get_pc()) + imm);
    return false;
	}
  return true;
}

bool ALU::BLTU(Registers& mstate, uint8_t rs1, uint8_t rs2, int32_t imm){
	if (mstate.get(rs1) < mstate.get(rs2)) {
		mstate.set_pc(static_cast<int32_t>(mstate.get_pc()) + imm);
    return false;
	}
  return true;
}

bool ALU::BGEU(Registers& mstate, uint8_t rs1, uint8_t rs2, int32_t imm){
	if (mstate.get(rs1) >= mstate.get(rs2)) {
		mstate.set_pc(static_cast<int32_t>(mstate.get_pc()) + imm);
    return false;
	}
  return true;
}

// B-type Instructions
void ALU::LUI(Registers& mstate, uint8_t rd,  uint32_t imm){
    mstate.set(rd, imm << 12);
}
void ALU::AUIPC(Registers& mstate, uint8_t rd,  uint32_t imm){
    mstate.set(rd, mstate.get_pc() + (imm << 12));
}

// Multiply Extension Functions

void ALU::MUL (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2){
	int32_t result = ((int32_t)mstate.get(rs1) * (int32_t)mstate.get(rs2));
	mstate.set(rd, result);
}

void ALU::MULH (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2){
	int64_t result = ((int64_t)mstate.get(rs1) * (int64_t)mstate.get(rs2));
	mstate.set(rd, (uint32_t)(result >> 32));
}

void ALU::MULSU (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2){
	int64_t result = ((int64_t)mstate.get(rs1) * (uint64_t)mstate.get(rs2));
	mstate.set(rd, (uint32_t)(result >> 32));
}

void ALU::MULU (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2){
	uint64_t result = ((uint64_t)mstate.get(rs1) * (uint64_t)mstate.get(rs2));
	mstate.set(rd, (uint32_t)(result >> 32));
}

void ALU::DIV (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2){
	int32_t result = ((int32_t)mstate.get(rs1) / (int32_t)mstate.get(rs2));
	mstate.set(rd, result);
}

void ALU::DIVU (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2){
	uint32_t result = ((uint32_t)mstate.get(rs1) / (uint32_t)mstate.get(rs2));
	mstate.set(rd, result);
}

void ALU::REM (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2){
	int32_t result = ((int32_t)mstate.get(rs1) % (int32_t)mstate.get(rs2));
	mstate.set(rd, result);
}

void ALU::REMU (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2){
	uint32_t result = ((uint32_t)mstate.get(rs1) % (uint32_t)mstate.get(rs2));
	mstate.set(rd, result);
}
