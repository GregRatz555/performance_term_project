#include "VM.h"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>

#include "Decode.h"

VM::VM(const size_t mem_size)
 : mem_(mem_size)
{
}

void VM::dump() const
{
  regs_.dump();
}

bool VM::run() {
  while(keep_running_) {
    const uint32_t current_pc = regs_.get_pc();
    const uint32_t current_instruction = mem_.read_word(current_pc);
    execute(current_instruction);
    dump();
  }
  return true;
}

bool VM::run(uint32_t instruction_count) {
  for (uint32_t i = 0; i<instruction_count; i++) {
    const uint32_t current_pc = regs_.get_pc();
    const uint32_t current_instruction = mem_.read_word(current_pc);
    execute(current_instruction);
    dump();
  }
  return true;
}

bool VM::execute(const uint32_t raw_instruction) {
  const Decode::InstructionType instruction = Decode::decode(raw_instruction);
  bool increment_pc = true;
  bool increment_pc_compressed = false;

  switch(instruction) {
	// R-type Instructions
    case Decode::kAddInstruction:
      alu_.ADD(regs_, Decode::decode_rd(raw_instruction), 
		Decode::decode_rs1(raw_instruction), 
		Decode::decode_rs2(raw_instruction));
      break;
    case Decode::kSubInstruction:
      alu_.SUB(regs_, Decode::decode_rd(raw_instruction), 
		Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction));
      break;
    case Decode::kXorInstruction:
      alu_.XOR(regs_, Decode::decode_rd(raw_instruction),
		Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction));
      break;
    case Decode::kOrInstruction:
      alu_.OR(regs_, Decode::decode_rd(raw_instruction),
		Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction));
      break;
    case Decode::kAndInstruction:
        alu_.AND(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_rs2(raw_instruction));
        break;
    case Decode::kShiftLeftLogicalInstruction:
        alu_.SLL(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_rs2(raw_instruction));
        break;
    case Decode::kShiftRightLogicalInstruction:
        alu_.SRL(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_rs2(raw_instruction));
        break;
    case Decode::kShiftRightArithmeticInstruction:
        alu_.SRA(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_rs2(raw_instruction));
        break;
    case Decode::kSetLessThanInstruction:
        alu_.SLT(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_rs2(raw_instruction));
        break;
    case Decode::kSetLessThanUInstruction:
        alu_.SLTU(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_rs2(raw_instruction));
        break;
	// I-type instructions
    case Decode::kAddImmediateInstruction:
        alu_.ADDI(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_I_imm(raw_instruction));
        break;
    case Decode::kXorImmediateInstruction:
        alu_.XORI(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_I_imm(raw_instruction));
        break;
    case Decode::kOrImmediateInstruction:
        alu_.ORI(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_I_imm(raw_instruction));
        break;
    case Decode::kAndImmediateInstruction:
        alu_.ANDI(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_I_imm(raw_instruction));
        break;
    case Decode::kShiftLeftLogicalImmInstruction:
        alu_.SLLI(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_I_imm(raw_instruction));
        break;
    case Decode::kShiftRightLogicalImmInstruction:
        alu_.SRLI(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_I_imm(raw_instruction));
        break;
    case Decode::kShiftRightArithmeticImmInstruction:
        alu_.SRAI(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_I_imm(raw_instruction));
        break;
    case Decode::kSetLessThanImmInstruction:
        alu_.SLTI(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_I_imm(raw_instruction));
        break;
    case Decode::kSetLessThanUImmInstruction:
        alu_.SLTIU(regs_, Decode::decode_rd(raw_instruction),
            Decode::decode_rs1(raw_instruction),
            Decode::decode_I_imm(raw_instruction));
        break;
    case Decode::kLoadByteInstruction:
      mem_.load_byte(regs_, Decode::decode_rd(raw_instruction),
		Decode::decode_rs1(raw_instruction),
		Decode::decode_I_imm(raw_instruction));
      break;
    case Decode::kLoadHalfInstruction:
      mem_.load_half(regs_, Decode::decode_rd(raw_instruction),
		Decode::decode_rs1(raw_instruction),
		Decode::decode_I_imm(raw_instruction));
      break;
    case Decode::kLoadWordInstruction:
      mem_.load_word(regs_, Decode::decode_rd(raw_instruction),
		Decode::decode_rs1(raw_instruction),
		Decode::decode_I_imm(raw_instruction));
      break;
    case Decode::kLoadByteUInstruction:
      mem_.load_u_byte(regs_, Decode::decode_rd(raw_instruction),
		Decode::decode_rs1(raw_instruction),
		Decode::decode_I_imm(raw_instruction));
      break;
    case Decode::kLoadHalfUInstruction:
      mem_.load_u_half(regs_, Decode::decode_rd(raw_instruction),
		Decode::decode_rs1(raw_instruction),
		Decode::decode_I_imm(raw_instruction));
      break;
	case Decode::kJumpAndLinkRegInstruction:
		alu_.JALR(regs_, 1, Decode::decode_rd(raw_instruction), 
						 Decode::decode_J_imm(raw_instruction));
		increment_pc = false;
		break;
	// S-type Instructions
    case Decode::kStoreByteInstruction:
      mem_.store_byte(regs_, Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction),
		Decode::decode_S_imm(raw_instruction));
      break;
    case Decode::kStoreHalfInstruction:
      mem_.store_half(regs_, Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction),
		Decode::decode_S_imm(raw_instruction));
      break;
    case Decode::kStoreWordInstruction:
      mem_.store_word(regs_, Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction),
		Decode::decode_S_imm(raw_instruction));
      break;
	// B-type Instructions
	case Decode::kBranchEqualInstruction:
	  increment_pc = alu_.BEQ(regs_, Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction),
		Decode::decode_B_imm(raw_instruction));
	  break;
	case Decode::kBranchNotEqualInstruction:
	  increment_pc = alu_.BNE(regs_, Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction),
		Decode::decode_B_imm(raw_instruction));
	  break;
	case Decode::kBranchLessThanInstruction:
	  increment_pc = alu_.BLT(regs_, Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction),
		Decode::decode_B_imm(raw_instruction));
	  break;
	case Decode::kBranchGreaterThanEqualInstruction:
	  increment_pc = alu_.BGE(regs_, Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction),
		Decode::decode_B_imm(raw_instruction));
	  break;
	case Decode::kBranchLessThanUInstruction:
	  increment_pc = alu_.BLTU(regs_, Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction),
		Decode::decode_B_imm(raw_instruction));
	  break;
	case Decode::kBranchGreaterThanEqualUInstruction:
	  increment_pc = alu_.BGEU(regs_, Decode::decode_rs1(raw_instruction),
		Decode::decode_rs2(raw_instruction),
		Decode::decode_B_imm(raw_instruction));
	  break;
	// J-Type instruction
	case Decode::kJumpAndLinkInstruction:
		alu_.JAL(regs_, Decode::decode_rd(raw_instruction), 
						Decode::decode_J_imm(raw_instruction));
		increment_pc = false;
		break;
	// U-type Instructions
	case Decode::kLoadUpperImmInstruction:
		alu_.LUI(regs_, Decode::decode_rd(raw_instruction),
						Decode::decode_U_imm(raw_instruction));
    	break;
	case Decode::kAddUpperImmToPCInstruction:
		alu_.AUIPC(regs_, Decode::decode_rd(raw_instruction),
				   		  Decode::decode_U_imm(raw_instruction));
    	break;
	// Unimplemented (beyond scope?)
	case Decode::kEnvironmentCallInstruction:
    // Transfer control to OS
    // do nothing
    	break;
	case Decode::kEnvironmentBreakInstruction:
    // Transfer control to debugger
    // do nothing
		break;

  // Multiply Extension
  // ------------------
	case Decode::kMultiplyInstruction:
		alu_.MUL(regs_, Decode::decode_rd(raw_instruction), 
		Decode::decode_rs1(raw_instruction), 
		Decode::decode_rs2(raw_instruction));
		break;
	case Decode::kMultiplyHighInstruction:
		alu_.MULH(regs_, Decode::decode_rd(raw_instruction), 
		Decode::decode_rs1(raw_instruction), 
		Decode::decode_rs2(raw_instruction));
		break;
	case Decode::kMultiplyHighSUInstruction:
		alu_.MULSU(regs_, Decode::decode_rd(raw_instruction), 
		Decode::decode_rs1(raw_instruction), 
		Decode::decode_rs2(raw_instruction));
		break;
	case Decode::kMultiplyHighUInstruction:
		alu_.MULU(regs_, Decode::decode_rd(raw_instruction), 
		Decode::decode_rs1(raw_instruction), 
		Decode::decode_rs2(raw_instruction));
		break;
	case Decode::kDivideInstruction:
		alu_.DIV(regs_, Decode::decode_rd(raw_instruction), 
		Decode::decode_rs1(raw_instruction), 
		Decode::decode_rs2(raw_instruction));
		break;
	case Decode::kDivideUInstruction:
		alu_.DIVU(regs_, Decode::decode_rd(raw_instruction), 
		Decode::decode_rs1(raw_instruction), 
		Decode::decode_rs2(raw_instruction));
		break;
	case Decode::kRemainderInstruction:
		alu_.REM(regs_, Decode::decode_rd(raw_instruction), 
		Decode::decode_rs1(raw_instruction), 
		Decode::decode_rs2(raw_instruction));
		break;
	case Decode::kRemainderUInstruction:
		alu_.REMU(regs_, Decode::decode_rd(raw_instruction), 
		Decode::decode_rs1(raw_instruction), 
		Decode::decode_rs2(raw_instruction));
		break;

	// Compressed Extension
	// --------------------
	case Decode::kcLoadWordFromSPInstruction:					// c.lwsp
		mem_.load_word(regs_, Decode::decode_CI_rd(raw_instruction), (uint8_t) SP,
							  Decode::decode_CLWSP_imm(raw_instruction));
		increment_pc = false;
		increment_pc_compressed = true;
		break;
	case Decode::kcStoreWordToSPInstruction:					// c.swsp
		mem_.store_word(regs_, (uint8_t) SP, Decode::decode_CSS_rs2(raw_instruction),
							   Decode::decode_CSS_imm(raw_instruction));
		increment_pc = false;
		increment_pc_compressed = true;
		break;
	case Decode::kcLoadWordInstruction:							// c.lw
		mem_.load_word(regs_, Decode::decode_CL_rd(raw_instruction),
							  Decode::decode_CL_rs1(raw_instruction),
							  Decode::decode_CL_imm(raw_instruction));
		increment_pc = false;
		increment_pc_compressed = true;
		break;
	case Decode::kcStoreWordInstruction:						// c.sw
		mem_.store_word(regs_, Decode::decode_CS_rs1(raw_instruction),
							   Decode::decode_CS_rs2(raw_instruction),
							   Decode::decode_CS_imm(raw_instruction));
		increment_pc = false;
		increment_pc_compressed = true;
		break;
	case Decode::kcJumpInstruction:								// c.j
		alu_.JAL(regs_, (uint8_t) 0, Decode::decode_CJ_offset(raw_instruction));
		increment_pc = false;
		break;
	case Decode::kcJumpAndLinkInstruction:						// c.jal
		alu_.JAL(regs_, (uint8_t) 1, Decode::decode_CJ_offset(raw_instruction));
		increment_pc = false;
		break;
	case Decode::kcJumpRegInstruction:							// c.jr
		alu_.JALR(regs_, (uint8_t) 0, Decode::decode_CR_rs1(raw_instruction), (int32_t) 0);
		increment_pc = false;
		break;
	case Decode::kcJumpAndLinkRegInstruction:					// c.jalr
		{
		uint8_t tmp_rs1 = Decode::decode_CR_rs1(raw_instruction);
		if (tmp_rs1 == 0) return VM::execute(Decode::kEnvironmentBreakInstruction); // Per spec
		alu_.JALR(regs_, 1, tmp_rs1, 0);
		regs_.set(1, regs_.get(1) - 2); // Per spec note
		increment_pc = false;
		} break;
	case Decode::kcBranchZeroInstruction:						// c.beqz
		increment_pc = false;
		increment_pc_compressed = alu_.BEQ(regs_, Decode::decode_CB_rs1(raw_instruction),
												  (uint8_t) 0, Decode::decode_CB_imm(raw_instruction));
		break;
	case Decode::kcBranchNotZeroInstruction:					// c.bnez
		increment_pc = false;
		increment_pc_compressed = alu_.BNE(regs_, Decode::decode_CB_rs1(raw_instruction),
												  (uint8_t) 0, Decode::decode_CB_imm(raw_instruction));
		break;
	case Decode::kcLoadImmediateInstruction:					// c.li
		alu_.ADDI(regs_, Decode::decode_CI_rd(raw_instruction), (uint8_t) 0,
				  Decode::decode_CI_imm(raw_instruction));
		increment_pc = false;
		increment_pc_compressed = true;
		break;
	case Decode::kcLoadUpperImmediateInstruction: 				// c.lui
		alu_.ADDI(regs_, Decode::decode_CI_rd(raw_instruction), (uint8_t) 0,
				  Decode::decode_CI_imm(raw_instruction) << 12);
		increment_pc = false;
		increment_pc_compressed = true;
		break;
	case Decode::kcAddImmediateInstruction:						// c.addi
		{
		uint8_t tmp_rd = Decode::decode_CI_rd(raw_instruction);
		alu_.ADDI(regs_, tmp_rd, tmp_rd, Decode::decode_CI_imm(raw_instruction));
		increment_pc = false;
		increment_pc_compressed = true;
		} break;
	case Decode::kcAdd16xImmediateToSPInstruction:				// c.addi16sp
		alu_.ADDI(regs_, SP , SP, Decode::decode_CADDI16SP_imm(raw_instruction));
		increment_pc = false;
		increment_pc_compressed = true;
		break;
	case Decode::kcShiftLeftLogicalImmediateInstruction:		// c.slli
		alu_.SLLI(regs_, Decode::decode_CI_rd(raw_instruction),
						 Decode::decode_CI_rd(raw_instruction),
						 Decode::decode_CI_imm(raw_instruction));
		increment_pc = false;
		increment_pc_compressed = true;
		break;
	case Decode::kcShiftRightLogicalImmediateInstruction:		// c.srli
		alu_.SRLI(regs_, Decode::decode_CI_rd(raw_instruction),
						 Decode::decode_CI_rd(raw_instruction),
						 Decode::decode_CI_imm(raw_instruction));
		increment_pc = false;
		increment_pc_compressed = true;
		break;
	case Decode::kcShiftRightArithmeticImmediateInstruction:	// c.srai
		alu_.SRAI(regs_, Decode::decode_CB_rs1(raw_instruction),
						 Decode::decode_CB_rs1(raw_instruction),
						 Decode::decode_CB_imm(raw_instruction));
		increment_pc = false;
		increment_pc_compressed = true;
		break;
	case Decode::kcANDInstruction:								// c.andi
		alu_.ANDI(regs_, Decode::decode_CB_rs1(raw_instruction),
						 Decode::decode_CB_rs1(raw_instruction),
						 Decode::decode_CB_imm(raw_instruction));
		increment_pc = false;
		increment_pc_compressed = true;
		break;
	case Decode::kcMoveInstruction:								// c.mv
		alu_.ADD(regs_, Decode::decode_CR_rs1(raw_instruction), (uint8_t) 0,
					 	Decode::decode_CR_rs2(raw_instruction));
		increment_pc = false;
		increment_pc_compressed = true;
		break;
	case Decode::kcADDInstruction:								// c.add
		alu_.ADD(regs_, Decode::decode_CR_rs1(raw_instruction),
						Decode::decode_CR_rs1(raw_instruction),
					 	Decode::decode_CR_rs2(raw_instruction));
		increment_pc = false;
		increment_pc_compressed = true;
		break;
	case Decode::kcANDImmediateInstruction:						// c.and
		alu_.AND(regs_, Decode::decode_CA_rs1(raw_instruction),
						Decode::decode_CA_rs1(raw_instruction),
					 	Decode::decode_CA_rs2(raw_instruction));
		increment_pc = false;
		increment_pc_compressed = true;
		break;
	case Decode::kcORInstruction:								// c.or
		alu_.OR(regs_, Decode::decode_CA_rs1(raw_instruction),
					   Decode::decode_CA_rs1(raw_instruction),
					   Decode::decode_CA_rs2(raw_instruction));
		increment_pc = false;
		increment_pc_compressed = true;
		break;
	case Decode::kcXORInstruction:								// c.xor
		alu_.XOR(regs_, Decode::decode_CA_rs1(raw_instruction),
						Decode::decode_CA_rs1(raw_instruction),
						Decode::decode_CA_rs2(raw_instruction));
		increment_pc = false;
		increment_pc_compressed = true;
		break;
	case Decode::kcSUBInstruction:								// c.sub
		alu_.SUB(regs_, Decode::decode_CA_rs1(raw_instruction),
						Decode::decode_CA_rs1(raw_instruction),
						Decode::decode_CA_rs2(raw_instruction));
		increment_pc = false;
		increment_pc_compressed = true;
		break;
	case Decode::kcNOPInstruction:								// c.nop
		increment_pc = false;
		increment_pc_compressed = true;
		break;
	case Decode::kcEnvironmentBreakInstruction:					// c.ebreak
		increment_pc = false;
		increment_pc_compressed = true;
		break;

	// Invalid instruction Fallthrough
    case Decode::kInvalidInstruction:
    default:
      throw std::runtime_error("Invalid or unknown instruction id: " +
			 std::to_string(instruction) + " [" + std::to_string(raw_instruction) + "]");
  }

  if(increment_pc) {
    regs_.set_pc(regs_.get_pc()+sizeof(uint32_t));
  }
  if(increment_pc_compressed) {
    regs_.set_pc(regs_.get_pc()+sizeof(uint16_t));
  }

  return true;
}

void VM::dump_mem(uint32_t front, uint32_t back) const
{
       mem_.debug_dump_range(front, back);
}

void VM::load_elf(const std::string &filename){

  std::ifstream input_file(filename, std::ios::binary);
  input_file.seekg(0, std::ios::end);
  const auto size = input_file.tellg();
  input_file.seekg(0);

  std::vector<uint8_t> data;
  data.resize(size);
  input_file.read((char*)data.data(), size);

  for(int i = 0; i < size; i++) {
    mem_.store(i, data[i]);
  }
}

const RegisterValues& VM::get_regs() const
{
  return regs_.get_values();
}
void VM::set_regs(const RegisterValues &new_regs)
{
  regs_.set_values(new_regs);
}
