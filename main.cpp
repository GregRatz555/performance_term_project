#include <iostream>
#include "VM.h"
#include "ALU.h"
#include "Memory.h"

int main() {
	// Attempt to create machine state
	std::cout << "Creating Machine!\n";
	// This section creates the parts of the VM, should probably be moved into VM.h
	VM  rv32i;
	ALU exec;
	Memory main_mem;
	std::cout << "Create Machine Successful!\n";
	rv32i.set_reg(2, 16);
	rv32i.set_reg(3, 32);
	exec.ADD(rv32i, 1, 2, 3);
	rv32i.dump_reg();
	main_mem.init(4096); // Test making a 4k mem block
	std::cout << "storage size  " << main_mem.size << std::endl;
	std::cout << "range  " << main_mem.addr_range[0] << " to " << main_mem.addr_range[1] << std::endl;

	main_mem.store(0x10, 0xFF);
	main_mem.store(0x11, 0xAA);
	main_mem.store(0x12, 0xBA);
	main_mem.store(0x13, 0xD0);
	main_mem.debug_dump_range(0,0x15);
	// Each load type works
	main_mem.load_byte(rv32i, 1, 0, 0x10);
	main_mem.load_u_byte(rv32i, 2, 0, 0x11);
	main_mem.load_half(rv32i, 3, 0, 0x10);
	main_mem.load_word(rv32i, 4, 0, 0x10);
	// offset from register value also works
	rv32i.set_reg(1, 0x11);
	main_mem.load_byte(rv32i, 6, 1, 0x00);
	main_mem.load_byte(rv32i, 7, 1, -1);
	rv32i.dump_reg();
	// store parts of 0xffaabad0 at 32(byte) 34-35(half) 37-40(word)
	rv32i.set_reg(2, 32);
	main_mem.store_byte(rv32i, 2, 4, 0);
	main_mem.store_half(rv32i, 2, 4, 2);
	main_mem.store_word(rv32i, 2, 4, 5);
	main_mem.debug_dump_range(30, 45);
	
	return 0;
}
