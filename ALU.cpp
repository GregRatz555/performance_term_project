#include "ALU.h"

#include <iostream>

ALU::ALU(){
  std::cout << "ALU CREATED" << std::endl;
}

// R-Type Instructions
void ALU::ADD(Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  printf("%d = %d + %d\n", rd, rs1, rs2);
  mstate.set(rd, mstate.get(rs1) + mstate.get(rs2));
}

void ALU::SUB(Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  mstate.set(rd, mstate.get(rs1) - mstate.get(rs2));
}

void ALU::OR (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  mstate.set(rd, mstate.get(rs1) | mstate.get(rs2));
}

void ALU::XOR(Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  mstate.set(rd, mstate.get(rs1) ^ mstate.get(rs2));
}
