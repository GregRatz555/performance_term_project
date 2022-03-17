#include "Decode.h"

#include <cassert>

namespace Decode {

InstructionType decode(const uint32_t raw_instruction)
{
  const uint8_t opcode = decode_opcode(raw_instruction);
  switch(opcode) {
  case 0b0110011:
    return decode_arithmetic_R(raw_instruction);
    break;
  case 0b0010011:
    return decode_arithmetic_I(raw_instruction);
  case 0b0000011:
    return decode_load_I(raw_instruction);
    break;
  case 0b0100011:
    return decode_store_S(raw_instruction);
    break;
  case 0b1100011:
    return decode_branch_B(raw_instruction);
    break;
  case 0b1101111:
    return kJumpAndLinkInstruction;
    break;
  case 0b1100111:
    return kJumpAndLinkRegInstruction;
    break;
  case 0b0110111:
    return kLoadUpperImmInstruction;
    break;
  case 0b0010111:
    return kAddUpperImmToPCInstruction;
    break;
  case 0b1110011:
    return decode_environment_I(raw_instruction);
    break;
  }
  return kInvalidInstruction;
}

uint8_t decode_opcode(const uint32_t raw_instruction)
{
  return raw_instruction & 0b01111111;
}

uint8_t decode_func3(const uint32_t raw_instruction)
{
  return (raw_instruction >> 12) & 0b00000111;;
}

uint8_t decode_R_func7(const uint32_t raw_instruction)
{
  return (raw_instruction >> 25) & 0b01111111;
}

RegisterType decode_rd(const uint32_t raw_instruction)
{
  const uint8_t reg = (raw_instruction >> 7) & 0b00011111;
  assert(reg < kNumRegisters);
  return static_cast<RegisterType>(reg);
}

RegisterType decode_rs1(const uint32_t raw_instruction)
{
  const uint8_t reg = (raw_instruction >> 15) & 0b00011111;
  assert(reg < kNumRegisters);
  return static_cast<RegisterType>(reg);
}

RegisterType decode_rs2(const uint32_t raw_instruction)
{
  const uint8_t reg = (raw_instruction >> 20) & 0b00011111;
  assert(reg < kNumRegisters);
  return static_cast<RegisterType>(reg);
}

InstructionType decode_arithmetic_R(const uint32_t raw_instruction)
{
  const uint8_t func3 = decode_func3(raw_instruction);
  const uint8_t func7 = decode_R_func7(raw_instruction);

  if(func3 == 0x0 && func7 == 0x0) {
  return kAddInstruction;
  } else if (func3 == 0 && func7 == 0x20) {
  return kSubInstruction;
  } else if(func3 == 0x4 && func7 == 0x0) {
  return kXorInstruction;
  } else if(func3 == 0x6 && func7 == 0x0) {
  return kOrInstruction;
  } else if(func3 == 0x7 && func7 == 0x0) {
  return kAndInstruction;
  } else if(func3 == 0x1 && func7 == 0x0) {
  return kShiftLeftLogicalInstruction;
  } else if(func3 == 0x5 && func7 == 0x0) {
  return kShiftRightLogicalInstruction;
  } else if(func3 == 0x5 && func7 == 0x20) {
  return kShiftRightArithmeticInstruction;
  } else if(func3 == 0x2 && func7 == 0x0) {
  return kSetLessThanInstruction;
  } else if(func3 == 0x3 && func7 == 0x0) {
    return kSetLessThanUInstruction;
  }
  return kInvalidInstruction;
}

InstructionType decode_arithmetic_I(const uint32_t raw_instruction)
{
  const uint8_t func3 = decode_func3(raw_instruction);
  const int8_t imm_5_thru_11 = decode_I_imm(raw_instruction) & 0x800;
  switch(func3) {
    case 0x0:
      return kAddImmediateInstruction;
      break;
    case 0x4:
      return kXorImmediateInstruction;
      break;
    case 0x6:
      return kOrImmediateInstruction;
      break;
    case 0x7:
      return kAndImmediateInstruction;
      break;
    case 0x1:
      return kShiftLeftLogicalImmInstruction;
      break;
    case 0x5:
      if(imm_5_thru_11) {
        return kShiftRightArithmeticImmInstruction;
      } else {
        return kShiftRightLogicalImmInstruction;
      }
      break;
    case 0x2:
      return kSetLessThanImmInstruction;
      break;
    case 0x3:
      return kSetLessThanUImmInstruction;
      break;
  }
  return kInvalidInstruction;
}

int32_t sign_extend(const uint32_t orig_num, const uint8_t num_bits_in_orig_num)
{
  const int m = 0b1 << (num_bits_in_orig_num - 1);
  return (orig_num ^ m) - m;
}

int32_t decode_I_imm(const uint32_t raw_instruction)
{
  const uint32_t a = (raw_instruction >> 20) & 0b111111111111;
  return sign_extend(a, 12);
}

int32_t decode_S_imm(const uint32_t raw_instruction)
{
  const uint16_t imm_lower = (raw_instruction >> 7) & 0b11111;
  const uint16_t imm_upper = (raw_instruction >> 25) & 0b1111111;
  const uint16_t full = (imm_upper << 5) | imm_lower;
  return sign_extend(full, 12);
}

int32_t decode_B_imm(const uint32_t raw_instruction)
{
  const uint16_t imm_a = (raw_instruction >> 8) & 0b1111; 				// imm[4:1]
  const uint16_t imm_b = (raw_instruction >> 25) & 0b111111;		// imm[10:5]
  const uint16_t imm_c = (raw_instruction >> 7) & 0b1;			// imm[11]
  const uint16_t imm_d = (raw_instruction >> 31) & 0b1;
  const uint16_t full = (imm_d << 12 ) | (imm_c << 11) | (imm_b << 5) | (imm_a << 1);
  return sign_extend(full, 13);
}

int32_t decode_U_imm(const uint32_t raw_instruction)
{
  return raw_instruction & 0xFFFFF000;
}

int32_t decode_J_imm(const uint32_t raw_instruction)
{
  const uint32_t imm_a = (raw_instruction >> 21) & 0b1111111111;
  const uint32_t imm_b = (raw_instruction >> 20) & 0b1;
  const uint32_t imm_c = (raw_instruction >> 12) & 0b11111111;
  const uint32_t imm_d = (raw_instruction >> 31) & 0b1;
  const uint32_t full = (imm_d << 20) | (imm_c << 12) | (imm_b << 11) | (imm_a << 1);
  return sign_extend(full, 21);
}

InstructionType decode_load_I(const uint32_t raw_instruction)
{
  const uint8_t func3 = decode_func3(raw_instruction);
  switch(func3) {
    case 0x0:
      return kLoadByteInstruction;
      break;
    case 0x1:
      return kLoadHalfInstruction;
      break;
    case 0x2:
      return kLoadWordInstruction;
      break;
    case 0x4:
      return kLoadByteUInstruction;
      break;
    case 0x5:
      return kLoadHalfUInstruction;
      break;
  }
  return kInvalidInstruction;
}

InstructionType decode_store_S(const uint32_t raw_instruction)
{
  const uint8_t func3 = decode_func3(raw_instruction);
  switch(func3) {
    case 0x0:
      return kStoreByteInstruction;
      break;
    case 0x1:
      return kStoreHalfInstruction;
      break;
    case 0x2:
      return kStoreWordInstruction;
      break;
  }
  return kInvalidInstruction;
}

InstructionType decode_branch_B(const uint32_t raw_instruction)
{
  const uint8_t func3 = decode_func3(raw_instruction);
  switch(func3) {
    case 0x0:
      return kBranchEqualInstruction;
      break;
    case 0x1:
      return kBranchNotEqualInstruction;
      break;
    case 0x4:
      return kBranchLessThanInstruction;
      break;
    case 0x5:
      return kBranchGreaterThanEqualInstruction;
      break;
    case 0x6:
      return kBranchLessThanUInstruction;
      break;
    case 0x7:
      return kBranchGreaterThanEqualUInstruction;
      break;
  }
  return kInvalidInstruction;
}

InstructionType decode_environment_I(const uint32_t raw_instruction)
{
  const uint16_t imm = decode_I_imm(raw_instruction);
  if(imm == 0x0) {
    return kEnvironmentCallInstruction;
  } else if(imm == 0x1) {
    return kEnvironmentBreakInstruction;
  }
  return kInvalidInstruction;
}
}; // namespace Decode
