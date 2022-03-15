#include "VM.h"
#include <iostream>
#include <stdio.h>
#include <cstdint>

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
      alu_.ADD(regs_, Decode::decode_rd(raw_instruction), Decode::decode_rs1(raw_instruction), Decode::decode_rs2(raw_instruction));
      break;
    case Decode::kSubInstruction:
      alu_.SUB(regs_, Decode::decode_rd(raw_instruction), Decode::decode_rs1(raw_instruction), Decode::decode_rs2(raw_instruction));
      break;
    case Decode::kXorInstruction:
      alu_.XOR(regs_, Decode::decode_rd(raw_instruction), Decode::decode_rs1(raw_instruction), Decode::decode_rs2(raw_instruction));
      break;
    case Decode::kOrInstruction:
      alu_.OR(regs_, Decode::decode_rd(raw_instruction), Decode::decode_rs1(raw_instruction), Decode::decode_rs2(raw_instruction));
      break;

    case Decode::kLoadByteInstruction:
      mem_.load_byte(regs_, Decode::decode_rd(raw_instruction), Decode::decode_rs1(raw_instruction), Decode::decode_I_imm(raw_instruction));
      break;
    case Decode::kLoadHalfInstruction:
      mem_.load_half(regs_, Decode::decode_rd(raw_instruction), Decode::decode_rs1(raw_instruction), Decode::decode_I_imm(raw_instruction));
      break;
    case Decode::kLoadWordInstruction:
      mem_.load_word(regs_, Decode::decode_rd(raw_instruction), Decode::decode_rs1(raw_instruction), Decode::decode_I_imm(raw_instruction));
      break;
    case Decode::kLoadByteUInstruction:
      mem_.load_u_byte(regs_, Decode::decode_rd(raw_instruction), Decode::decode_rs1(raw_instruction), Decode::decode_I_imm(raw_instruction));
      break;
    case Decode::kLoadHalfUInstruction:
      mem_.load_u_half(regs_, Decode::decode_rd(raw_instruction), Decode::decode_rs1(raw_instruction), Decode::decode_I_imm(raw_instruction));
      break;

    case Decode::kStoreByteInstruction:
      mem_.store_byte(regs_, Decode::decode_rs1(raw_instruction), Decode::decode_rs2(raw_instruction), Decode::decode_S_imm(raw_instruction));
      break;
    case Decode::kStoreHalfInstruction:
      mem_.store_half(regs_, Decode::decode_rs1(raw_instruction), Decode::decode_rs2(raw_instruction), Decode::decode_S_imm(raw_instruction));
      break;
    case Decode::kStoreWordInstruction:
      mem_.store_word(regs_, Decode::decode_rs1(raw_instruction), Decode::decode_rs2(raw_instruction), Decode::decode_S_imm(raw_instruction));
      break;

    case Decode::kInvalidInstruction:
      // fallthrough
    default:
      throw std::runtime_error("Invalid or unknown instruction id: " + std::to_string(instruction) + " [" + std::to_string(raw_instruction) + "]");
  }
  return true;
}

void VM::dump_mem(uint32_t front, uint32_t back){
	mem_.debug_dump_range(front, back);
}

void VM::load_elf(const char *filename){
    // TODO parse elf header?
	printf("Loading ELF FIle: %s!\n", filename);
	uint32_t w_addr = 0;
	FILE *f = fopen(filename, "rb");
    // Read in the header
	char elf_header[53];
	char c;
	for (int i = 0; i < 53; i++){
		c = getc(f);
		elf_header[i] = c;
	}
    // Read in the rest of the ELF
	while (c != EOF) {
		mem_.store(w_addr++, (uint8_t)c);
		c = getc(f);
   }
   fclose(f);
}
