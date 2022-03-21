#include <gtest/gtest.h>
#include "VM.h"

class AluTest: public ::testing::Test {
 public:
  AluTest() = default;
  virtual ~AluTest() = default;

 protected:

  void SetUp() override {
  }

  // void TearDown() override {}
  //

  VM vm_{64*1024};
};

TEST_F(AluTest, load_imm_positive) {
  vm_.execute(0x00500013); //           li  zero,5
  vm_.execute(0x00500093); //           li  ra,5
  vm_.execute(0x00500113); //           li  sp,5
  vm_.execute(0x00500193); //           li  gp,5
  vm_.execute(0x00500213); //           li  tp,5
  vm_.execute(0x00500293); //           li  t0,5
  vm_.execute(0x00500313); //           li  t1,5
  vm_.execute(0x00500393); //           li  t2,5
  vm_.execute(0x00500413); //           li  s0,5
  vm_.execute(0x00500493); //           li  s1,5
  vm_.execute(0x00500513); //           li  a0,5
  vm_.execute(0x00500593); //           li  a1,5
  vm_.execute(0x00500613); //           li  a2,5
  vm_.execute(0x00500693); //           li  a3,5
  vm_.execute(0x00500713); //           li  a4,5
  vm_.execute(0x00500793); //           li  a5,5
  vm_.execute(0x00500813); //           li  a6,5
  vm_.execute(0x00500893); //           li  a7,5
  vm_.execute(0x00500913); //           li  s2,5
  vm_.execute(0x00500993); //           li  s3,5
  vm_.execute(0x00500a13); //           li  s4,5
  vm_.execute(0x00500a93); //           li  s5,5
  vm_.execute(0x00500b13); //           li  s6,5
  vm_.execute(0x00500b93); //           li  s7,5
  vm_.execute(0x00500c13); //           li  s8,5
  vm_.execute(0x00500c93); //           li  s9,5
  vm_.execute(0x00500d13); //           li  s10,5
  vm_.execute(0x00500d93); //           li  s11,5
  vm_.execute(0x00500e13); //           li  t3,5
  vm_.execute(0x00500e93); //           li  t4,5
  vm_.execute(0x00500f13); //           li  t5,5
  vm_.execute(0x00500f93); //           li  t6,5
  vm_.dump();
}

TEST_F(AluTest, load_imm_negative) {
  vm_.execute(0xffb00013); //           li  zero,-5
  vm_.execute(0xffb00093); //           li  ra,-5
  vm_.execute(0xffb00113); //           li  sp,-5
  vm_.execute(0xffb00193); //           li  gp,-5
  vm_.execute(0xffb00213); //           li  tp,-5
  vm_.execute(0xffb00293); //           li  t0,-5
  vm_.execute(0xffb00313); //           li  t1,-5
  vm_.execute(0xffb00393); //           li  t2,-5
  vm_.execute(0xffb00413); //           li  s0,-5
  vm_.execute(0xffb00493); //           li  s1,-5
  vm_.execute(0xffb00513); //           li  a0,-5
  vm_.execute(0xffb00593); //           li  a1,-5
  vm_.execute(0xffb00613); //           li  a2,-5
  vm_.execute(0xffb00693); //           li  a3,-5
  vm_.execute(0xffb00713); //           li  a4,-5
  vm_.execute(0xffb00793); //           li  a5,-5
  vm_.execute(0xffb00813); //           li  a6,-5
  vm_.execute(0xffb00893); //           li  a7,-5
  vm_.execute(0xffb00913); //           li  s2,-5
  vm_.execute(0xffb00993); //           li  s3,-5
  vm_.execute(0xffb00a13); //           li  s4,-5
  vm_.execute(0xffb00a93); //           li  s5,-5
  vm_.execute(0xffb00b13); //           li  s6,-5
  vm_.execute(0xffb00b93); //           li  s7,-5
  vm_.execute(0xffb00c13); //           li  s8,-5
  vm_.execute(0xffb00c93); //           li  s9,-5
  vm_.execute(0xffb00d13); //           li  s10,-5
  vm_.execute(0xffb00d93); //           li  s11,-5
  vm_.execute(0xffb00e13); //           li  t3,-5
  vm_.execute(0xffb00e93); //           li  t4,-5
  vm_.execute(0xffb00f13); //           li  t5,-5
  vm_.execute(0xffb00f93); //           li  t6,-5}
  vm_.dump();
}

TEST_F(AluTest, add_positive) {
  vm_.execute(0x00500093); //           li  ra,5
  vm_.execute(0x00500113); //           li  sp,5
  vm_.execute(0x002081b3); //           add gp,ra,sp
  vm_.dump();
}

TEST_F(AluTest, add_negative) {
  vm_.execute(0xffb00093); //           li  ra,-5
  vm_.execute(0xffb00113); //           li  sp,-5
  vm_.execute(0x002081b3); //           add gp,ra,sp
  vm_.dump();
}

TEST_F(AluTest, sub_positive) {
  vm_.execute(0x00500093); //           li  ra,5
  vm_.execute(0x00500113); //           li  sp,5
  vm_.execute(0x402081b3); //           sub gp,ra,sp
  vm_.dump();
}

TEST_F(AluTest, sub_negative) {
  vm_.execute(0xffb00093); //           li  ra,-5
  vm_.execute(0xffb00113); //           li  sp,-5
  vm_.execute(0x402081b3); //           sub gp,ra,sp
  vm_.dump();
}

TEST_F(AluTest, xor_positive) {
  vm_.execute(0x00500093); //           li  ra,5
  vm_.execute(0x00500113); //           li  sp,5
  vm_.execute(0x0020c1b3); //           xor gp,ra,sp
  vm_.dump();
}

