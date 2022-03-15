#ifndef __DECODE_HPP_
#define __DECODE_HPP_

#include <cstdint>

namespace Decode {
  enum InstructionFormat {
  kRInstructionFormat = 0,
  kIInstructionFormat,
  kSInstructionFormat,
  kBInstructionFormat,
  kUInstructionFormat,
  kJInstructionFormat,
  kNumInstructionFormats
  };

  enum InstructionType {
  kInvalidInstruction = 0,
  kAddInstruction,
  kSubInstruction,
  kXorInstruction,
  kOrInstruction,
  kAndInstruction,
  kShiftLeftLogicalInstruction,
  kShiftRightLogicalInstruction,
  kShiftRightArithmeticInstruction,
  kSetLessThanInstruction,
  kSetLessThanUInstruction,
  kAddImmediateInstruction,
  kXorImmediateInstruction,
  kOrImmediateInstruction,
  kAndImmediateInstruction,
  kShiftLeftLogicalImmInstruction,
  kShiftRightLogicalImmInstruction,
  kShiftRightArithmeticImmInstruction,
  kSetLessThanImmInstruction,
  kSetLessThanUImmInstruction,
  kLoadByteInstruction,
  kLoadHalfInstruction,
  kLoadWordInstruction,
  kLoadByteUInstruction,
  kLoadHalfUInstruction,
  kStoreByteInstruction,
  kStoreHalfInstruction,
  kStoreWordInstruction,
  kBranchEqualInstruction,
  kBranchNotEqualInstruction,
  kBranchLessThanInstruction,
  kBranchGreaterThanEqualInstruction,
  kBranchLessThanUInstruction,
  kBranchGreaterThanEqualUInstruction,
  kJumpAndLinkInstruction,
  kJumpAndLinkRegInstruction,
  kLoadUpperImmInstruction,
  kAddUpperImmToPCInstruction,
  kEnvironmentCallInstruction,
  kEnvironmentBreakInstruction,
  };

  enum RegisterType {
    kRegister0 = 0,
    kRegister1,
    kRegister2,
    kRegister3,
    kRegister4,
    kRegister5,
    kRegister6,
    kRegister7,
    kRegister8,
    kRegister9,
    kRegister10,
    kRegister11,
    kRegister12,
    kRegister13,
    kRegister14,
    kRegister15,
    kRegister16,
    kRegister17,
    kRegister18,
    kRegister19,
    kRegister20,
    kRegister21,
    kRegister22,
    kRegister23,
    kRegister24,
    kRegister25,
    kRegister26,
    kRegister27,
    kRegister28,
    kRegister29,
    kRegister30,
    kRegister31,
    kRegister32,
    kNumRegisters
  };

  InstructionType decode(const uint32_t raw_instruction);

  RegisterType decode_rd(const uint32_t raw_instruction);
  RegisterType decode_rs1(const uint32_t raw_instruction);
  RegisterType decode_rs2(const uint32_t raw_instruction);

  uint16_t decode_I_imm(const uint32_t raw_instruction);
  uint16_t decode_S_imm(const uint32_t raw_instruction);

  uint8_t decode_opcode(const uint32_t raw_instruction);
  uint8_t decode_R_func7(const uint32_t raw_instruction);
  uint8_t decode_func3(const uint32_t raw_instruction);

  InstructionType decode_arithmetic_R(const uint32_t raw_instruction);
  InstructionType decode_arithmetic_I(const uint32_t raw_instruction);
  InstructionType decode_load_I(const uint32_t raw_instruction);
  InstructionType decode_store_S(const uint32_t raw_instruction);
  InstructionType decode_branch_B(const uint32_t raw_instruction);
  InstructionType decode_environment_I(const uint32_t raw_instruction);
};

#endif
