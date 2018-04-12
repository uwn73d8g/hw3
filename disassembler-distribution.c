#include "disassembler.h"
#include "machine.h"

// Prints the disasssembled instruction to file out
// using fprintf(out, ...).  The lower 3 bytes of
// parameter instruction have the 3 bytes of simulated
// machine memory pointed at by the PC.

void disassemble(FILE *out, uint32_t instruction) {

  //---------------------------------------------------
  // Step 3
  //   When the simualtor is in debug mode, this method
  //   is called each time a new instruction is fetched.
  //   The goal is to print a readable form of the instruction.
  //   The readable form is created by looking at the bit
  //   string representation of the instruction (held in
  //   parameter instruction) and "disassembling" it.
  //
  //   Run the solution executable for an example of what you might
  //   print here.
  //
  //  Hint 1: You'll need your step 1 code.
  //  Hint 2: The overall structure of the code here
  //          is very similar to the code in simulator-distribution.c
  //---------------------------------------------------
    uint8_t  OP = instruction>>18;
    uint8_t  RA = (instruction>>15)&7;
    uint8_t  RB = (instruction>>12)&7;
    uint8_t  RC = (instruction>>9)&7;
    int16_t  IMMED_10 = (instruction>>8)&1023;
    int16_t  IMMED_12 = instruction&4095;
    int16_t  IMMED_15 = instruction&32767;

    
    switch (OP) {
        case STOP:
            fprintf("[0x%04x]: 0x%0x\n  STOP");
            break;
            
        case NOP:
            fprintf("[0x%04x]: 0x%0x\n  NOP");
            break;
            
        case LW:
            fprintf("[0x%04x]: 0x%0x\n  LW  r%d  r%d  r%d", RA, RB, RC);
            break;
            
        case LB:
            fprintf("[0x%04x]: 0x%0x\n  LB  r%d  r%d  r%d", RA, RB, RC);

            break;
            
        case SW:
            fprintf("[0x%04x]: 0x%0x\n  SW  r%d  r%d  r%d", RA, RB, RC);

            break;
            
        case SB:
            fprintf("[0x%04x]: 0x%0x\n  SB  r%d  r%d  r%d", RA, RB, RC);
            break;
            
        case ADD:
            fprintf("[0x%04x]: 0x%0x\n  ADD  r%d  r%d  r%d", RA, RB, RC);
            break;
            
        case SUB:
            fprintf("[0x%04x]: 0x%0x\n  SUB  r%d  r%d  r%d", RA, RB, RC);
            break;
            
        case MUL:
            fprintf("[0x%04x]: 0x%0x\n  MUL  r%d  r%d  r%d", RA, RB, RC);
            break;
            
        case DIV:
            fprintf("[0x%04x]: 0x%0x\n  DIV  r%d  r%d  r%d", RA, RB, RC);
            break;
            
        case ADDI:
            fprintf("[0x%04x]: 0x%0x\n  ADDI  r%d  r%d  %d", RA, RB, IMMED_10);
            break;
            
        case AND:
            fprintf("[0x%04x]: 0x%0x\n  AND  r%d  r%d  r%d", RA, RB, RC);
            break;
            
        case OR:
            fprintf("[0x%04x]: 0x%0x\n  OR  r%d  r%d  r%d", RA, RB, RC);
            break;
            
        case XOR:
            fprintf("[0x%04x]: 0x%0x\n  XOR  r%d  r%d  r%d", RA, RB, RC);
            break;
            
        case SHFTL:
            fprintf("[0x%04x]: 0x%0x\n  SHFTL  r%d  r%d  %d", RA, RB, IMMED_12);
            break;
            
        case SHFTR:
            fprintf("[0x%04x]: 0x%0x\n  SHFTR  r%d  r%d  %d", RA, RB, IMMED_10);
            break;
            
        case CMP:
            fprintf("[0x%04x]: 0x%0x\n  CMP  r%d  r%d  r%d", RA, RB, RC);
            break;
            
        case BE:
            fprintf("[0x%04x]: 0x%0x\n  BE  %d", IMMED_10);
            break;
            
        case BLT:
            fprintf("[0x%04x]: 0x%0x\n  BLT  %d", IMMED_10);
            break;
            
        case BGT:
            fprintf("[0x%04x]: 0x%0x\n  BGT  %d", IMMED_10);
            break;
            
        case JR:
            fprintf("[0x%04x]: 0x%0x\n  JR  r%d  r%d  r%d", RA, RB, RC);
            break;
            
        case CALL:
            fprintf("[0x%04x]: 0x%0x\n  CALL  r%d  %d", RA, IMMED_15);
            break;
            
        case PRINTR:
            fprintf("[0x%04x]: 0x%0x\n  PRINTR  r%d  r%d  r%d", RA, RB, RC);
            break;
            
        case PRINTM:
            fprintf("[0x%04x]: 0x%0x\n  PRINTM  r%d  r%d  r%d", RA, RB, RC);
            break;
            
            
        case PRINTC:
            fprintf("[0x%04x]: 0x%0x\n  PRINTC  r%d  r%d  r%d", RA, RB, RC);

            break;
            
        default:
//            printf("@ 0x%04x\tMachine check: invalid opcode: 0x%0x\n");
            fprintf("");
        }
    }

    
  // The fprintf "format string" is just a string with
  // format specifications mixed in.  The "just a string"
  // part is printed.  The format specifications are how to
  // print the value of a variable.
  // In this example, %04x and %0x are the format specifications.
  // They are matched to the values given as arguments (PC and
  // instruction) in order.  So, the value of PC is printed
  // according to specification %04x and instruction according
  // to %0x.
  // Meaning:
  //    % - I'm a specification
  //    x - Print in hex
  //    %0 - Print leading zeroes
  //    4  - print 4 hex digits
  
  fprintf(out, "[0x%04x]: 0x%0x\n", PC, instruction);


