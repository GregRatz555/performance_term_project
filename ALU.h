/*
 * ALU class
 * Handles Instruction 
 */

#ifndef __ALU__
#define __ALU__

#include <cstdint>

#include "Registers.h"

class ALU {
  public:
    // R-type functions
    ALU();
    void ADD(Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
    void SUB(Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
    void OR (Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
    void XOR(Registers& mstate, uint8_t rd, uint8_t rs1, uint8_t rs2);
};

#endif
