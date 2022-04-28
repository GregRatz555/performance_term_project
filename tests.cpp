#include <gtest/gtest.h>
#include <chrono>
#include <thread>
#include "VM.h"

class AluTest: public ::testing::Test {
 public:
  AluTest() = default;
  virtual ~AluTest() = default;

 protected:

  void SetUp() override
  {
    expected_values_.regs.fill(0);
    expected_values_.pc = 0;
  }

  // void TearDown() override {}
  //

  VM vm_{1*1024};
  RegisterValues expected_values_;
};

TEST_F(AluTest, load_imm_positive) {

  expected_values_.regs[Decode::kRegister0] = 0;
  expected_values_.pc += 4;
  vm_.execute(0x00500013); //           li  zero,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister1] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500093); //           li  ra,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister2] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500113); //           li  sp,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister3] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500193); //           li  gp,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister4] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500213); //           li  tp,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister5] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500293); //           li  t0,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister6] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500313); //           li  t1,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister7] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500393); //           li  t2,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister8] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500413); //           li  s0,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister9] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500493); //           li  s1,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister10] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500513); //           li  a0,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister11] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500593); //           li  a1,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister12] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500613); //           li  a2,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister13] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500693); //           li  a3,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister14] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500713); //           li  a4,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister15] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500793); //           li  a5,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister16] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500813); //           li  a6,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister17] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500893); //           li  a7,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister18] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500913); //           li  s2,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister19] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500993); //           li  s3,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister20] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500a13); //           li  s4,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister21] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500a93); //           li  s5,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister22] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500b13); //           li  s6,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister23] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500b93); //           li  s7,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister24] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500c13); //           li  s8,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister25] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500c93); //           li  s9,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister26] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500d13); //           li  s10,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister27] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500d93); //           li  s11,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister28] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500e13); //           li  t3,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister29] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500e93); //           li  t4,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister30] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500f13); //           li  t5,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister31] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500f93); //           li  t6,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);
}

TEST_F(AluTest, load_imm_negative) {

  expected_values_.regs[Decode::kRegister0] = 0;
  expected_values_.pc += 4;
  vm_.execute(0xffb00013); //           li  zero,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister1] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00093); //           li  ra,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister2] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00113); //           li  sp,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister3] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00193); //           li  gp,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister4] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00213); //           li  tp,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister5] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00293); //           li  t0,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister6] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00313); //           li  t1,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister7] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00393); //           li  t2,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister8] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00413); //           li  s0,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister9] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00493); //           li  s1,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister10] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00513); //           li  a0,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister11] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00593); //           li  a1,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister12] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00613); //           li  a2,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister13] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00693); //           li  a3,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister14] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00713); //           li  a4,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister15] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00793); //           li  a5,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister16] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00813); //           li  a6,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister17] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00893); //           li  a7,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister18] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00913); //           li  s2,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister19] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00993); //           li  s3,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister20] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00a13); //           li  s4,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister21] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00a93); //           li  s5,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister22] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00b13); //           li  s6,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister23] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00b93); //           li  s7,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister24] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00c13); //           li  s8,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister25] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00c93); //           li  s9,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister26] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00d13); //           li  s10,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister27] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00d93); //           li  s11,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister28] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00e13); //           li  t3,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister29] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00e93); //           li  t4,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister30] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00f13); //           li  t5,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister31] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00f93); //           li  t6,-5}
  EXPECT_EQ(vm_.get_regs(), expected_values_);
}

TEST_F(AluTest, add_positive) {

  expected_values_.regs[Decode::kRegister1] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500093); //           li  ra,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister2] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500113); //           li  sp,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister3] = 10;
  expected_values_.pc += 4;
  vm_.execute(0x002081b3); //           add gp,ra,sp
  EXPECT_EQ(vm_.get_regs(), expected_values_);
}

TEST_F(AluTest, add_negative) {

  expected_values_.regs[Decode::kRegister1] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00093); //           li  ra,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister2] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00113); //           li  sp,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister3] = -10;
  expected_values_.pc += 4;
  vm_.execute(0x002081b3); //           add gp,ra,sp
  EXPECT_EQ(vm_.get_regs(), expected_values_);
}

TEST_F(AluTest, sub_positive) {
  expected_values_.regs[Decode::kRegister1] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500093); //           li  ra,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister2] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500113); //           li  sp,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister3] = 0;
  expected_values_.pc += 4;
  vm_.execute(0x402081b3); //           sub gp,ra,sp
  EXPECT_EQ(vm_.get_regs(), expected_values_);
}

TEST_F(AluTest, sub_negative) {
  expected_values_.regs[Decode::kRegister1] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00093); //           li  ra,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister2] = -5;
  expected_values_.pc += 4;
  vm_.execute(0xffb00113); //           li  sp,-5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister3] = 0;
  expected_values_.pc += 4;
  vm_.execute(0x402081b3); //           sub gp,ra,sp
  EXPECT_EQ(vm_.get_regs(), expected_values_);
}

TEST_F(AluTest, xor_positive) {
  expected_values_.regs[Decode::kRegister1] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500093); //           li  ra,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister2] = 5;
  expected_values_.pc += 4;
  vm_.execute(0x00500113); //           li  sp,5
  EXPECT_EQ(vm_.get_regs(), expected_values_);

  expected_values_.regs[Decode::kRegister3] = 0;
  expected_values_.pc += 4;
  vm_.execute(0x0020c1b3); //           xor gp,ra,sp
  EXPECT_EQ(vm_.get_regs(), expected_values_);
}

