#ifndef MACHINE_H
#define MACHINE_H

#include <stdio.h>
#include <stdint.h>

#define MEMSIZE (1<<16)
#define NREGISTERS 8

//----------------------------------------------------------
// Here is the machine memory and register configuration.
// These C variables hold values in BIG-ENDIAN format.
// You should NEVER touch them directly.  For that reason,
// their definitions are commented out here. DO NOT UNCOMMENT
// them.
// Use the methods in memRegAccess.h to read and write memory
// and registers
//----------------------------------------------------------

//uint8_t  MEMORY[MEMSIZE];
//int16_t  REGISTER[NREGISTERS];  // R0 is 0

uint16_t PC;
uint8_t  CC;  
enum { CC_EQUAL = 0, CC_LESS = 1, CC_GREATER = 2}; // condition codes

//---------------------------------------------------
// Memory and register set/get macros are in memRegAccess.h.
// You should ALWAYS use those macros.  NEVER touch MEMORY
// or REGISTER variables directly.
//---------------------------------------------------
#include "machineAccess.h"

//---------------------------------------------------
// OPCODE definitions are in opcodes.h
//---------------------------------------------------
#include "opcodes.h"

//---------------------------------------------------
// sets registers, PC, CC, and memory to zeroes
//---------------------------------------------------
void machine_init();

//---------------------------------------------------
// utility routines
//---------------------------------------------------
void machine_dumpMachine(FILE* out);
void machine_dumpReg(FILE *out);
void machine_dumpMem(FILE *out);
void machine_dumpPC(FILE *out);
void machine_dumpCC(FILE *out);


#endif // MACHINE_H
