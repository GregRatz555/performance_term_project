#!/bin/bash

riscv64-unknown-elf-objdump -D -S $1 > $2
