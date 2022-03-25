cmake_minimum_required(VERSION 3.2)
project(riscv-simulator CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 14)

enable_testing()
find_package(GTest)

add_library(riscv-cpu
  VM.cpp
  Decode.cpp
  ALU.cpp
  Memory.cpp
  Registers.cpp
)

add_executable(rv_simulator main.cpp)
target_link_libraries(rv_simulator riscv-cpu)

if(GTest_FOUND)
  add_executable(tests tests.cpp)
  target_link_libraries(tests riscv-cpu GTest::gtest GTest::gtest_main)
endif()
