/*
    Remove all unnecessary lines (including this one) 
    in this comment.
    REFER TO THE SUBMISSION INSTRUCTION FOR DETAILS

    Name 1: Masaad Khan
    Name 2: Rithvik Dyava
    UTEID 1: UT EID of the first partner
    UTEID 2: UT EID of the second partner
*/

/***************************************************************/
/*                                                             */
/*   LC-3b Instruction Level Simulator                         */
/*                                                             */
/*   EE 460N                                                   */
/*   The University of Texas at Austin                         */
/*                                                             */
/***************************************************************/

#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lc3bsim2.h"

/***************************************************************/
/*                                                             */
/* Files: isaprogram   LC-3b machine language program file     */
/*                                                             */
/***************************************************************/

/***************************************************************/
/* These are the functions you'll have to write.               */
/***************************************************************/

void process_instruction(void);

/***************************************************************/
/* Main memory.                                                */
/***************************************************************/

uint8_t MEMORY[WORDS_IN_MEM][2];

/***************************************************************/
/* LC-3b State info.                                           */
/***************************************************************/

bool RUN_BIT;	/* run bit */

struct System_Latches CURRENT_LATCHES;
struct System_Latches NEXT_LATCHES;

/***************************************************************/
/* A cycle counter.                                            */
/***************************************************************/
int INSTRUCTION_COUNT; // todo: look at this in depth later

/***************************************************************/
/*                                                             */
/* Procedure : help                                            */
/*                                                             */
/* Purpose   : Print out a list of commands                    */
/*                                                             */
/***************************************************************/
void help() {                                                    
  printf("----------------LC-3b ISIM Help-----------------------\n");
  printf("go               -  run program to completion         \n");
  printf("run n            -  execute program for n instructions\n");
  printf("mdump low high   -  dump memory from low to high      \n");
  printf("rdump            -  dump the register & bus values    \n");
  printf("?                -  display this help menu            \n");
  printf("quit             -  exit the program                  \n\n");
}

/***************************************************************/
/*                                                             */
/* Procedure : cycle                                           */
/*                                                             */
/* Purpose   : Execute a cycle                                 */
/*                                                             */
/***************************************************************/
void cycle() {                                                
  process_instruction();
  CURRENT_LATCHES = NEXT_LATCHES;
  INSTRUCTION_COUNT++;
}

/***************************************************************/
/*                                                             */
/* Procedure : run n                                           */
/*                                                             */
/* Purpose   : Simulate the LC-3b for n cycles                 */
/*                                                             */
/***************************************************************/
void run(int num_cycles) {                                      
  int i;

  if (RUN_BIT == false) {
    printf("Can't simulate, Simulator is halted\n\n");
    return;
  }

  printf("Simulating for %d cycles...\n\n", num_cycles);
  for (i = 0; i < num_cycles; i++) {
    if (CURRENT_LATCHES.PC == 0x0000) {
	    RUN_BIT = false;
	    printf("Simulator halted\n\n");
	    break;
    }
    cycle();
  }
}

/***************************************************************/
/*                                                             */
/* Procedure : go                                              */
/*                                                             */
/* Purpose   : Simulate the LC-3b until HALTed                 */
/*                                                             */
/***************************************************************/
void go() {                                                     
  if (RUN_BIT == false) {
    printf("Can't simulate, Simulator is halted\n\n");
    return;
  }

  printf("Simulating...\n\n");
  while (CURRENT_LATCHES.PC != 0x0000)
    cycle();
  RUN_BIT = false;
  printf("Simulator halted\n\n");
}

/***************************************************************/ 
/*                                                             */
/* Procedure : mdump                                           */
/*                                                             */
/* Purpose   : Dump a word-aligned region of memory to the     */
/*             output file.                                    */
/*                                                             */
/***************************************************************/
void mdump(FILE * dumpsim_file, int start, int stop) {          
  int address; /* this is a byte address */

  printf("\nMemory content [0x%.4x..0x%.4x] :\n", start, stop);
  printf("-------------------------------------\n");
  for (address = (start >> 1); address <= (stop >> 1); address++)
    printf("  0x%.4x (%d) : 0x%.2x%.2x\n", address << 1, address << 1, MEMORY[address][1], MEMORY[address][0]);
  printf("\n");

  /* dump the memory contents into the dumpsim file */
  fprintf(dumpsim_file, "\nMemory content [0x%.4x..0x%.4x] :\n", start, stop);
  fprintf(dumpsim_file, "-------------------------------------\n");
  for (address = (start >> 1); address <= (stop >> 1); address++)
    fprintf(dumpsim_file, " 0x%.4x (%d) : 0x%.2x%.2x\n", address << 1, address << 1, MEMORY[address][1], MEMORY[address][0]);
  fprintf(dumpsim_file, "\n");
  fflush(dumpsim_file);
}

