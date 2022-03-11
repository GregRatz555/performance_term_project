/*
 * Memory Class
 * Memory management and IO
 */

#ifndef __MEM__
#define __MEM__
#include <cstdint>
#include "VM.h"

class Memory {
	public:
		Memory();
		uint8_t init(uint32_t memsize);
		uint32_t size; 											// Bytes available to address
		uint32_t addr_range[2];									// First and last addresses
		void debug_dump_range(uint32_t front, uint32_t back);	// To check memory methods
		int8_t load_byte(VM& mstate, uint8_t rd, uint8_t rs1, int8_t imm);		// lb
		int8_t load_half(VM& mstate, uint8_t rd, uint8_t rs1, int8_t imm);		// lh
		int8_t load_word(VM& mstate, uint8_t rd, uint8_t rs1, int8_t imm);		// l2
		int8_t load_u_byte(VM& mstate, uint8_t rd, uint8_t rs1, int8_t imm);	// lbu
		int8_t load_u_half(VM& mstate, uint8_t rd, uint8_t rs1, int8_t imm);	// lhu
		int8_t store_byte(VM& mstate, uint8_t rs1, uint8_t rs2, int8_t imm);	// lb
		int8_t store_half(VM& mstate, uint8_t rs1, uint8_t rs2, int8_t imm);	// lh
		int8_t store_word(VM& mstate, uint8_t rs1, uint8_t rs2, int8_t imm);	// l2
		// Return to Private
		uint8_t load(uint32_t req_address);						// Basic load an address
		uint8_t store(uint32_t req_address, uint8_t value);		// Basic byte store an address
		uint8_t check_address(uint32_t address);				// Check if valid
	private:
		uint8_t *storage;										// Array of storage
		//uint8_t check_address(uint32_t address);				// Check if valid
		//uint8_t load(uint32_t req_address);						// Basic load an address
		//uint8_t store(uint32_t req_address, uint8_t value);		// Basic byte store an address
};

#endif
