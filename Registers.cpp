#include "Registers.h"

#include <iostream>

Registers::Registers()
{
}

uint32_t Registers::get_pc() const
{
  return regs_.pc;
}

void Registers::set_pc(const uint32_t value)
{
  regs_.pc = value;
}

uint8_t Registers::set(const uint8_t rd, const uint32_t value)
{
  // Safe way of setting registers
  // Register 0 must be 0, it is always 0
  // Returns success state
  // Could be replaced in decode step
  if (rd > 31){
    throw std::runtime_error("set: Nonexistant register referenced "
        "At pc: " + std::to_string(regs_.pc));
  }
  if (rd != 0) {
    regs_.regs[rd] = value;
  }
  return 0;
}

uint32_t Registers::get(const uint8_t rd) const
{
  // Safe way of getting register values
  // Register 0 must be 0, it is always 0
  // returns register value
  if (rd > 31) {
    throw std::runtime_error("get: Nonexistant register referenced "
        "At pc: " + std::to_string(regs_.pc));
  }
  if (rd == 0) return 0;
  return regs_.regs[rd];
}

void Registers::dump() const
{
  if(regs_.pc == 0) {
    printf("********************************************************************\n");
  }
  // Prints all register states
  printf("REG[PC] = 0x%x\n", regs_.pc);
  if(regs_.pc > 0x69a0 && regs_.pc < 0x6a38) {
  for (int r=0; r<32; r++) {
    printf("REG[%02d] = 0x%x\n", r, regs_.regs[r]);
  }
  printf("\n");
  }
}

const RegisterValues& Registers::get_values() const
{
  return regs_;
}

void Registers::set_values(const RegisterValues &new_values)
{
  regs_ = new_values;
}
