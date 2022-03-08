#include <iostream>
#include "VM.cpp"
#include "CPU.cpp"

int main() {
	// Attempt to create machine state
	std::cout << "Creating Machine!\n";
	VM rv32i;
	CPU exec;
	std::cout << "Create Machine Successful!\n";
	rv32i.set_reg(2, 16);
	rv32i.set_reg(3, 32);
	exec.INSR_ADD(&rv32i, 1, 2, 3);
	rv32i.dump_reg();
	return 0;
}