/***************************************************************/
/*                                                             */
/* Procedure : rdump                                           */
/*                                                             */
/* Purpose   : Dump current register and bus values to the     */   
/*             output file.                                    */
/*                                                             */
/***************************************************************/
void rdump(FILE * dumpsim_file) {                               
  int k; 

  printf("\nCurrent register/bus values :\n");
  printf("-------------------------------------\n");
  printf("Instruction Count : %d\n", INSTRUCTION_COUNT);
  printf("PC                : 0x%.4x\n", CURRENT_LATCHES.PC);
  printf("CCs: N = %d  Z = %d  P = %d\n", CURRENT_LATCHES.N, CURRENT_LATCHES.Z, CURRENT_LATCHES.P);
  printf("Registers:\n");
  for (k = 0; k < MAX_NUM_REGS; k++)
    printf("%d: 0x%.4x\n", k, CURRENT_LATCHES.REGS[k]);
  printf("\n");

  /* dump the state information into the dumpsim file */
  fprintf(dumpsim_file, "\nCurrent register/bus values :\n");
  fprintf(dumpsim_file, "-------------------------------------\n");
  fprintf(dumpsim_file, "Instruction Count : %d\n", INSTRUCTION_COUNT);
  fprintf(dumpsim_file, "PC                : 0x%.4x\n", CURRENT_LATCHES.PC);
  fprintf(dumpsim_file, "CCs: N = %d  Z = %d  P = %d\n", CURRENT_LATCHES.N, CURRENT_LATCHES.Z, CURRENT_LATCHES.P);
  fprintf(dumpsim_file, "Registers:\n");
  for (k = 0; k < MAX_NUM_REGS; k++)
    fprintf(dumpsim_file, "%d: 0x%.4x\n", k, CURRENT_LATCHES.REGS[k]);
  fprintf(dumpsim_file, "\n");
  fflush(dumpsim_file);
}

/***************************************************************/
/*                                                             */
/* Procedure : get_command                                     */
/*                                                             */
/* Purpose   : Read a command from standard input.             */  
/*                                                             */
/***************************************************************/
void get_command(FILE * dumpsim_file) {                         
  char buffer[20];
  int start, stop, cycles;

  printf("LC-3b-SIM> ");

  scanf("%s", buffer);
  printf("\n");

  switch(buffer[0]) {
  case 'G':
  case 'g':
    go();
    break;

  case 'M':
  case 'm':
    scanf("%i %i", &start, &stop);
    mdump(dumpsim_file, start, stop);
    break;

  case '?':
    help();
    break;
  case 'Q':
  case 'q':
    printf("Bye.\n");
    exit(0);

  case 'R':
  case 'r':
    if (buffer[1] == 'd' || buffer[1] == 'D')
	    rdump(dumpsim_file);
    else {
	    scanf("%d", &cycles);
	    run(cycles);
    }
    break;

  default:
    printf("Invalid Command\n");
    break;
  }
}

/***************************************************************/
/*                                                             */
/* Procedure : init_memory                                     */
/*                                                             */
/* Purpose   : Zero out the memory array                       */
/*                                                             */
/***************************************************************/
void init_memory() {                                           
  int i;

  for (i=0; i < WORDS_IN_MEM; i++) {
    MEMORY[i][0] = 0;
    MEMORY[i][1] = 0;
  }
}

/**************************************************************/
/*                                                            */
/* Procedure : load_program                                   */
/*                                                            */
/* Purpose   : Load program and service routines into mem.    */
/*                                                            */
/**************************************************************/
void load_program(char *program_filename) {                   
  FILE * prog;
  int ii, word, program_base;

  /* Open program file. */
  prog = fopen(program_filename, "r");
  if (prog == NULL) {
    printf("Error: Can't open program file %s\n", program_filename);
    exit(-1);
  }

  /* Read in the program. */
  if (fscanf(prog, "%x\n", &word) != EOF)
    program_base = word >> 1;
  else {
    printf("Error: Program file is empty\n");
    exit(-1);
  }

  ii = 0;
  while (fscanf(prog, "%x\n", &word) != EOF) {
    /* Make sure it fits. */
    if (program_base + ii >= WORDS_IN_MEM) {
	    printf("Error: Program file %s is too long to fit in memory. %x\n",
             program_filename, ii);
	    exit(-1);
    }

    /* Write the word to memory array. */ // todo: make sure that this is working right
    printf("Made it here, program_base: %x, %d\n", program_base, ii);
    MEMORY[program_base + ii][0] = word & 0x00FF;
    MEMORY[program_base + ii][1] = (word >> 8) & 0x00FF;
    ii++;
  }

  if (CURRENT_LATCHES.PC == 0) CURRENT_LATCHES.PC = (program_base << 1);

  printf("Read %d words from program into memory.\n\n", ii);
}

