#include <iostream>
#include "VM.h"
#include "ALU.h"
#include "Memory.h"

int main() {
  VM rv32i;
  rv32i.load_elf("main.o");
  rv32i.dump_mem(0,9);
  rv32i.run(2);
  return 0;
}
