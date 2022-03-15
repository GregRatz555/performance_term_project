#include "VM.h"
#include <iostream>
#include <stdio.h>
#include <cstdint>

#include "Decode.h"

VM::VM()
{
  // TODO: REMOVE THIS. DEBUG
  //regs_.set(4, 16);
  //regs_.set(5, 32);
  //mem_.write_word(0, 0x004282b3); // add a5,a5,a4
}

void VM::dump()
{
  regs_.dump();
}

bool VM::run() {
  while(keep_running_) {
    const uint32_t current_pc = regs_.get_pc();
    const uint32_t current_instruction = mem_.read_word(current_pc);
    regs_.set_pc(current_pc+4);
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
  printf("Raw: 0x%X InstructionType: %d\n", raw_instruction, instruction);
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
  }
  return false;
}

void VM::dump_mem(uint32_t front, uint32_t back){
	mem_.debug_dump_range(front, back);
}

void VM::load_elf(const char *filename){
	/*
	printf("Loading ELF FIle: %s!\n", filename);
	std::ifstream elf_file;
	elf_file.open(filename, std::ifstream::in);
	char elf_header[53];
	elf_file.get(elf_header, 53);
	
	uint32_t address = 0;
	while (!elf_file.eof()){
		char word;
		elf_file.get(&word, 1);
		uint8_t representation = (uint8_t)word;
		printf("READ byte as %u\n", word);
		mem_.store(address++, representation);
	}
	*/
	uint32_t w_addr = 0;
	FILE *f = fopen(filename, "rb");
	char elf_header[53];
	char c;
	for (int i = 0; i < 53; i++){
		c = getc(f);
		elf_header[i] = c;
	}
	while (c != EOF) {
		mem_.store(w_addr++, (uint8_t)c);
		c = getc(f);
   }
   fclose(f);
}

