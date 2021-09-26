#include <stdbool.h>
#include <stdint.h>

#define DEBUG 1

// Lab Document
#define WORDS_IN_MEM 0x08000
#define MAX_NUM_REGS 8

enum run_type {
  FINISH,
  NOT_FINISH,
};

struct System_Latches {
  uint16_t PC;
  bool N;
  bool Z;
  bool P;

  int16_t REGS[MAX_NUM_REGS]; /* register file. */
};

// Opcodes
enum opcode {
  ADD = 0x1,
  AND = 0x5,
  BR = 0x0,
  JMP_RET = 0xC,
  JSR_JSRR = 0x4,
  LDB = 0x2,
  LDW = 0x6,
  LEA = 0xE,
  SHFT = 0xD,
  STB = 0x3,
  STW = 0x7,
  TRAP = 0xF,
  XOR_NOT = 0x9,

  INVALID = 0xFF,
};

// Magic Numbers
#define REGISTER 0
#define IMMEDIATE 1

#define LSHF 0
#define RSHFL 1
#define RSHFA 3

#define string_equal(str1, str2) ((bool)(strcmp(str1, str2) == 0))

// Getters
#define GET_OPCODE(instr) ((((uint16_t)instr) & 0xf000) >> 12)

#define GET_DR(instr) ((((uint16_t)instr) & 0x0e00) >> 9)
#define GET_SR(instr) ((((uint16_t)instr) & 0x01c0) >> 6)
#define GET_ST_SR(instr) ((((uint16_t)instr) & 0x0e00) >> 9)
#define GET_SR1(instr) ((((uint16_t)instr) & 0x01c0) >> 6)
#define GET_SR2(instr) ((((uint16_t)instr) & 0x0007) >> 0)
#define GET_BASE_R(instr) ((((uint16_t)instr) & 0x01c0) >> 6)

#define GET_IMM_OR_REG_B5(instr) ((((uint16_t)instr) & 0x0020) >> 5)
#define GET_IMM_OR_REG_B11(instr) ((((uint16_t)instr) & 0x0800) >> 11)
#define GET_SHF_TYPE(instr) ((((uint16_t)instr) & 0x0030) >> 4)

#define GET_IMM5(instr) ((((uint16_t)instr) & 0x001f) >> 0)
#define GET_AMOUNT4(instr) ((((uint16_t)instr) & 0x000f) >> 0)

#define GET_PCOFFSET9(instr) ((((uint16_t)instr) & 0x01ff) >> 0)
#define GET_PCOFFSET11(instr) ((((uint16_t)instr) & 0x07ff) >> 0)
#define GET_BOFFSET6(instr) ((((uint16_t)instr) & 0x003f) >> 0)
#define GET_OFFSET6(instr) ((((uint16_t)instr) & 0x003f) >> 0)

#define GET_CC_N(instr) ((((uint16_t)instr) & 0x0800) >> 11)
#define GET_CC_Z(instr) ((((uint16_t)instr) & 0x0400) >> 10)
#define GET_CC_P(instr) ((((uint16_t)instr) & 0x0200) >> 9)

#define GET_TRAPVECT8(instr) ((((uint16_t)instr) & 0x00ff) >> 0)

#define ADDRESS(addr) (((uint16_t)addr) >> 1)

#define SET_MEMORY(mem1, mem2) ((((uint8_t)mem1) << 8) | ((uint8_t)mem2))

#define LSHFT(reg, amt4) (((uint16_t)reg) << amt4)
#define RSHFTL(reg, amt4) (((uint16_t)reg) >> amt4)
#define RSHFTA(reg, amt4) (((int16_t)reg) >> amt4)

#define LSHIFT(pc_off) (((uint16_t)pc_off) << 1)

#define SEXT(val, sig_ext) (((uint16_t)val) | (0 - (((uint16_t)val) & sig_ext)))
#define ZEXT(x) (((uint16_t)x) & 0x00FF)

#define CHECK_VALID_PC(x) (x)