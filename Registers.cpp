#include "Registers.h"

#include <iostream>

Registers::Registers()
{
  regs_.regs.fill(0);
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
  // Prints all register states
  printf("REG[PC] = %d\n", regs_.pc);
  for (int r=0; r<32; r++) {
    printf("REG[%02d] = %d\n", r, regs_.regs[r]);
  }
}

const RegisterValues& Registers::get_values() const
{
  return regs_;
}
