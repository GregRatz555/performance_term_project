#include <iostream>
#include "VM.h"
#include "ALU.h"
#include "Memory.h"

int main(int argc, char *argv[]) {
  if(argc != 2) {
    printf("Invalid number of parameters:\n\t%s <bin to run>\n", argv[0]);
    return -1;
  }

  VM rv32i;
  rv32i.load_elf(argv[1]);
  rv32i.dump_mem(0,12);
  rv32i.run();
  return 0;
}
