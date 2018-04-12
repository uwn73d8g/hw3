#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main() {
  int64_t num = 0x0102030405060708;

  printf("%p: %lx\n", &num, *&num);

  char *pc = (char*)&num;
  for (int i=0; i<8; i++) printf("%p: %x\n", &pc[i], pc[i]);

  int *pi = (int*)&num;
  for (int j=0; j<2; j++) printf("%p: %x\n", &pi[j], pi[j]);

  int64_t little = 0;
  int64_t big = 0;
  pc = (char*)&num;
  for (int k=0; k<8; k++) {
    little = (((int64_t)pc[k]) << 8*k) | little;
  }
  for (int k=0; k<8; k++) {
    big = (big << 8) | pc[k];
  }
  printf("num/little/big:  %0lx / %0lx  / %0lx\n", num, little, big);

  return 0;
}
