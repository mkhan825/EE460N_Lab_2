#include <stdint.h>
#include <stdio.h>

#define LSHFT(reg, amt4) (((uint16_t)reg) << amt4)
#define SEXT(val, sig_ext) (((uint16_t)val) | (0 - (((uint16_t)val) & sig_ext)))

int main () {
  uint16_t v = 0;
  uint16_t u = 0x1e;

  v = SEXT(u, 0x10);

  printf("This is the value of v: %x\n", v);

  u = 0x100;
  v = SEXT(u, 0x100);

  printf("This is the value of v: %x\n", v);
}