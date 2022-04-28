cmake_minimum_required(VERSION 3.2)
project(riscv-simulator CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type specified. Defaulting to RELWITHDEBINFO")
  set(CMAKE_BUILD_TYPE RELWITHDEBINFO CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel ..." FORCE)
endif()

add_compile_options(-Wall)

enable_testing()
find_package(GTest REQUIRED)

add_library(riscv-cpu
  VM.cpp
  Decode.cpp
  ALU.cpp
  Memory.cpp
  Registers.cpp
)

add_executable(rv_simulator main.cpp)
target_link_libraries(rv_simulator riscv-cpu)

add_executable(tests tests.cpp)
target_link_libraries(tests riscv-cpu GTest::gtest GTest::gtest_main)
