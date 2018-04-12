#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <stdio.h>
#include <stdint.h>

// prints the disasssembled instruction to file out
// using fprintf(out, ...).  The lower 3 bytes of
// parameter instruction have the 3 bytes of simulated
// machine memory pointed at by the PC.

void disassemble(FILE *out, uint32_t instruction);


#endif // DISASSEMBLER_H
