#include <stdint.h>

#include "machine.h"
#include "simulator.h"
#include "debugger.h"
#include "disassembler.h"

//----------------------------------------------------
// Main entry point for the simulator
//----------------------------------------------------

void simRun(bool debug) {

  // go into fetch, increment, execute loop

  bool machineIsRunning = true;
  bool debugStop = debug;
  
  while (machineIsRunning) {

    uint32_t instruction = (fetchMemByte(PC)<<16) |
                           (fetchMemByte(PC+1)<<8) |
                           fetchMemByte(PC+2);

    if ( debug ) disassemble(stderr, instruction);

    if ( debugStop ) {
      Debugger_Rcode rcode =debuggerRun();
      if ( rcode == DEBUGGER_HALT ) break;
      if ( rcode == DEBUGGER_CONTINUE ) debugStop = false;
      // otherwise it's DEBUGGER_STEP, which we're about to do
    }

    //---------------------------------------------------------
    // STEP 1 - replace '0' in the statements below with an
    //          expressions that have the right effect.
    //
    // The 3 bytes pointed at by the PC have been fetched
    // into variable 'instruction'.  They are the low order
    // 24 bits of that 32-bit variable.
    //
    // The job now is to parse the three bytes for all five
    // instruction formats (since we haven't yet decoded the
    // opcode and so dont' know instruction we have).
    //---------------------------------------------------------
    
    uint8_t  OP = instruction>>18;
    uint8_t  RA = (instruction>>15)&7;
    uint8_t  RB = (instruction>>12)&7;
    uint8_t  RC = (instruction>>9)&7;
    int16_t  IMMED_10 = (instruction>>8)&1023;
    int16_t  IMMED_12 = instruction&4095;
    int16_t  IMMED_15 = instruction&32767;

    //--------------------------------------------------------
    // STEP 2
    // The 10 bit, 12 bit, and 15 bit immediate value
    // field from the instruction is in a 16-bit C variable.
    // Sign-extend the immediate field.
    // That means if the highest order bit (of the 10/12/15)
    // is 0, do nothing. If it's 1, make all bits to its
    // left 1's as well (in the 16-bit variable).
    //--------------------------------------------------------

    // Your code here
    IMMED_10 = IMMED_10<<6>>6;
    IMMED_12 = IMMED_12<<4>>4;
    IMMED_15 = IMMED_15<<1>>1;
  

    //----------------------------------
    // Execute the instruction
    //----------------------------------
    
    switch(OP) {
    case STOP:
      PC += 1;
      machineIsRunning = false;
      break;

    case NOP:
      PC += 1;
      break;

    case LW:
      PC += 2;
      setReg(RA, fetchMemWord( getRegUnsigned(RB) + getRegUnsigned(RC) ));
      break;

    case LB:
      PC += 2;
      setRegByteUnsigned(RA, fetchMemByte( getRegUnsigned(RB) + getRegUnsigned(RC) ));
      break;

    case SW:
      PC += 2;
      storeMemWord(getRegUnsigned(RB) + getRegUnsigned(RC), getRegUnsigned(RA));
      break;

    case SB:
      PC += 2;
      storeMemByte(getRegUnsigned(RB) + getRegUnsigned(RC), getRegByteUnsigned(RA));
      break;

    case ADD:
      PC += 2;
      setReg(RA, getRegSigned(RB) + getRegSigned(RC));
      break;
      
    case SUB:
      PC += 2;
      setReg(RA, getRegSigned(RB) - getRegSigned(RC));
      break;
      
    case MUL:
      PC += 2;
      setReg(RA, getRegSigned(RB) * getRegSigned(RC));
      break;
      
    case DIV:
      {
	int16_t regC = getRegSigned(RC);
	if ( regC == 0 ) {
	  fprintf(stderr, "@ 0x%04x\tMachine check: divisor is 0\n", PC);
	  machineIsRunning = false;
	  break;
	}
	PC += 2;
	setReg(RA, getRegSigned(RB) / regC);
      }
      break;
      
    case ADDI:
      PC += 3;
      setReg(RA, getRegSigned(RB) + IMMED_12);
      break;

    case AND:
      PC += 2;
      setReg(RA, getRegUnsigned(RB) & getRegUnsigned(RC));
      break;
      
    case OR:
      PC += 2;
      setReg(RA, getRegUnsigned(RB) |  getRegUnsigned(RC));
      break;
      
    case XOR:
      PC += 2;
      setReg(RA, getRegUnsigned(RB) ^ getRegSigned(RC));
      break;

    case SHFTL:
      PC += 3;
      setReg(RA, getRegUnsigned(RB) << IMMED_12);
      break;
      
    case SHFTR:
      PC += 3;
      setReg(RA, getRegSigned(RB) >> IMMED_12);
      break;

    case CMP:
      {
	PC += 2;
	int16_t signedB = getRegSigned(RB);
	int16_t signedC = getRegSigned(RC);
	if ( signedB == signedC ) CC = CC_EQUAL;
	else if ( signedB < signedC ) CC = CC_LESS;
	else CC = CC_GREATER;
      }
      break;
      
    case BE:
      if ( CC == CC_EQUAL ) PC += IMMED_10;
      else PC += 2;
      break;
      
    case BLT:
      if ( CC == CC_LESS ) PC += IMMED_10;
      else PC += 2;
      break;
      
    case BGT:
      if ( CC == CC_GREATER ) PC += IMMED_10;
      else PC += 2;
      break;
      
    case JR:
      PC = getRegUnsigned(RB) + getRegUnsigned(RC);
      break;

    case CALL:
      {
	// have to be careful as CALL can write a register used
	// in computing target address
	uint16_t updatedPC = PC + 3;
	PC = IMMED_15;
	setReg(RA, updatedPC); // we leave the updated PC in RA
      }
      break;
      
    case PRINTR:
      {
	uint16_t val = getRegUnsigned(RA);
	printf("[r%d @ 0x%04x] 0x%02x%02x\n",
	       RA,
	       PC,
	       (uint8_t)(val>>8),
	       (uint8_t)val
	       );
	PC += 2;
      }
      break;

    case PRINTM:
      {
	uint16_t addr = getRegUnsigned(RB) + getRegUnsigned(RC);
	uint16_t val = fetchMemWord( addr );
	printf("[MEM[0x%04x] @ 0x%04x] 0x%02x%02x\n",
	       addr,
	       PC,
	       (uint8_t)(val>>8),
	       (uint8_t)val
	     );
	PC += 2;
      }
      break;


    case PRINTC:
      {
	PC += 2;
	uint16_t addr = getRegUnsigned(RB) + getRegUnsigned(RC);
	char c = fetchMemByte(addr);
	printf("%c", c);
      }
      break;

    default:
      fprintf(stderr, "@ 0x%04x\tMachine check: invalid opcode: 0x%0x\n", PC, OP);
      machineIsRunning = false;
      
    }
  }

  machine_dumpMachine(stdout);
    
  return;
}
