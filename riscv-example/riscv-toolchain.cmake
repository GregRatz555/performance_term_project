#set(TOOLCHAIN_PATH /home/user/Downloads/riscv64-unknown-elf-toolchain-10.2.0-2020.12.8-x86_64-linux-centos6)
set(TOOLCHAIN_PATH /home/user/git/freedom-tools/obj/x86_64-linux-centos6/build/riscv64-unknown-elf-gcc/install-gcc)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR riscv)
set(CMAKE_SYSROOT ${TOOLCHAIN_PATH}/riscv64-unknown-elf/)

set(CMAKE_C_COMPILER ${TOOLCHAIN_PATH}/bin/riscv64-unknown-elf-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}/bin/riscv64-unknown-elf-g++)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