/************************************************************/
/*                                                          */
/* Procedure : initialize                                   */
/*                                                          */
/* Purpose   : Load machine language program                */ 
/*             and set up initial state of the machine.     */
/*                                                          */
/************************************************************/
void initialize(char *program_filename, int num_prog_files) { 
  int i;

  init_memory();
  for ( i = 0; i < num_prog_files; i++ ) {
    load_program(program_filename);
    while(*program_filename++ != '\0');
  }
  CURRENT_LATCHES.Z = 1;  
  NEXT_LATCHES = CURRENT_LATCHES;
    
  RUN_BIT = true;
}

/***************************************************************/
/*                                                             */
/* Procedure : main                                            */
/*                                                             */
/***************************************************************/
int main(int argc, char *argv[]) {                              
  FILE * dumpsim_file;

  /* Error Checking */
  if (argc < 2) {
    printf("Error: usage: %s <program_file_1> <program_file_2> ...\n",
           argv[0]);
    exit(1);
  }

  printf("LC-3b Simulator\n\n");

  initialize(argv[1], argc - 1);

  if ( (dumpsim_file = fopen( "dumpsim", "w" )) == NULL ) {
    printf("Error: Can't open dumpsim file\n");
    exit(-1);
  }

  while (1)
    get_command(dumpsim_file);
    
}

/***************************************************************/
/* Do not modify the above code.
   You are allowed to use the following global variables in your
   code. These are defined above.

   MEMORY

   CURRENT_LATCHES
   NEXT_LATCHES

   You may define your own local/global variables and functions.
   You may use the functions to get at the control bits defined
   above.

   Begin your code here 	  			       */

/***************************************************************/

char* opcode_str[] = {"branch", "add", "ldb", "stb", "jsr_jsrr", "and", "ldw", 
                      "stw", "invalid", "xor_not", "invalid", "invalid", "jmp_ret",
                      "shft", "lea", "trap"};

int
power(int value, int exponent) {
  int sum = value;
  for (int i = exponent; i >= 2; i--) {
    sum = sum*value;
  }
  return sum;
}

void
CHECK_IMM5(int16_t IMM5) {
  if (IMM5 > (power(2, 4) - 1)) {
    /* IMM5 is greater than the max positive value */
    #if (TEST || DEBUG)
    printf("IMM5 %d is too big!\n", IMM5);
    printf("Error Code: %d\n", 3);
    #endif

    exit(3);
  } else if (IMM5 < (-power(2,4))) {
    /* IMM5 is smaller than the most negative value */
    #if (TEST || DEBUG)
    printf("IMM5 %d is too small!\n", IMM5);
    printf("Error Code: %d\n", 3);
    #endif

    exit(3);
  }
}

void
CHECK_PCOFFSET9(int16_t PC_OFFSET9) {
  if (PC_OFFSET9 > (power(2, 8) - 1)) {
    /* PC offset is greater than the max positive value */
    #if (TEST || DEBUG)
    printf("PC_OFFSET9 %d is too big!\n", PC_OFFSET9);
    printf("Error Code: %d\n", 4);
    #endif

    exit(4);
  } else if (PC_OFFSET9 < (-power(2,8))) {
    /* PC offset is smaller than the most negative value */
    #if (TEST || DEBUG)
    printf("PC_OFFSET9 %d is too small!\n", PC_OFFSET9);
    printf("Error Code: %d\n", 4);
    #endif

    exit(4);
  }
}

