#include "Memory.h"
#include <iostream>
#include <cstdint>

Memory::Memory(){
		Memory::storage = 0;
		Memory::addr_range[0] = 0x0000;
		Memory::addr_range[1] = 0x0000;
		Memory::size = 0;
}

uint8_t Memory::init(uint32_t memsize){
	// Try to create a sector of memory with the given size,
	// Return success of operation
	if (Memory::storage != 0) {
		// Avoid memleak and use-after-free
		// If for some reason a memory is re-init'ed, lose the old
		std::cout << "Memory re-init. Core dumped." << std::endl;
		free(Memory::storage);
		Memory::storage = 0;
	}
	// Create an empty memory block
	Memory::storage = (uint8_t*)calloc(memsize, sizeof(uint8_t));
	if (Memory::storage == NULL) {
		// In case of failure, reset attributes
		std::cout << "Storage Init failed!";
		Memory::addr_range[0] = 0x0000;
		Memory::addr_range[1] = 0x0000;
		Memory::size = 0;
		return 1;
	} else {
		// Else update attributes
		std::cout << "Storage Init Success!";
		Memory::addr_range[0] = 0x0000;
		Memory::addr_range[1] = 0x0000 + memsize;
		Memory::size = memsize;
		return 0;
	}
}

uint8_t Memory::check_address(uint32_t address){
	return ((address >= addr_range[0]) && (address < addr_range[1])) ? 0 : 1;
}

uint8_t Memory::load(uint32_t req_address){
	if (Memory::check_address(req_address) == 0) {
		return Memory::storage[req_address];
	} else {
		std::cerr << "Fatal: load fail at addr=" << req_address << std::endl;
		exit(1);
	}
}

uint8_t Memory::store(uint32_t req_address, uint8_t value){
	if(Memory::check_address(req_address) == 0){
		Memory::storage[req_address] = value;
		return 0;
	}
	return 1;
}

int8_t Memory::load_byte(VM& mstate, uint8_t rd, uint8_t rs1, int8_t imm){
	uint32_t base = mstate.get_reg(rs1);
	uint32_t req_address = base + imm;
	uint32_t result = Memory::load(req_address);
	return mstate.set_reg(rd, result);
}

int8_t Memory::load_half(VM& mstate, uint8_t rd, uint8_t rs1, int8_t imm){
	uint32_t base = mstate.get_reg(rs1);
	uint32_t req_address = base + imm;
	uint32_t result = Memory::load(req_address);
	result = result << 8;
	result |= Memory::load(req_address+1);
	return mstate.set_reg(rd, result);
}

int8_t Memory::load_u_byte(VM& mstate, uint8_t rd, uint8_t rs1, int8_t imm){
	// NOTE: I see no reason for this to vary from the "signed" version
	return Memory::load_byte(mstate, rd, rs1, imm);
}

int8_t Memory::load_u_half(VM& mstate, uint8_t rd, uint8_t rs1, int8_t imm){
	return Memory::load_half(mstate, rd, rs1, imm);
}

int8_t Memory::load_word(VM& mstate, uint8_t rd, uint8_t rs1, int8_t imm){
	uint32_t base = mstate.get_reg(rs1);
	uint32_t req_address = base + imm;
	uint32_t result = (Memory::load(req_address) << 24);
	result |= (Memory::load(req_address+1) << 16);
	result |= (Memory::load(req_address+2) << 8);
	result |= Memory::load(req_address+3);
	return mstate.set_reg(rd, result);
}

int8_t Memory::store_byte(VM& mstate, uint8_t rs1, uint8_t rs2, int8_t imm){
	uint32_t base = mstate.get_reg(rs1);
	uint32_t req_address = base + imm;
	uint8_t  write_value = (mstate.get_reg(rs2) & 0xFF);
	return Memory::store(req_address, write_value);
}

int8_t Memory::store_half(VM& mstate, uint8_t rs1, uint8_t rs2, int8_t imm){
	uint32_t base = mstate.get_reg(rs1);
	uint32_t req_address = base + imm;
	uint32_t reg_value = mstate.get_reg(rs2);
	uint8_t write_value = (reg_value & 0xFF00) >> 8;
	if (Memory::store(req_address, write_value) == 1) return 1;
	write_value = reg_value & 0xFF;
	return Memory::store(req_address+1, write_value);
}

int8_t Memory::store_word(VM& mstate, uint8_t rs1, uint8_t rs2, int8_t imm){
	uint32_t base = mstate.get_reg(rs1);
	uint32_t req_address = base + imm;
	uint32_t reg_value = mstate.get_reg(rs2);
	uint8_t write_value = (reg_value & 0xFF000000) >> 24;
	if (Memory::store(req_address, write_value) == 1) return 1;
	write_value = (reg_value & 0xFF0000) >> 16;
	if (Memory::store(req_address+1, write_value) == 1) return 1;
	write_value = (reg_value & 0xFF00) >> 8;
	if (Memory::store(req_address+2, write_value) == 1) return 1;
	write_value = reg_value & 0xFF;
	return Memory::store(req_address+3, write_value);
}

void Memory::debug_dump_range(uint32_t front, uint32_t back){
	for (uint32_t i = front; i < back; i++){
		uint8_t next = Memory::load(i);
		printf("MEM[%u] = [%u]\n", i, next);
	}
}

