#include "Registers.h"

#include <iostream>

Registers::Registers()
{
  regs_.fill(0);
}

uint32_t Registers::get_pc() const
{
  return pc_;
}

void Registers::set_pc(const uint32_t value)
{
  pc_ = value;
}

uint8_t Registers::set(const uint8_t rd, const uint32_t value)
{
  // Safe way of setting registers
  // Register 0 must be 0, it is always 0
  // Returns success state
  // Could be replaced in decode step
  if (rd > 31){
    std::cerr << "Nonexistant register referenced";
    std::cerr << "At pc = " << pc_;
    return 1;
  }
  if (rd != 0) {
    printf("Set Reg %d: %d\n", rd, value);
    regs_[rd] = value;
  }
  return 0;
}

uint32_t Registers::get(const uint8_t rd) const
{
  // Safe way of getting register values
  // Register 0 must be 0, it is always 0
  // returns register value
  if (rd > 31) {
    std::cerr << "Fatal: Nonexistant register referenced";
    std::cerr << "At pc = " << pc_;
    exit(1); // TODO get better error system
  }
  printf("Get reg %d: %d\n", rd, regs_[rd]);
  if (rd == 0) return 0;
  return regs_[rd];
}

void Registers::dump() const
{
  // Prints all register states
  printf("REG[PC] = %d\n", pc_);
  for (int r=0; r<32; r++) {
    printf("REG[%02d] = %d\n", r, regs_[r]);
  }
}
