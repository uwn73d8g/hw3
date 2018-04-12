#include <stdio.h>

//----------------------------------------------------------
// Prints hex for strings given as command line arguments.
//Example invocation:
// $ ./stringToHex 'Test string' 'Another string'
//----------------------------------------------------------

int main(int argc, char *argv[]) {
  for (char **pArg = &argv[1]; *pArg; pArg++ ) {
    printf("%s => ", *pArg);
    int space = 0;
    for (char *pc=*pArg; *pc; pc++, space++ ) {
      if (space %2 == 0 ) printf(" ");
      printf("%x", *pc);
    }
    printf("00\n");  // print string terminator '\0'
  }
  return 0;
  
}
