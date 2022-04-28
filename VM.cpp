#include "VM.h"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>

#include "Decode.h"

VM::VM(const size_t mem_size)
 : mem_(mem_size)
{
}

void VM::dump(const bool force) const
{
  regs_.dump(force);
}

bool VM::run() {
  while(keep_running_) {
    const uint32_t current_pc = regs_.get_pc();
    const uint32_t current_instruction = mem_.read_data<uint32_t>(current_pc);
    execute(current_instruction);
    dump();
  }
  return true;
}

bool VM::run(uint32_t instruction_count) {
  for (uint32_t i = 0; i<instruction_count; i++) {
    const uint32_t current_pc = regs_.get_pc();
    const uint32_t current_instruction = mem_.read_data<uint32_t>(current_pc);
    execute(current_instruction);
    dump();
  }
  return true;
}

bool VM::execute(const uint32_t raw_instruction) {
  const Decode::InstructionType instruction = Decode::decode(raw_instruction);
  bool increment_pc = true;

  switch(instruction) {
    case Decode::kAddInstruction:
      alu_.ADD(regs_, Decode::decode_rd(raw_instruction), 
		Decode::decode_rs1(raw_instruction), 
		Decode::decode_rs2(raw_instruction));
      break;
    case Decode::kSubInstruction:
      alu_.SUB(regs_, Decode::decode_rd(raw_instruction), 
		Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction));
      break;
    case Decode::kXorInstruction:
      alu_.XOR(regs_, Decode::decode_rd(raw_instruction),
		Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction));
      break;
    case Decode::kOrInstruction:
      alu_.OR(regs_, Decode::decode_rd(raw_instruction),
		Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction));
      break;
    case Decode::kAndInstruction:
        alu_.AND(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_rs2(raw_instruction));
        break;
    case Decode::kShiftLeftLogicalInstruction:
        alu_.SLL(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_rs2(raw_instruction));
        break;
    case Decode::kShiftRightLogicalInstruction:
        alu_.SRL(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_rs2(raw_instruction));
        break;
    case Decode::kShiftRightArithmeticInstruction:
        alu_.SRA(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_rs2(raw_instruction));
        break;
    case Decode::kSetLessThanInstruction:
        alu_.SLT(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_rs2(raw_instruction));
        break;
    case Decode::kSetLessThanUInstruction:
        alu_.SLTU(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_rs2(raw_instruction));
        break;

    case Decode::kAddImmediateInstruction:
        alu_.ADDI(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_I_imm(raw_instruction));
        break;
    case Decode::kXorImmediateInstruction:
        alu_.XORI(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_I_imm(raw_instruction));
        break;
    case Decode::kOrImmediateInstruction:
        alu_.ORI(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_I_imm(raw_instruction));
        break;
    case Decode::kAndImmediateInstruction:
        alu_.ANDI(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_I_imm(raw_instruction));
        break;
    case Decode::kShiftLeftLogicalImmInstruction:
        alu_.SLLI(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_I_imm(raw_instruction));
        break;
    case Decode::kShiftRightLogicalImmInstruction:
        alu_.SRLI(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_I_imm(raw_instruction));
        break;
    case Decode::kShiftRightArithmeticImmInstruction:
        alu_.SRAI(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_I_imm(raw_instruction));
        break;
    case Decode::kSetLessThanImmInstruction:
        alu_.SLTI(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_I_imm(raw_instruction));
        break;
    case Decode::kSetLessThanUImmInstruction:
        alu_.SLTIU(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_I_imm(raw_instruction));
        break;

    case Decode::kLoadByteInstruction:
      mem_.load_byte(regs_, Decode::decode_rd(raw_instruction),
		Decode::decode_rs1(raw_instruction),
		Decode::decode_I_imm(raw_instruction));
      break;
    case Decode::kLoadHalfInstruction:
      mem_.load_half(regs_, Decode::decode_rd(raw_instruction),
		Decode::decode_rs1(raw_instruction),
		Decode::decode_I_imm(raw_instruction));
      break;
    case Decode::kLoadWordInstruction:
      mem_.load_word(regs_, Decode::decode_rd(raw_instruction),
		Decode::decode_rs1(raw_instruction),
		Decode::decode_LW_imm(raw_instruction));
      break;
    case Decode::kLoadByteUInstruction:
      mem_.load_u_byte(regs_, Decode::decode_rd(raw_instruction),
		Decode::decode_rs1(raw_instruction),
		Decode::decode_I_imm(raw_instruction));
      break;
    case Decode::kLoadHalfUInstruction:
      mem_.load_u_half(regs_, Decode::decode_rd(raw_instruction),
		Decode::decode_rs1(raw_instruction),
		Decode::decode_I_imm(raw_instruction));
      break;

    case Decode::kStoreByteInstruction:
      mem_.store_byte(regs_, Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction),
		Decode::decode_S_imm(raw_instruction));
      break;
    case Decode::kStoreHalfInstruction:
      mem_.store_half(regs_, Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction),
		Decode::decode_S_imm(raw_instruction));
      break;
    case Decode::kStoreWordInstruction:
      mem_.store_word(regs_, Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction),
		Decode::decode_S_imm(raw_instruction));
      break;

	case Decode::kBranchEqualInstruction:
	  increment_pc = alu_.BEQ(regs_, Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction),
		Decode::decode_B_imm(raw_instruction));
	  break;
	case Decode::kBranchNotEqualInstruction:
	  increment_pc = alu_.BNE(regs_, Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction),
		Decode::decode_B_imm(raw_instruction));
	  break;
	case Decode::kBranchLessThanInstruction:
	  increment_pc = alu_.BLT(regs_, Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction),
		Decode::decode_B_imm(raw_instruction));
	  break;
	case Decode::kBranchGreaterThanEqualInstruction:
	  increment_pc = alu_.BGE(regs_, Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction),
		Decode::decode_B_imm(raw_instruction));
	  break;
	case Decode::kBranchLessThanUInstruction:
	  increment_pc = alu_.BLTU(regs_, Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction),
		Decode::decode_B_imm(raw_instruction));
	  break;
	case Decode::kBranchGreaterThanEqualUInstruction:
	  increment_pc = alu_.BGEU(regs_, Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction),
		Decode::decode_B_imm(raw_instruction));
	  break;

  case Decode::kJumpAndLinkInstruction:
    // rd = PC+4
    regs_.set(Decode::decode_rd(raw_instruction), regs_.get_pc() + 4);
    // PC += IMM
    regs_.set_pc(regs_.get_pc() + Decode::decode_J_imm(raw_instruction));
    increment_pc = false;
    break;
  case Decode::kJumpAndLinkRegInstruction: {
      // read state now before potentially modified below
    const uint32_t rs1 = regs_.get(Decode::decode_rs1(raw_instruction));

    //rd = PC+4;
    regs_.set(Decode::decode_rd(raw_instruction), regs_.get_pc() + 4);
    //PC = rs1 + imm
    regs_.set_pc(rs1 + Decode::decode_I_imm(raw_instruction));

    increment_pc = false;
    }
    break;

  case Decode::kLoadUpperImmInstruction:
    // rd = imm << 12
    regs_.set(Decode::decode_rd(raw_instruction), Decode::decode_U_imm(raw_instruction));
    break;
  case Decode::kAddUpperImmToPCInstruction:
    // rd = PC + (imm << 12)
    regs_.set(Decode::decode_rd(raw_instruction), (regs_.get_pc() + (Decode::decode_U_imm(raw_instruction)) ));
    break;

  case Decode::kEnvironmentCallInstruction:
    // Transfer control to OS
    // do nothing
    break;
  case Decode::kEnvironmentBreakInstruction:
    // Transfer control to debugger
    // do nothing
    break;

    case Decode::kInvalidInstruction:
      // fallthrough
    default:
      throw std::runtime_error("Invalid or unknown instruction id: " +
			 std::to_string(instruction) + " [" + std::to_string(raw_instruction) + "]");
  }

  if(increment_pc) {
    regs_.set_pc(regs_.get_pc()+sizeof(uint32_t));
  }

  return true;
}

void VM::dump_mem(uint32_t front, uint32_t back) const
{
       mem_.debug_dump_range(front, back);
}

void VM::load_elf(const std::string &filename){

  std::ifstream input_file(filename, std::ios::binary);
  input_file.seekg(0, std::ios::end);
  const auto size = input_file.tellg();
  input_file.seekg(0);

  std::vector<uint8_t> data;
  data.resize(size);
  input_file.read((char*)data.data(), size);

  for(int i = 0; i < size; i++) {
    mem_.store(i, data[i]);
  }
}

const RegisterValues& VM::get_regs() const
{
  return regs_.get_values();
}
void VM::set_regs(const RegisterValues &new_regs)
{
  regs_.set_values(new_regs);
}

const Memory& VM::get_mem() const
{
  return mem_;
}

void VM::set_mem(const Memory &new_mem)
{
  mem_ = new_mem;
}
