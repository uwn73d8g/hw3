 //----------------------------------------------------------
// Debugger commands:
//    pm  - print memory
//    pr  - print registers
//    ppc - print pc
//    pcc - print cc
//    pM  - pinter machine
//
//    s  - step
//    c  - continue
//    q  - quit
//----------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debugger.h"
#include "machine.h"

//---------------------------------------
// debugRun()
//   Called by simulator mainline
//   Returns:
//       DEBUGGER_HALT to ask for halt
//       DEBUGGER_STEP to single step
//       DEBUGGER_CONTINUE to continue
//---------------------------------------

Debugger_Rcode debuggerRun() {
  char line[128];
  char *token;
  char *whiteSpace = " \t\n\f\r\v";

  while (1) {
    fprintf(stderr, "debugger 0x%04x> ", PC);
    if ( !fgets(line, 128, stdin) ) return DEBUGGER_HALT;

    for ( token = strtok(line, whiteSpace); token; token = strtok(NULL, whiteSpace) ) {
      if ( !strcmp(token, "s") ) return DEBUGGER_STEP;
      if ( !strcmp(token, "c") ) return DEBUGGER_CONTINUE;
      if ( !strcmp(token, "q") ) return DEBUGGER_HALT;
      
      if ( !strcmp(token, "pm") ) machine_dumpMem(stdout);
      else if ( !strcmp(token, "pr") ) machine_dumpReg(stdout);
      else if ( !strcmp(token, "ppc") ) machine_dumpPC(stdout);
      else if ( !strcmp(token, "pcc") ) machine_dumpCC(stdout);
      else if ( !strcmp(token, "pM") ) machine_dumpMachine(stdout);
      else fprintf(stderr, "Unrecogized debugger command ignored: '%s'\n", token);
    }
  }
  return DEBUGGER_STEP;
}

