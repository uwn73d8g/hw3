#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "machine.h"
#include "simulator.h"
#include "loader.h"
#include "debugger.h"

void usage(const char *exeName) {
  fprintf(stderr, "Usage: %s  [-n] filename ...\n", exeName);
  fprintf(stderr, "  Options:\n");
  fprintf(stderr, "     -n\tDo not invoke the debugger.\n");
  exit(1);
}

int main(int argc, char *argv[]) {

  //------------------------------
  // process options
  //------------------------------

  int opt;
  bool debug = true;
  while ((opt = getopt(argc, argv, "n")) != -1) {
    switch (opt) {
    case 'n':
      debug = false;
      break;
    default: usage(argv[0]);
    }
  }

  if (optind >= argc) usage(argv[0]);
  
  //------------------------------
  // set machine to known state (all zeroes)
  //------------------------------

  machine_init();


  //------------------------------
  // load all exe files
  //------------------------------

  for ( char** pArg = &argv[optind]; *pArg; pArg++ ) {
  
    FILE *exeFile = fopen(*pArg, "r");
    if ( exeFile == NULL ) {
      fprintf(stderr, "Can't open %s\n", *pArg);
      exit(2);
    }
  
    int rcode = loader(exeFile);
    if ( rcode != 0 ) {
      fprintf(stderr, "Loader failed on %s with code %d\n", *pArg, rcode);
      exit(3);
    }
    fclose(exeFile);
  }

  //------------------------------
  // run simulator
  //------------------------------
  
  simRun(debug);
  
  return EXIT_SUCCESS;
}