void
CHECK_PCOFFSET11(int16_t PC_OFFSET11) {
  if (PC_OFFSET11 > (power(2, 10) - 1)) {
    /* PC offset is greater than the max positive value */
    #if (TEST || DEBUG)
    printf("PC_OFFSET11 %d is too big!\n", PC_OFFSET11);
    printf("Error Code: %d\n", 4);
    #endif

    exit(4);
  } else if (PC_OFFSET11 < (-power(2,10))) {
    /* PC offset is smaller than the most negative value */
    #if (TEST || DEBUG)
    printf("PC_OFFSET11 %d is too small!\n", PC_OFFSET11);
    printf("Error Code: %d\n", 4);
    #endif

    exit(4);
  }
}

void
CHECK_BOFFSET6(int16_t BOFFSET6) {
  if (BOFFSET6 > (power(2, 5) - 1)) {
    /* BOFFSET6 is greater than the max positive value */
    #if (TEST || DEBUG)
    printf("BOFFSET6 %d is too big!\n", BOFFSET6);
    printf("Error Code: %d\n", 3);
    #endif

    exit(3);
  } else if (BOFFSET6 < (-power(2,5))) {
    /* BOFFSET6 is smaller than the most negative value */
    #if (TEST || DEBUG)
    printf("BOFFSET6 %d is too small!\n", BOFFSET6);
    printf("Error Code: %d\n", 3);
    #endif

    exit(3);
  }
}

void
CHECK_OFFSET6(int16_t OFFSET6) {
  if (OFFSET6 > (power(2, 5) - 1)) {
    /* OFFSET6 is greater than the max positive value */
    #if (TEST || DEBUG)
    printf("OFFSET6 %d is too big!\n", OFFSET6);
    printf("Error Code: %d\n", 3);
    #endif

    exit(3);
  } else if (OFFSET6 < (-power(2,5))) {
    /* OFFSET6 is smaller than the most negative value */
    #if (TEST || DEBUG)
    printf("OFFSET6 %d is too small!\n", OFFSET6);
    printf("Error Code: %d\n", 3);
    #endif

    exit(3);
  }
}

void
CHECK_AMOUNT4(int16_t AMOUNT4) {
  if (AMOUNT4 > (power(2, 4) - 1)) {
    /* AMOUNT4 is greater than the max positive value */
    #if (TEST || DEBUG)
    printf("AMOUNT4 %d is too big!\n", AMOUNT4);
    printf("Error Code: %d\n", 3);
    #endif

    exit(3);

  } else if (AMOUNT4 < 0) {
    /* AMOUNT4 cannot be negative */
    #if (TEST || DEBUG)
    printf("AMOUNT4 %d cannot be negative!\n", AMOUNT4);
    printf("Error Code: %d\n", 3);
    #endif

    exit(3);
  }
}

void
CHECK_TRAPVECT8(int16_t TRAPVECT8) {
  if (TRAPVECT8 > (power(2, 8) - 1)) {
    /* TRAPVECT8 is greater than the max positive value */
    #if (TEST || DEBUG)
    printf("TRAPVECT8 %d is too big!\n", TRAPVECT8);
    printf("Error Code: %d\n", 3);
    #endif

    exit(3);
  } else if (TRAPVECT8 < 0) {
    /* TRAPVECT8 cannot be a negative value */
    #if (TEST || DEBUG)
    printf("TRAPVECT8 %d cannot be negative!\n", TRAPVECT8);
    printf("Error Code: %d\n", 3);
    #endif

    exit(3);
  }
}


void
update_cc(int16_t value) {
  if (value < 0) {
    NEXT_LATCHES.N = true;
    NEXT_LATCHES.P = false;
    NEXT_LATCHES.Z = false;
  } else if (value > 0) {
    NEXT_LATCHES.N = false;
    NEXT_LATCHES.P = true;
    NEXT_LATCHES.Z = false;
  } else {
    NEXT_LATCHES.N = false;
    NEXT_LATCHES.P = false;
    NEXT_LATCHES.Z = true;
  }
}

// todo: what if there is self-modifying code that changes the assembly
void
add_instr(uint16_t instr) {
  // if (GET_DR(instr)) {
    
  // }
  if (GET_IMM_OR_REG_B5(instr) == REGISTER) {
    NEXT_LATCHES.REGS[GET_DR(instr)] = CURRENT_LATCHES.REGS[GET_SR1(instr) + CURRENT_LATCHES.REGS[GET_SR2(instr)]];
  } else {
    NEXT_LATCHES.REGS[GET_DR(instr)] = CURRENT_LATCHES.REGS[GET_SR1(instr)] + SEXT(GET_IMM5(instr), 0x10);
  }

  update_cc(NEXT_LATCHES.REGS[GET_DR(instr)]);
}

