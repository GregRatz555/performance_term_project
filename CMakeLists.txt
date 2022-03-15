cmake_minimum_required(VERSION 3.2)
project(riscv-simulator CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 14)

add_library(riscv-cpu
  VM.cpp
  Decode.cpp
  ALU.cpp
  Memory.cpp
  Registers.cpp
)

add_executable(rv_simulator main.cpp)
target_link_libraries(rv_simulator riscv-cpu)
