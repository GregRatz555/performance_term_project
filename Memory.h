/*
 * Memory Class
 * Memory management and IO
 */

#ifndef __MEM__
#define __MEM__
#include <cstdint>
#include <cstring>
#include "Registers.h"

class Memory {
  public:
    Memory(const std::size_t memsize);
    uint8_t init(uint32_t memsize);
    uint32_t size;                      // Bytes available to address
    uint32_t addr_range[2];                 // First and last addresses
    void debug_dump_range(uint32_t front, uint32_t back) const; // To check memory methods
    int8_t load_byte(Registers& mstate, uint8_t rd, uint8_t rs1, int32_t imm);  // lb
    int8_t load_half(Registers& mstate, uint8_t rd, uint8_t rs1, int32_t imm);  // lh
    int8_t load_word(Registers& mstate, uint8_t rd, uint8_t rs1, int32_t imm);  // l2
    int8_t load_u_byte(Registers& mstate, uint8_t rd, uint8_t rs1, int32_t imm);  // lbu
    int8_t load_u_half(Registers& mstate, uint8_t rd, uint8_t rs1, int32_t imm);  // lhu
    int8_t store_byte(Registers& mstate, uint8_t rs1, uint8_t rs2, int32_t imm); // lb
    int8_t store_half(Registers& mstate, uint8_t rs1, uint8_t rs2, int32_t imm); // lh
    int8_t store_word(Registers& mstate, uint8_t rs1, uint8_t rs2, int32_t imm); // l2

    // Return to Private
    uint8_t load(uint32_t req_address) const;         // Basic load an address
    uint8_t store(uint32_t req_address, uint8_t value);   // Basic byte store an address

    template <typename T>
    T read_data(const uint32_t req_address)
    {
      uint32_t offset = req_address/sizeof(T);
      return reinterpret_cast<T*>(storage)[offset];
    }

    template <typename T>
    void write_data(const uint32_t req_address, const T value)
    {
      const uint32_t offset = req_address/sizeof(T);
      reinterpret_cast<T*>(storage)[offset] = value;
    }

    inline bool operator==(const Memory& lhs) const
    {
      return (lhs.size == size) && (0 == std::memcmp(lhs.storage, storage, size));
    }

    uint8_t check_address(uint32_t address) const;      // Check if valid
    uint32_t read_clock();

  private:
    uint8_t *storage;                   // Array of storage
    //uint8_t check_address(uint32_t address);        // Check if valid
    //uint8_t load(uint32_t req_address);           // Basic load an address
    //uint8_t store(uint32_t req_address, uint8_t value);   // Basic byte store an address
};

#endif
