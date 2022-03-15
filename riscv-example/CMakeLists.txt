cmake_minimum_required(VERSION 3.2)
project(riscv-example CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-march=rv32i -mabi=ilp32)

add_executable(rv_code main.cpp)
set_target_properties(rv_code PROPERTIES LINK_FLAGS "-march=rv32i -mabi=ilp32 -T${CMAKE_CURRENT_SOURCE_DIR}/microsemi-riscv.ld -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/rv_code.map")

add_custom_command(TARGET rv_code POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O binary rv_code rv_code.bin
        COMMENT "Invoking: Hexdump")
