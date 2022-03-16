#include "VM.h"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>

#include "Decode.h"

VM::VM()
{
}

void VM::dump()
{
  regs_.dump();
}

bool VM::run() {
  while(keep_running_) {
    const uint32_t current_pc = regs_.get_pc();
    const uint32_t current_instruction = mem_.read_word(current_pc);
    regs_.set_pc(current_pc+sizeof(uint32_t));
    execute(current_instruction);
    dump();
  }
  return true;
}

bool VM::run(uint32_t instruction_count) {
  for (uint32_t i = 0; i<instruction_count; i++) {
    const uint32_t current_pc = regs_.get_pc();
    const uint32_t current_instruction = mem_.read_word(current_pc);
    regs_.set_pc(current_pc+4);
    execute(current_instruction);
    dump();
  }
  return true;
}

bool VM::execute(const uint32_t raw_instruction) {
  const Decode::InstructionType instruction = Decode::decode(raw_instruction);
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
		Decode::decode_I_imm(raw_instruction));
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
	  alu_.BEQ(regs_, Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction),
		Decode::decode_B_imm(raw_instruction));
	  break;
	case Decode::kBranchNotEqualInstruction:
	  alu_.BNE(regs_, Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction),
		Decode::decode_B_imm(raw_instruction));
	  break;
	case Decode::kBranchLessThanInstruction:
	  alu_.BLT(regs_, Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction),
		Decode::decode_B_imm(raw_instruction));
	  break;
	case Decode::kBranchGreaterThanEqualInstruction:
	  alu_.BGE(regs_, Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction),
		Decode::decode_B_imm(raw_instruction));
	  break;
	case Decode::kBranchLessThanUInstruction:
	  alu_.BLTU(regs_, Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction),
		Decode::decode_B_imm(raw_instruction));
	  break;
	case Decode::kBranchGreaterThanEqualUInstruction:
	  alu_.BGEU(regs_, Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction),
		Decode::decode_B_imm(raw_instruction));
	  break;

    case Decode::kAddUpperImmToPCInstruction:
      regs_.set(Decode::decode_rd(raw_instruction), (regs_.get_pc() + (Decode::decode_U_imm(raw_instruction)<<12) ));
      break;

    case Decode::kInvalidInstruction:
      // fallthrough
    default:
      throw std::runtime_error("Invalid or unknown instruction id: " +
			 std::to_string(instruction) + " [" + std::to_string(raw_instruction) + "]");
  }
  return true;
}

void VM::dump_mem(uint32_t front, uint32_t back){
       mem_.debug_dump_range(front, back);
}

void VM::load_elf(const std::string &filename){
  printf("Loading Bin File: %s!\n", filename.c_str());

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
