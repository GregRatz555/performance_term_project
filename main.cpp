#include <iostream>
#include <chrono>
#include "VM.h"
#include "ALU.h"
#include "Memory.h"

int main(int argc, char *argv[]) {
  if(argc < 2) {
    printf("Invalid number of parameters:\n\t%s <bin to run>\n", argv[0]);
    return -1;
  }
  const bool should_dump = (argc == 3);
  printf("Num ticks: %ld/%ld\n", std::chrono::high_resolution_clock::period::num, std::chrono::high_resolution_clock::period::den);

  VM rv32i(64*1024);
  rv32i.load_elf(argv[1]);
  rv32i.run(should_dump);
  return 0;
}
