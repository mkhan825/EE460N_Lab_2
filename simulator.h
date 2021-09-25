#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define DEBUG 1

/* Defines */
// Getters
// Magic Numbers
#define AMT_LC3_REGS 8
#define MAX_MEM_LOCATIONS 0x8000

/* Enums or Structs */
enum
{
  DONE, OK, EMPTY_LINE
};

enum run_type {
  FINISH,
  NOT_FINISH,
};

// Opcodes
enum opcode {
  ADD = 0x1,
  AND = 0x5,

  BR = 0x0,
  BRP = 0x0,
  BRZ = 0x0,
  BRZP = 0x0,
  BRN = 0x0,
  BRNP = 0x0,
  BRNZ = 0x0,
  BRNZP = 0x0,

  JMP = 0xC,
  RET = 0xC,

  JSR = 0x4,
  JSRR = 0x4,

  LDB = 0x2,
  LDW = 0x6,
  LEA = 0xE,
  RTI = 0x8,

  LSHF = 0xD,
  RSHFL = 0xD,
  RSHFA = 0xD,

  STB = 0x3,
  STW = 0x7,
  TRAP = 0xF,

  XOR = 0x9,
  NOT = 0x9,

  INVALID = 0xFF,
};

struct System_Latches_Struct {
  bool PC;
  bool N;
  bool P;
  bool Z;

  uint16_t REGS[AMT_LC3_REGS];
};

#define string_equal(str1, str2) ((bool)(strcmp(str1, str2) == 0))

//Getters
#define GET_OPCODE(instr) ((((uint16_t)instr) & 0xf000) >> 12)

#define GET_DR(instr) ((((uint16_t)instr) & 0gx0700) << 9)
#define GET_SR(instr) ((((uint16_t)instr) & 0x7) << 6)
#define GET_ST_SR(instr) ((((uint16_t)instr) & 0x7) << 9)
#define GET_SR1(instr) ((((uint16_t)instr) & 0x7) << 6)
#define GET_SR2(instr) ((((uint16_t)instr) & 0x7) << 0)
#define GET_BASE_R(instr) ((((uint16_t)instr) & 0x7) << 6)

#define GET_IMM_OR_REG_B5(instr) ((((uint16_t)instr) & 0x1) << 5)
#define GET_IMM_OR_REG_B11(instr) ((((uint16_t)instr) & 0x1) << 11)
#define GET_SHF_TYPE(instr) ((((uint16_t)instr) & 0x3) << 4)

#define GET_IMM5(instr) ((((uint16_t)instr) & 0x1f) << 0)
#define GET_AMOUNT4(instr) ((((uint16_t)instr) & 0xf) << 0)

#define GET_PCOFFSET9(instr) ((((uint16_t)instr) & 0x1ff) << 0)
#define GET_PCOFFSET11(instr) ((((uint16_t)instr) & 0x7ff) << 0)
#define GET_BOFFSET6(instr) ((((uint16_t)instr) & 0x2f) << 0)
#define GET_OFFSET6(instr) ((((uint16_t)instr) & 0x2f) << 0)

#define GET_CC_N(instr) ((((uint16_t)instr) & 0x1) << 11)
#define GET_CC_Z(instr) ((((uint16_t)instr) & 0x1) << 10)
#define GET_CC_P(instr) ((((uint16_t)instr) & 0x1) << 9)

#define GET_TRAPVECT8(instr) ((((uint16_t)instr) & 0xff) << 0)