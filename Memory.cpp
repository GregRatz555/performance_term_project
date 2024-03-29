#include "Memory.h"
#include <iostream>
#include <cstdint>
#include <ctime>
#include <chrono>

Memory::Memory(const std::size_t memsize){
  init(memsize);
}

uint8_t Memory::init(uint32_t memsize){
	// Try to create a sector of memory with the given size,
	// Return success of operation
    /* (doesn't work, initial pointer not null?)
	if (Memory::storage != 0) {
		// Avoid memleak and use-after-free
		// If for some reason a memory is re-init'ed, lose the old
		free(Memory::storage);
		Memory::storage = 0;
	}
    */
	// Create an empty memory block
	Memory::storage = (uint8_t*)calloc(memsize, sizeof(uint8_t));
	if (Memory::storage == NULL) {
		// In case of failure, reset attributes
		Memory::addr_range[0] = 0x0000;
		Memory::addr_range[1] = 0x0000;
		Memory::size = 0;
		return 1;
	} else {
		// Else update attributes
		Memory::addr_range[0] = 0x0000;
		Memory::addr_range[1] = 0x0000 + memsize;
		Memory::size = memsize;
		return 0;
	}
}

uint8_t Memory::check_address(uint32_t address) const {
	return ((address >= addr_range[0]) && (address < addr_range[1])) ? 0 : 1;
}

uint8_t Memory::load(uint32_t req_address) const {
	if (Memory::check_address(req_address) == 0) {
		return Memory::storage[req_address];
	} else {
		std::cerr << "Fatal: load fail at addr=" << req_address << std::endl;
		exit(1);
	}
}

uint8_t Memory::store(uint32_t req_address, uint8_t value){
  if(req_address == 0xDEADBEEE) {
    printf("%c", value);
  } else if(Memory::check_address(req_address) == 0){
		Memory::storage[req_address] = value;
		return 0;
	}
	return 1;
}

int8_t Memory::load_byte(Registers& regs, uint8_t rd, uint8_t rs1, int32_t imm){
	uint32_t base = regs.get(rs1);
	uint32_t req_address = base + imm;
	uint32_t result = Memory::load(req_address);
	return regs.set(rd, Decode::sign_extend(result, 8));
}

int8_t Memory::load_half(Registers& regs, uint8_t rd, uint8_t rs1, int32_t imm){
	uint32_t base = regs.get(rs1);
	uint32_t req_address = base + imm;
	uint32_t result = (Memory::load(req_address+1) << 8)
      | Memory::load(req_address);
	return regs.set(rd, Decode::sign_extend(result, 16));
}

int8_t Memory::load_u_byte(Registers& regs, uint8_t rd, uint8_t rs1, int32_t imm){
	uint32_t base = regs.get(rs1);
	uint32_t req_address = base + imm;
	uint32_t result = Memory::load(req_address);
	return regs.set(rd, result);
}

int8_t Memory::load_u_half(Registers& regs, uint8_t rd, uint8_t rs1, int32_t imm){
	uint32_t base = regs.get(rs1);
	uint32_t req_address = base + imm;
	uint32_t result = (Memory::load(req_address+1) << 8)
      | Memory::load(req_address);
	return regs.set(rd, result);
}

int8_t Memory::load_word(Registers& regs, uint8_t rd, uint8_t rs1, int32_t imm){
	const uint32_t base = regs.get(rs1);
	const uint32_t req_address = base + imm;
	uint32_t result;

  if(req_address == 0xDEADBEE0) {
    result = read_clock();
  } else {
	  result = (Memory::load(req_address+3) << 24)
	    | (Memory::load(req_address+2) << 16)
	    | (Memory::load(req_address+1) << 8)
	    | Memory::load(req_address);
  }
	return regs.set(rd, result);
}

uint32_t Memory::read_clock() {
  static const auto start_time = std::chrono::high_resolution_clock::now();
  const auto now = std::chrono::high_resolution_clock::now();
  return (now - start_time).count() / 1000000;
}

int8_t Memory::store_byte(Registers& regs, uint8_t rs1, uint8_t rs2, int32_t imm){
	uint32_t base = regs.get(rs1);
	uint32_t req_address = base + imm;
	uint8_t  write_value = (regs.get(rs2) & 0xFF);
	return Memory::store(req_address, write_value);
}

int8_t Memory::store_half(Registers& regs, uint8_t rs1, uint8_t rs2, int32_t imm){
	uint32_t base = regs.get(rs1);
	uint32_t req_address = base + imm;
	uint32_t reg_value = regs.get(rs2);
	uint8_t write_value = (reg_value & 0xFF00) >> 8;
	if (Memory::store(req_address+1, write_value) == 1) return 1;
	write_value = reg_value & 0xFF;
	return Memory::store(req_address, write_value);
}

int8_t Memory::store_word(Registers& regs, uint8_t rs1, uint8_t rs2, int32_t imm){
	uint32_t base = regs.get(rs1);
	uint32_t req_address = base + imm;
	uint32_t reg_value = regs.get(rs2);
	uint8_t write_value = (reg_value & 0xFF000000) >> 24;
	if (Memory::store(req_address+3, write_value) == 1) return 1;
	write_value = (reg_value & 0xFF0000) >> 16;
	if (Memory::store(req_address+2, write_value) == 1) return 1;
	write_value = (reg_value & 0xFF00) >> 8;
	if (Memory::store(req_address+1, write_value) == 1) return 1;
	write_value = reg_value & 0xFF;
	return Memory::store(req_address, write_value);
}

void Memory::debug_dump_range(uint32_t front, uint32_t back) const{
	for (uint32_t i = front; i < back; i++){
		uint8_t next = Memory::load(i);
		printf("MEM[%x] = [%02X]\n", i, next);
	}
}

