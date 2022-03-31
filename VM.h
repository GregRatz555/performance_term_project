/* 
 * Virtual Machine Class
 * Holds registers , machine state
 */

#ifndef __VM_H__
#define __VM_H__
#include <cstdint>


class VM {
	uint32_t reg[32];	// Register 
	uint32_t pc;	// program counter
	public:
		VM();
		void init_registers();
		uint8_t set_reg(uint8_t rd, uint32_t value);
		uint32_t get_reg(uint8_t rd);
		void dump_reg();
};

#endif
