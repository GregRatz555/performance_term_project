#include "ALU.h"
#include <iostream>
ALU::ALU(){std::cout << "ALU CREATED" << std::endl;}

// R-Type Instructions
void ALU::ADD(VM& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2) {
	mstate.set_reg(rd, mstate.get_reg(rs1) + mstate.get_reg(rs2)); 
}
void ALU::SUB(VM& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2) {
	mstate.set_reg(rd, mstate.get_reg(rs1) - mstate.get_reg(rs2)); 
}
void ALU::OR (VM& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2) {
	mstate.set_reg(rd, mstate.get_reg(rs1) | mstate.get_reg(rs2)); 
}
void ALU::XOR(VM& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2) {
	mstate.set_reg(rd, mstate.get_reg(rs1) ^ mstate.get_reg(rs2));
}
