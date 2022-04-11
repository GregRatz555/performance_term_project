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
  kNumInstructionFormats,
  // Compressed formats
  kCRInstructionFormat,
  kCIInstructionFormat,
  kCSSInstructionFormat,
  kCIWInstructionFormat,
  kCLInstructionFormat,
  kCSInstructionFormat,
  kCBInstructionFormat,
  kCJInstructionFormat
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
  // Multiply Extension
  kMultiplyInstruction,
  kMultiplyHighInstruction,
  kMultiplyHighSUInstruction,
  kMultiplyHighUInstruction,
  kDivideInstruction,
  kDivideUInstruction,
  kRemainderInstruction,
  kRemainderUInstruction,
  // Compressed Extension
  kcLoadWordFromSPInstruction,
  kcStoreWordToSPInstruction,
  kcLoadWordInstruction,
  kcStoreWordInstruction,
  kcJumpInstruction,
  kcJumpAndLinkInstruction,
  kcJumpRegInstruction,
  kcJumpAndLinkRegInstruction,
  kcBranchZeroInstruction,
  kcBranchNotZeroInstruction,
  kcLoadImmediateInstruction,
  kcLoadUpperImmediateInstruction,
  kcAddImmediateInstruction,
  kcAdd16xImmediateToSPInstruction,
  kcAdd4xImmediateToSPInstruction,
  kcShiftLeftLogicalImmediateInstruction,
  kcShiftRightLogicalImmediateInstruction,
  kcShiftRightArithmeticImmediateInstruction,
  kcANDImmediateInstruction,
  kcMoveInstruction,
  kcADDInstruction,
  kcANDInstruction,
  kcORInstruction,
  kcXORInstruction,
  kcSUBInstruction,
  kcNOPInstruction,
  kcEnvironmentBreakInstruction
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
    kNumRegisters
  };

  InstructionType decode(const uint32_t raw_instruction);

  RegisterType decode_rd(const uint32_t raw_instruction);
  RegisterType decode_rs1(const uint32_t raw_instruction);
  RegisterType decode_rs2(const uint32_t raw_instruction);

  int32_t decode_I_imm(const uint32_t raw_instruction);
  int32_t decode_S_imm(const uint32_t raw_instruction);
  int32_t decode_B_imm(const uint32_t raw_instruction);
  int32_t decode_U_imm(const uint32_t raw_instruction);
  int32_t decode_J_imm(const uint32_t raw_instruction);
  // Compressed Extension
  uint8_t decode_CI_rd(const uint32_t raw_instruction);
  int32_t decode_CI_imm(const uint32_t raw_instruction);
  int32_t decode_CLWSP_imm(const uint32_t raw_instruction);
  int32_t decode_CADDI16SP_imm(const uint32_t raw_instruction);
  uint8_t decode_CSS_rs2(const uint32_t raw_instruction);
  int32_t decode_CSS_imm(const uint32_t raw_instruction);
  int32_t decode_CIW_imm(const uint32_t raw_instruction);
  uint8_t decode_CL_rd(const uint32_t raw_instruction);
  uint8_t decode_CL_rs1(const uint32_t raw_instruction);
  int32_t decode_CL_imm(const uint32_t raw_instruction);
  uint8_t decode_CS_rs1(const uint32_t raw_instruction);
  uint8_t decode_CS_rs2(const uint32_t raw_instruction);
  int32_t decode_CS_imm(const uint32_t raw_instruction);
  uint8_t decode_CB_rs1(const uint32_t raw_instruction);
  int32_t decode_CB_imm(const uint32_t raw_instruction);
  int32_t decode_CJ_offset(const uint32_t raw_instruction);
  uint8_t decode_CR_rs1(const uint32_t raw_instruction);
  uint8_t decode_CR_rs2(const uint32_t raw_instruction);
  uint8_t decode_CA_rs1(const uint32_t raw_instruction);
  uint8_t decode_CA_rs2(const uint32_t raw_instruction);

  uint8_t decode_opcode(const uint32_t raw_instruction);
  uint8_t decode_R_func7(const uint32_t raw_instruction);
  uint8_t decode_func3(const uint32_t raw_instruction);
  uint8_t decode_compressed_funct3(const uint32_t raw_instruction);
  uint8_t decode_compressed_funct4(const uint32_t raw_instruction);
  uint8_t decode_compressed_funct6(const uint32_t raw_instruction);
  uint8_t decode_compressed_cr_rs1(const uint32_t raw_instruction);
  uint8_t decode_compressed_cr_rs2(const uint32_t raw_instruction);
  uint8_t decode_compressed_cb_type(const uint32_t raw_instruction);
  uint8_t decode_compressed_op3_type(const uint32_t raw_instruction);
  uint8_t decode_compressed_opcode(const uint32_t raw_instruction);

  InstructionType decode_compressed(const uint32_t raw_instruction);
  InstructionType decode_compressed_cr(const uint32_t raw_instruction);
  InstructionType decode_arithmetic_R(const uint32_t raw_instruction);
  InstructionType decode_arithmetic_I(const uint32_t raw_instruction);
  InstructionType decode_load_I(const uint32_t raw_instruction);
  InstructionType decode_store_S(const uint32_t raw_instruction);
  InstructionType decode_branch_B(const uint32_t raw_instruction);
  InstructionType decode_environment_I(const uint32_t raw_instruction);

  int32_t sign_extend(const uint32_t orig_num, const uint8_t num_bits_in_orig_num);
};

#endif
