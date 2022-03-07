#ifndef __VM_H__
#define __VM_H__
#endif

class VM {
	uint32_t reg[32];	// Register 
	uint32_t pc;	// program counter
	public:
		VM();
		void init_registers();
};

