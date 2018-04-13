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
  //   parameter instruction) and "disassembling"it.
  //
  //   Run the solution executable for an example of what you might
  //   print here.
  //
  //  Hint 1: You'll need your step 1 code.
  //  Hint 2: The overall structure of the code here
  //          is very similar to the code in simulator-distribution.c
  //---------------------------------------------------
    uint8_t  OP = instruction >> 18;
    uint8_t  RA = (instruction >> 15) & 7;
    uint8_t  RB = (instruction >> 12) & 7;
    uint8_t  RC = (instruction >> 9) & 7;
    int16_t  IMMED_10 = (instruction >> 8) & 1023;
    int16_t  IMMED_12 = (instruction) & 4095;
    int16_t  IMMED_15 = (instruction) & 32767;

    IMMED_10 = (IMMED_10 << 6) >> 6;
    IMMED_12 = (IMMED_12 << 4) >> 4;
    IMMED_15 = (IMMED_15 << 1) >> 1;

  // The fprintf "format string"is just a string with
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
    fprintf(out, "[0x%04x]: 0x%0x  ", PC, instruction);

  switch(OP) {
    case STOP:
      fprintf(out, "STOP");
      break;

    case NOP:
      fprintf(out, "NOP");
      break;

    case LW:

      fprintf(out, "LW r%d r%d r%d\n",  RA, RB, RC);
      break;

    case LB:

      fprintf(out, "LB r%d r%d r%d\n",  RA, RB, RC);
      break;

    case SW:

      fprintf(out, "SW r%d r%d r%d\n", RA, RB, RC);
      break;

    case SB:

      fprintf(out, "SB r%d r%d r%d\n", RA, RB, RC);
      break;

    case ADD:
      fprintf(out, "ADD r%d r%d r%d\n",  RA, RB, RC);
      break;
      
    case SUB:
      fprintf(out, "SUB r%d r%d r%d\n",  RA, RB, RC);
      break;
      
    case MUL:
      fprintf(out, "MUL r%d r%d r%d\n",  RA, RB, RC);
      break;
      
    case DIV:
      {
	int16_t regC = getRegSigned(RC);
	if ( regC == 0 ) {
	  fprintf(stderr, "Machine check: divisor is 0\n");
	  break;
	}

      fprintf(out, "DIV r%d r%d r%d\n", RA, RB, RC);
      break;
      
    case ADDI:
      fprintf(out, "ADDI r%d r%d r%d ",  RA, RB, IMMED_12);
      break;

    case AND:
      fprintf(out, "AND r%d r%d r%d\n",  RA, RB, RC);
      break;
      
    case OR:
      fprintf(out, "OR r%d r%d r%d\n",  RA, RB, RC);
      break;
      
    case XOR:
      fprintf(out, "XOR r%d r%d r%d\n",  RA, RB, RC);
      break;

    case SHFTL:
      fprintf(out, "SHFTL r%d r%d $%d\n",  RA, RB, IMMED_12);
      break;
      
    case SHFTR:
      fprintf(out, "SHFTR r%d r%d $%d\n",  RA, RB, IMMED_12);
      break;

    case CMP:

      fprintf(out, "CMP r%d r%d $%d\n", RA, RB, RC);
      break;
      
    case BE:

      fprintf(out, "BE ",  IMMED_10);
      break;
      
    case BLT:

      fprintf(out, "BLT ", IMMED_10);
      break;
      
    case BGT:

      fprintf(out, "BGT ", IMMED_10);
      break;
      
    case JR:
      fprintf(out, "JR r%d r%d $%d\n",  RA, RB, RC);
      break;

    case CALL:

      fprintf(out, "CALL r%d r%d ", RA, RB, RC);
      break;
      
    case PRINTR:
      
       fprintf(out, "PRINTR r%d r%d ", RA, RB, RC);
      break;

    case PRINTM:

  fprintf(out, "PRINTM r%d r%d ",  RA, RB, RC);
      break;


    case PRINTC:
      fprintf(out, "PRINTC r%d r%d ", RA, RB, RC);
      break;

    default:
      fprintf(stderr, "0x%04x\tMachine check: invalid opcode: ", PC, OP);
      }
    }
  }
