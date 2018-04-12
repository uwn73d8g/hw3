#ifndef SIMULATOR_PRIVATE_H
#define SIMULATOR_PRIVATE_H


// Instruction formats:
// B:  OP x
//     6  2                [8 bits]
//
// O:  OP  IMMED_10
//     6   10              [16 bits]
//
// R:  OP  RA  RB  RC  x
//     6   3   3   3   1   [16 bits]
//     RA <- RB op RC
//
// RI: OP  RA  RB  IMMED_12
//     6   3   3   12      [24 bits]
//
// LI: OP RA  IMMED_15
//     6  3   15           [24 bits]


// opcode definitions

enum opcodes {
  STOP,          // 000000    B format
  NOP,           // 000001    B format
  
  LW,            // 000010    R format  RA <- Mem[RB + RC]
  LB,            // 000011    
 
  SW,            // 000100    R format: Mem[RB + RC] <- RA
  SB,            // 000101

  ADD,           // 000110    R format:  RA <- RB + RC
  SUB,           // 000111    R format:  RA <- RB - RC
  MUL,           // 001000    R format:  RA <- RB * RC
  DIV,           // 001001               RA <- RB / RC

  ADDI,          // 001010    RI format: RA <- RB op sign_extend(IMMED)

  AND,           // 001011    R format:  RA <- RB & RC
  OR,            // 001100    R format:  RA <- RB | RC
  XOR,           // 001101    R format:  RA <- RB ^ RC

  SHFTL,         // 001110    RI format:  RA <- (RB) << sign_extend(IMMED_12)
  SHFTR,         // 001111      (arithmetic right shift)

  CMP,           // 010000    R format:  CC < (RB) cmp (RC)
  
  BE,            // 010001    O format  [CC:eq] PC <- updated_PC + sign_extend(Immed)
  BLT,           // 010010    O format
  BGT,           // 010011    O format
  JR,            // 010100    R format  PC <- (RB) + (RC)

  CALL,          // 010101    LI format: RA <- PC; PC <- IMMED_15

  PRINTR,        // 010110    R format: print word RA
  PRINTM,        // 010111    R format: print word MEM[(RB) + (RC)]
  PRINTC,        // 011000    R format: print ASCII character  at MEM[(RA) + (RC)]
};



#endif // SIMULATOR_PRIVATE_H
