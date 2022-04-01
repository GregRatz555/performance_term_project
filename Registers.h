#ifndef REGISTERS_H_
#define REGISTERS_H_

#include <array>
#include <cstdint>

#include "Decode.h"

struct RegisterValues
{
  std::array<uint32_t, Decode::kNumRegisters> regs; // Register
  uint32_t pc = 0;

  RegisterValues()
  {
    regs.fill(0);
  }

  inline bool operator==(const RegisterValues& lhs) const
  {
    return pc == lhs.pc &&
      regs == lhs.regs;
  }

  inline bool operator!=(const RegisterValues& lhs) const { return !(lhs == *this); }
};

class Registers {

 public:
  Registers();
  uint32_t get_pc() const;
  void set_pc(const uint32_t value);

  uint8_t set(const uint8_t rd, uint32_t value);
  uint32_t get(const uint8_t rd) const;
  void dump() const;
  const RegisterValues& get_values() const;
  void set_values(const RegisterValues &new_values);

 private:
  RegisterValues regs_;
};
#endif
