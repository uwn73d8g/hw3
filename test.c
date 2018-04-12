#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main() {
  int8_t x = -10, y = 100;
  uint8_t ux = x, uy = 100;

  int16_t big = ux;
  int16_t big2 = x;

  uint16_t resultUnsigned = ((int16_t)ux) + ((int16_t)uy);
  int16_t  resultSigned = ((int16_t)ux) + ((int16_t)uy);

  printf("ux uy = %x  %x\n", x, y);
  printf("ux uy = %d  %d\n", x, y);
  printf("ux+uy = %x %d\n", ux+uy, ux+uy);
  printf("ux+uy = %x %d\n", ((int8_t)ux)+((int8_t)uy), ((int8_t)ux)+((int8_t)uy));

  printf("%d\n", y/x);

  ux = x;
  uy = y;

  printf("\n%u\n", uy/ux);
  printf("%d\n", (unsigned int)y/x);


  memcpy(&ux, &x, 2);
  memcpy(&uy, &y, 2);

  printf("\n%u\n", ((int)uy)/((int)ux));
  printf("%d\n", (unsigned int)y/x);

  int32_t  si = -1;
  uint32_t ui = si;
  printf("\nui = %u\n", ui);

  return 0;
}
  