TEST_F(AluTest, shift_right_logical) {
  RegisterValues input;

  input.regs[Decode::kRegister1] = -5;
  input.regs[Decode::kRegister2] = 1;
  vm_.set_regs(input);

  expected_values_.regs[Decode::kRegister1] = -5;
  expected_values_.regs[Decode::kRegister2] = 1;
  expected_values_.regs[Decode::kRegister3] = 0x7FFFFFFD;
  expected_values_.pc += 4;
  vm_.execute(0x0020d1b3); // srl gp,ra,sp
  EXPECT_EQ(vm_.get_regs(), expected_values_);
}

TEST_F(AluTest, shift_right_arithmedic) {
  RegisterValues input;

  input.regs[Decode::kRegister1] = -5;
  input.regs[Decode::kRegister2] = 1;
  vm_.set_regs(input);


  expected_values_.regs[Decode::kRegister1] = -5;
  expected_values_.regs[Decode::kRegister2] = 1;
  expected_values_.regs[Decode::kRegister3] = -3;
  expected_values_.pc += 4;

  vm_.execute(0x4020d1b3); //           sra gp,ra,sp
  EXPECT_EQ(vm_.get_regs(), expected_values_);
}

TEST_F(AluTest, load_word) {
  Memory mem(1024);
  mem.write_data<uint32_t>(0x200, 0x20000040);
  vm_.set_mem(mem);

  expected_values_.regs[Decode::kRegister1] = 0x20000040;
  expected_values_.regs[Decode::kRegister2] = 0x1ec;
  expected_values_.pc += 4;

  RegisterValues input;
  input.regs[Decode::kRegister2] = 0x1ec;
  vm_.set_regs(input);

  vm_.execute(0x01412083);  // lw ra, 20(sp)
  EXPECT_EQ(vm_.get_regs(), expected_values_);
}

TEST_F(AluTest, load_half) {
  Memory mem(1024);
  mem.write_data<uint16_t>(0x200, 0x00000040);
  vm_.set_mem(mem);

  expected_values_.regs[Decode::kRegister1] = 0x00000040;
  expected_values_.regs[Decode::kRegister2] = 0x1ec;
  expected_values_.pc += 4;

  RegisterValues input;
  input.regs[Decode::kRegister2] = 0x1ec;
  vm_.set_regs(input);

  vm_.execute(0x01411083);  // lh ra, 20(sp)
  EXPECT_EQ(vm_.get_regs(), expected_values_);
}

TEST_F(AluTest, load_u_half) {
  Memory mem(1024);
  mem.write_data<uint16_t>(0x200, 0x00000040);
  vm_.set_mem(mem);

  expected_values_.regs[Decode::kRegister1] = 0x00000040;
  expected_values_.regs[Decode::kRegister2] = 0x1ec;
  expected_values_.pc += 4;

  RegisterValues input;
  input.regs[Decode::kRegister2] = 0x1ec;
  vm_.set_regs(input);

  vm_.execute(0x01410083);  // lh ra, 20(sp)
  EXPECT_EQ(vm_.get_regs(), expected_values_);
}

TEST_F(AluTest, load_byte) {
  Memory mem(1024);
  mem.write_data<uint8_t>(0x200, 0x00000040);
  vm_.set_mem(mem);

  expected_values_.regs[Decode::kRegister1] = 0x00000040;
  expected_values_.regs[Decode::kRegister2] = 0x1ec;
  expected_values_.pc += 4;

  RegisterValues input;
  input.regs[Decode::kRegister2] = 0x1ec;
  vm_.set_regs(input);

  vm_.execute(0x01410083);  // lb ra, 20(sp)
  EXPECT_EQ(vm_.get_regs(), expected_values_);
}

TEST_F(AluTest, load_u_byte) {
  Memory mem(1024);
}

TEST_F(AluTest, store_word) {

  RegisterValues input;
  input.regs[Decode::kRegister1] = 0x02004000;
  input.regs[Decode::kRegister2] = 0x1ec;
  vm_.set_regs(input);

  Memory mem_expected(1024);
  mem_expected.write_data<uint32_t>(0x200, 0x02004000);

  vm_.execute(0x00112a23);  // sw ra, 20(sp)
  EXPECT_EQ(vm_.get_mem(), mem_expected);
}

TEST_F(AluTest, store_half) {
  RegisterValues input;
  input.regs[Decode::kRegister1] = 0x02004000;
  input.regs[Decode::kRegister2] = 0x1ec;
  vm_.set_regs(input);

  Memory mem_expected(1024);
  mem_expected.write_data<uint16_t>(0x200, 0x00004000);

  vm_.execute(0x00111a23);  // sh ra, 20(sp)
  EXPECT_EQ(vm_.get_mem(), mem_expected);
}

TEST_F(AluTest, store_byte) {
  RegisterValues input;
  input.regs[Decode::kRegister1] = 0x02004040;
  input.regs[Decode::kRegister2] = 0x1ec;
  vm_.set_regs(input);

  Memory mem_expected(1024);
  mem_expected.write_data<uint8_t>(0x200, 0x00000040);

  vm_.execute(0x00110a23);  // sb ra, 20(sp)
  EXPECT_EQ(vm_.get_mem(), mem_expected);
}

TEST_F(AluTest, determine_clock_rate) {
  Memory mem(1024);
  const uint32_t start = mem.read_clock();
  std::this_thread::sleep_for(std::chrono::seconds(4));
  const uint32_t stop = mem.read_clock();
  printf("Start: %u\nStop: %u\n", start, stop);
}
