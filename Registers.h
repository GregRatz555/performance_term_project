#ifndef REGISTERS_H_
#define REGISTERS_H_

#include <array>
#include <cstdint>

class Registers {

 public:
  Registers();
  uint32_t get_pc() const;
  void set_pc(const uint32_t value);

  uint8_t set(const uint8_t rd, uint32_t value);
  uint32_t get(const uint8_t rd) const;
  void dump() const;

 private:
  std::array<uint32_t, 32> regs_; // Register
  uint32_t pc_ = 0;
};
#endif
