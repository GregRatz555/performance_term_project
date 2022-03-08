#include "CPU.h"
CPU::CPU(){std::cout << "CPU CREATED" << std::endl;}

// R-Type Instructions
void CPU::INSR_ADD(VM* mstate, uint8_t rd, uint8_t rs1, uint8_t rs2) {
	mstate->set_reg(rd, mstate->get_reg(rs1) + mstate->get_reg(rs2)); 
}
void CPU::INSR_SUB(VM* mstate, uint8_t rd, uint8_t rs1, uint8_t rs2) {
	mstate->set_reg(rd, mstate->get_reg(rs1) - mstate->get_reg(rs2)); 
}
void CPU::INSR_OR (VM* mstate, uint8_t rd, uint8_t rs1, uint8_t rs2) {
	mstate->set_reg(rd, mstate->get_reg(rs1) | mstate->get_reg(rs2)); 
}
void CPU::INSR_XOR(VM* mstate, uint8_t rd, uint8_t rs1, uint8_t rs2) {
	mstate->set_reg(rd, mstate->get_reg(rs1) ^ mstate->get_reg(rs2));
}
