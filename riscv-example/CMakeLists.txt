cmake_minimum_required(VERSION 3.2)
project(riscv-example CXX C ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-march=rv32i -mabi=ilp32)

macro(create_rv_exe exe_name exe_src)
  add_executable(${exe_name} ${exe_src})
  set_target_properties(${exe_name} PROPERTIES LINK_FLAGS "-march=rv32i -mabi=ilp32 -T${CMAKE_CURRENT_SOURCE_DIR}/microsemi-riscv.ld -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/${exe_name}.map")

  add_custom_command(TARGET ${exe_name} POST_BUILD
	  COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_CURRENT_BINARY_DIR}/${exe_name} ${CMAKE_CURRENT_BINARY_DIR}/${exe_name}.bin
        COMMENT "Invoking: Objcopy ${exe_name}")
endmacro()


create_rv_exe(rv_code main.cpp)

create_rv_exe(rv_fib main.fib.S)
target_compile_options(rv_fib PRIVATE -nostdlib)
target_link_options(rv_fib PRIVATE -nostdlib)
