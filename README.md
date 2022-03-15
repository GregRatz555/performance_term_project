```
add x5,x5,x4
mv a0,a5
````


Toolchain: [[https://github.com/sifive/freedom-tools/releases/tag/v2020.12.0]]


How to get raw instructions


./riscv64-unknown-elf-g++ -c -march=rv32i -mabi=ilp32 main.S


./riscv64-unknown-elf-objdump -D -s ./main.o
