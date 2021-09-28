#include <stdbool.h>
#include <stdint.h>

#define DEBUG 0

// Lab Document
#define MAX_NUM_REGS 8

enum run_type {
  FINISH,
  NOT_FINISH,
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

#define string_equal(str1, str2) ((bool)(strcmp(str1, str2) == 0))

#define EVEN(value) (((uint16_t)value) % 2)
#define ADDRESS(addr) (((uint16_t)addr) >> 1)

#define LSHFT(reg, amt4) (((uint16_t)reg) << amt4)
#define RSHFTL(reg, amt4) (((uint16_t)reg) >> amt4)
#define RSHFTA(reg, amt4) (((int16_t)reg) >> amt4)

#define SET_MEMORY(mem1, mem2) ((((uint8_t)mem1) << 8) | ((uint8_t)mem2))
#define GET_LOW_BYTE(mem) (((uint16_t)mem) & 0xFF)
#define GET_HIGH_BYTE(mem) ((((uint16_t)mem) & 0xFF00) >> 8)

#define SEXT(val, sig_ext) (((uint16_t)val) | (0 - (((uint16_t)val) & sig_ext)))
#define ZEXT(x) (((uint16_t)x) & 0x00FF)

#define LSHIFT(pc_off) (((uint16_t)pc_off) << 1)

#define MASK_16_BITS(val) (((uint16_t)val) & 0xFFFF)
#define MASK_8_BITS(val) ((uint8_t)(((uint16_t)val) & 0xFF))

// Magic Numbers
#define REGISTER 0
#define IMMEDIATE 1

#define LSHF 0
#define RSHFL 1
#define RSHFA 3

#define SEXT_11BITS 0x400
#define SEXT_9BITS  0x100
#define SEXT_8BITS  0x80
#define SEXT_6BITS  0x20
#define SEXT_5BITS  0x10


#define LOW_BYTE 0
#define HIGH_BYTE 1

#define RETURN_REG 7

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