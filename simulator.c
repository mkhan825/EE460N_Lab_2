#include <stdio.h>
#include <string.h>
#include "simulator.h"
#include <stdint.h>

uint8_t MEMORY[MAX_MEM_LOCATIONS][2];

void
run() {
  if (strcmp()) {

  }
}

int main (int argc, char* argv[]) {
  if (argc < 2) { // todo: not sure if this should be < 3
    printf("Incorrect amount of parameters given to program!\n");
  }

  /* open the source file */
  FILE* infile = fopen(argv[1], "r");
  // FILE* outfile = fopen(oFileName, "w");

  run();
}