void
and_instr(uint16_t instr) {
  if (GET_IMM_OR_REG_B5(instr) == REGISTER){
    NEXT_LATCHES.REGS[GET_DR(instr)] = CURRENT_LATCHES.REGS[GET_SR1(instr) & CURRENT_LATCHES.REGS[GET_SR2(instr)]];
  } else {
    NEXT_LATCHES.REGS[GET_DR(instr)] = CURRENT_LATCHES.REGS[GET_SR1(instr)] & SEXT(GET_IMM5(instr), 0x10);
  }

  update_cc(NEXT_LATCHES.REGS[GET_DR(instr)]);
}

void
br_instr(uint16_t instr) {
  bool BEN = (GET_CC_N(instr) && CURRENT_LATCHES.N) ||
             (GET_CC_Z(instr) && CURRENT_LATCHES.Z) ||
             (GET_CC_P(instr) && CURRENT_LATCHES.P);

  if (BEN) {
    NEXT_LATCHES.PC = NEXT_LATCHES.PC + LSHIFT(SEXT(GET_PCOFFSET9(instr), 0x100));
  } else {
    // todo: double check that you do nothing here...
  }
}

void
jmp_ret_instr(uint16_t instr) {
  // todo: check for valid PC
  uint16_t jmp_pc = GET_BASE_R(instr);
  CHECK_VALID_PC(jmp_pc);
  NEXT_LATCHES.PC = jmp_pc;
}

void
jsr_jsrr_instr(uint16_t instr) {
  if(GET_IMM_OR_REG_B11(instr) == REGISTER){
    NEXT_LATCHES.PC = NEXT_LATCHES.REGS[GET_BASE_R(instr)];
  }
  else{
    NEXT_LATCHES.PC += LSHIFT(SEXT(GET_PCOFFSET11(instr), 0x400));
  }
}

void
ldb_instr(uint16_t instr) {
  // todo: ig we should always be checking for bad pc values in OS, etc
  uint16_t addr = ADDRESS(CURRENT_LATCHES.REGS[GET_BASE_R(instr)] + SEXT(GET_BOFFSET6(instr), 0x20));
  printf("Check LDB whether we are SEXT this properly\n");
  printf("Value: %x vs %x\n", SEXT(SET_MEMORY(MEMORY[addr][1], MEMORY[addr][0]), 0x8000), (int16_t)SET_MEMORY(MEMORY[addr][1], MEMORY[addr][0]));
  NEXT_LATCHES.REGS[GET_DR(instr)] = SEXT(SET_MEMORY(MEMORY[addr][1], MEMORY[addr][0]), 0x8000);
  update_cc(NEXT_LATCHES.REGS[GET_DR(instr)]);
}

void
ldw_instr(uint16_t instr) {
  uint16_t addr = ADDRESS(CURRENT_LATCHES.REGS[GET_BASE_R(instr)] + SEXT(GET_OFFSET6(instr), 0x20));
  NEXT_LATCHES.REGS[GET_DR(instr)] = SEXT(SET_MEMORY(MEMORY[addr][1], MEMORY[addr][0]), 0x8000);
  update_cc(NEXT_LATCHES.REGS[GET_DR(instr)]);
}

void
lea_instr(uint16_t instr) {
  NEXT_LATCHES.REGS[GET_DR(instr)] = NEXT_LATCHES.PC + LSHIFT(SEXT(GET_PCOFFSET9(instr), 0x100));
}

void
shft_instr(uint16_t instr) {
  // todo: do we check for negative shift amt
  if (GET_SHF_TYPE(instr) == LSHF) {
    NEXT_LATCHES.REGS[GET_DR(instr)] = LSHFT(CURRENT_LATCHES.REGS[GET_SR(instr)], GET_AMOUNT4(instr));
  } else if (GET_SHF_TYPE(instr) == RSHFL) {
    // todo: check logical right shift
    NEXT_LATCHES.REGS[GET_DR(instr)] = RSHFTL(CURRENT_LATCHES.REGS[GET_SR(instr)], GET_AMOUNT4(instr));
  } else if (GET_SHF_TYPE(instr) == RSHFA) {
    // todo: check arithmetic right shift
    NEXT_LATCHES.REGS[GET_DR(instr)] = RSHFTA(CURRENT_LATCHES.REGS[GET_SR(instr)], GET_AMOUNT4(instr));
  }

  update_cc(NEXT_LATCHES.REGS[GET_DR(instr)]);
}

