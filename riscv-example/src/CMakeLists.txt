create_rv_exe(rv_code main.cpp)

create_rv_exe(rv_fib main.fib.S)
target_compile_options(rv_fib PRIVATE -nostdlib)
target_link_options(rv_fib PRIVATE -nostdlib)
