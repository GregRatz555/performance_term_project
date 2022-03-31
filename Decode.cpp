#include "Decode.h"

Decode::InstructionType Decode::decode(const uint32_t raw_instruction)
{
  const uint8_t opcode = decode_opcode(raw_instruction);
  switch(opcode) {
	case 0b0110011:
	  return decode_arithmetic_R(raw_instruction);
	  break;
  }
  return kInvalidInstruction;
}

uint8_t Decode::decode_opcode(const uint32_t raw_instruction)
{
  return raw_instruction & 0b00111111;
}

uint8_t Decode::decode_R_func3(const uint32_t raw_instruction)
{
  return (raw_instruction >> 12) & 0b00000111;;
}

uint8_t Decode::decode_R_func7(const uint32_t raw_instruction)
{
  return (raw_instruction >> 25) & 0b01111111;
}

uint8_t Decode::decode_R_rd(const uint32_t raw_instruction)
{
  return (raw_instruction >> 7) & 0b00011111;
}

uint8_t Decode::decode_R_rs1(const uint32_t raw_instruction)
{
  return (raw_instruction >> 15) & 0b00011111;
}

uint8_t Decode::decode_R_rs2(const uint32_t raw_instruction)
{
  return (raw_instruction >> 20) & 0b00011111;
}

Decode::InstructionType Decode::decode_arithmetic_R(const uint32_t raw_instruction)
{
  const uint8_t func3 = decode_R_func3(raw_instruction);
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
	//return kSetL;
  }
  return kInvalidInstruction;
}

