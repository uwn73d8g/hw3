#include "machine.h"

//---------------------------------------------------
// Sets all machine components to zeroes
//---------------------------------------------------
void machine_init() {
  PC = 0x0010;  // default entry point
  CC = 0;
  for (int r=0; r<8; r++) setReg(r, 0);
  for (int addr=0; addr<MEMSIZE; addr++) storeMemByte(addr,0);
}

//---------------------------------------------------
// Prints contents of memory to file stream out
//---------------------------------------------------
void machine_dumpMem(FILE *out) {

  typedef enum state { start, hadZero, hadZeroes } State;
  State state = start;
  
  fprintf(out, "  Memory:\n");

  for ( uint32_t loc = 0; loc < 0x00010000u; loc += 2 ) {
    
    if ( fetchMemByte(loc) == 0 && fetchMemByte(loc+1) == 0 && loc != MEMSIZE-2) {
      if ( state == hadZero ) {
	fprintf(out, "\t0x%04x:   ...\n", loc);
	state = hadZeroes;
	continue;
      }
      else if ( state == hadZeroes) continue;
      state = hadZero;
    }
    else state = start;
    fprintf(out, "\t0x%04x:   0x%02x%02x\n", loc, fetchMemByte(loc), fetchMemByte(loc+1) );
  }

}

//---------------------------------------------------
// dumpReg()
//---------------------------------------------------
void machine_dumpReg(FILE *out) {
  fprintf(out, "  Registers:\n");
  fprintf(out, "    ");
  for (uint8_t r=0; r<NREGISTERS; r++) {
    fprintf(out, "       [%1x]", r);
  }
  fprintf(out, "\n    ");
  for (uint8_t r=0; r<NREGISTERS; r++) {
    fprintf(out, "    0x%04x", getRegUnsigned(r));
  }
  fprintf(out, "\n");
}

//---------------------------------------------------
// dumpReg()
//---------------------------------------------------
void machine_dumpPC(FILE *out) {
  fprintf(out, "  PC:\t0x%04x\n", PC);
}

//---------------------------------------------------
// dumpCC()
//---------------------------------------------------
void machine_dumpCC(FILE *out) {
  fprintf(out, "  CC:\t0x%02x\n", CC);
}

//---------------------------------------------------
// dumpMachine()
//---------------------------------------------------
void machine_dumpMachine(FILE *out) {
  fprintf(out, "\nMachine State:\n");
  machine_dumpPC(out);
  machine_dumpCC(out);
  machine_dumpReg(out);
  machine_dumpMem(out);
}
