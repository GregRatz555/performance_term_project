/* 
 * Virtual Machine Class
 * Holds registers , machine state
 */

#ifndef __VM_H__
#define __VM_H__

#include <atomic>
#include <cstdint>
#include <string>

#include "ALU.h"
#include "Memory.h"
#include "Registers.h"

class VM {
  Memory mem_;
  Registers regs_;
  ALU alu_;
  std::atomic<bool> keep_running_{true};

  public:
    VM(const size_t mem_size);
    bool execute(const uint32_t raw_instruction);
    bool run();
    bool run(uint32_t instruction_count);
    void dump() const ;
    void dump_mem(uint32_t front, uint32_t back) const;
    void load_elf(const std::string &filename);
    const RegisterValues& get_regs() const;
    void set_regs(const RegisterValues &new_regs);
};

#endif
