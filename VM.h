/* 
 * Virtual Machine Class
 * Holds registers , machine state
 */

#ifndef __VM_H__
#define __VM_H__

#include <atomic>
#include <cstdint>

#include "ALU.h"
#include "Memory.h"
#include "Registers.h"

class VM {
  Memory mem_{64*1024};
  Registers regs_;
  ALU alu_;
  std::atomic<bool> keep_running_{true};

  public:
    VM();
    bool execute(const uint32_t raw_instruction);
    bool run();
    bool run(uint32_t instruction_count);
    void dump();
    void dump_mem(uint32_t front, uint32_t back);
    void load_elf(const char *filename);
};

#endif
