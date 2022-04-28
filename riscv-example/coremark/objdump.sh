#!/bin/bash

riscv64-unknown-elf-objdump -D -s $1 > $2