void
stb_instr(uint16_t instr) {
  uint16_t addr = ADDRESS(CURRENT_LATCHES.REGS[GET_BASE_R(instr)] + SEXT(GET_BOFFSET6(instr), 0x20));

  if ((addr % 2) == 0) {
    MEMORY[addr][0] = CURRENT_LATCHES.REGS[GET_SR(instr)];
  } else {
    MEMORY[addr][1] = CURRENT_LATCHES.REGS[GET_SR(instr)];
  }
    
}

void
stw_instr(uint16_t instr) {
  // todo: ctrl + f make sure all next regs are on the left operands
  // todo: fix this command
  uint16_t addr = ADDRESS(CURRENT_LATCHES.REGS[GET_BASE_R(instr)] + LSHIFT(SEXT(GET_OFFSET6(instr), 0x20)));
  MEMORY[addr][0] = CURRENT_LATCHES.REGS[GET_SR(instr)] & 0xFF;
  MEMORY[addr][1] = (CURRENT_LATCHES.REGS[GET_SR(instr)] & 0xFF00) >> 8;
  // ((uint16_t*)(&MEMORY[addr][0]))[0] = 
}

void
trap_instr(uint16_t instr) {
  // RUN_BIT = false; // todo: check for trap x25 (HALT)

  NEXT_LATCHES.REGS[7] = NEXT_LATCHES.PC;
  uint16_t addr = ADDRESS(LSHIFT(ZEXT(GET_TRAPVECT8(instr))));
  NEXT_LATCHES.PC = SET_MEMORY(MEMORY[addr][1], MEMORY[addr][0]); //todo: zext
}

void
xor_not_instr(uint16_t instr) {
  if (GET_IMM_OR_REG_B5(instr) == REGISTER) {
    NEXT_LATCHES.REGS[GET_DR(instr)] = CURRENT_LATCHES.REGS[GET_SR1(instr) ^ CURRENT_LATCHES.REGS[GET_SR2(instr)]];
  } else {
    NEXT_LATCHES.REGS[GET_DR(instr)] = CURRENT_LATCHES.REGS[GET_SR1(instr)] ^ SEXT(GET_IMM5(instr), 0x10);
  }

  update_cc(NEXT_LATCHES.REGS[GET_DR(instr)]);
}

void process_instruction(void){
  /*  function: process_instruction
   *  
   *    Process one instruction at a time  
   *       -Fetch one instruction
   *       -Decode 
   *       -Execute
   *       -Update NEXT_LATCHES
   */     

  printf("Current PC: 0x%X\n", CURRENT_LATCHES.PC);
  printf("Instruction: %x%x\n", MEMORY[ADDRESS(CURRENT_LATCHES.PC)][1], MEMORY[ADDRESS(CURRENT_LATCHES.PC)][0]);
  NEXT_LATCHES.PC += 2;

  uint16_t instruction = SET_MEMORY(MEMORY[ADDRESS(CURRENT_LATCHES.PC)][1], MEMORY[ADDRESS(CURRENT_LATCHES.PC)][0]);

  printf("Going into instruction %s\n", opcode_str[GET_OPCODE(instruction)]);
  if (GET_OPCODE(instruction) == ADD) {
    add_instr(instruction);
  } else if (GET_OPCODE(instruction) == AND) {
    and_instr(instruction);
  } else if (GET_OPCODE(instruction) == BR) {
    br_instr(instruction);
  } else if (GET_OPCODE(instruction) == JMP_RET) {
    jmp_ret_instr(instruction);
  } else if (GET_OPCODE(instruction) == JSR_JSRR) {
    jsr_jsrr_instr(instruction);
  } else if (GET_OPCODE(instruction) == LDB) {
    ldb_instr(instruction);
  } else if (GET_OPCODE(instruction) == LDW) {
    ldw_instr(instruction);
  } else if (GET_OPCODE(instruction) == LEA) {
    lea_instr(instruction);
  } else if (GET_OPCODE(instruction) == SHFT) {
    shft_instr(instruction);
  } else if (GET_OPCODE(instruction) == STB) {
    stb_instr(instruction);
  } else if (GET_OPCODE(instruction) == STW) {
    stw_instr(instruction);
  } else if (GET_OPCODE(instruction) == TRAP) {
    trap_instr(instruction);
  } else if (GET_OPCODE(instruction) == XOR_NOT) {
    xor_not_instr(instruction);
  } else {
    printf("Found invalid instruction: %x!\n", GET_OPCODE(instruction));
  }
}