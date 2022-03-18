mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../riscv-toolchain.cmake
make

# To build container
podman build -f Dockerfile-run -t riscv64-cmake

# To run container
Compiler is found in /riscv64-unknown-elf-toolchain-\*

Current working directory directory is mapped into /shared

```
podman run --security-opt label=disable -it -v=$(pwd):/shared riscv64-cmake

podman push --creds=beaverb1ll:${GITHUB_PAT} riscv64-cmake ghcr.io/GregRatz555/riscv64-cmake:latest
