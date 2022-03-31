#ifndef __DECODE_HPP_
#define __DECODE_HPP_

#include <cstdint>

class Decode {
 public:
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
  };

  InstructionType decode(const uint32_t raw_instruction);

 private:
  uint8_t decode_opcode(const uint32_t raw_instruction);

  uint8_t decode_R_func3(const uint32_t raw_instruction);
  uint8_t decode_R_func7(const uint32_t raw_instruction);
  uint8_t decode_R_rd(const uint32_t raw_instruction);
  uint8_t decode_R_rs1(const uint32_t raw_instruction);
  uint8_t decode_R_rs2(const uint32_t raw_instruction);

  InstructionType decode_arithmetic_R(const uint32_t raw_instruction);

};

#endif
