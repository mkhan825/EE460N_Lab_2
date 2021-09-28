#include <stdint.h>
#include <stdio.h>

#define SEXT(val, sig_ext) (((uint16_t)val) | (0 - (((uint16_t)val) & sig_ext)))

int main () {
  printf("6 ^ -1: %d or %x\n", 6^SEXT(0x1f, 0x10), 6^SEXT(0x1f, 0x10));
  printf("0xFFFF: %x, %d\n", 0xFFFF, (uint16_t)0xFFFF);
}