cmake_minimum_required(VERSION 3.2)
project(riscv-coremark CXX C ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type specified. Defaulting to RELWITHDEBINFO")
  set(CMAKE_BUILD_TYPE RELWITHDEBINFO CACHE STRING "Choose the type of build, options are: None Debug Releas    e RelWithDebInfo MinSizeRel ..." FORCE)
endif()

add_compile_options(-march=rv32i -mabi=ilp32)

set(exe_name riscv-coremark-sim)
add_executable(${exe_name} entry.S core_list_join.c  core_main.c  core_matrix.c  core_portme.c  core_state.c  core_util.c  cvt.c  ee_printf.c)
set_target_properties(${exe_name} PROPERTIES LINK_FLAGS "-march=rv32i -mabi=ilp32 -T${CMAKE_SOURCE_DIR}/../microsemi-riscv.ld -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/${exe_name}.map")
target_include_directories(${exe_name} PUBLIC ${CMAKE_SOURCE_DIR})

add_custom_command(TARGET ${exe_name} POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_CURRENT_BINARY_DIR}/${exe_name} ${CMAKE_CURRENT_BINARY_DIR}/${exe_name}.objcopy.bin
      COMMENT "Invoking: Objcopy ${exe_name}")
