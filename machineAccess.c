#include "machine.h"
#include "machine_private.h"
#include "machineAccess.h"

#define REGNUM_MASK  0x0007     // reg is 3 bits
#define MEMADDR_MASK 0x0000ffff // memory addresses are 16 bits

//---------------------------------------------
// Register access
//---------------------------------------------
void setReg(uint8_t reg, uint16_t data) {
  // set CC, even if target reg is 0
  if ( data == 0 ) CC = CC_EQUAL;
  else if ( data & 0x8000 ) CC = CC_LESS;
  else CC = CC_GREATER;
  
  reg = reg & REGNUM_MASK;
  if ( reg == 0 ) return;  // R0 is always 0
  uint8_t *pReg = (uint8_t*)&REGISTER[reg];
  pReg[0] = data>>8;
  pReg[1] = data & 0x00ff;
  // set CC
}
void setRegByteUnsigned(uint8_t reg, uint8_t data) {
  if ( data == 0 ) CC = CC_EQUAL;
  else CC = CC_GREATER;

  // sets reg to 0x0000[data]
  reg = reg & REGNUM_MASK;
  if ( reg == 0 ) return;  // R0 is always 0
  uint8_t *p = (uint8_t*)&REGISTER[reg];
  p[0] = 0x00;
  p[1] = data;
}

int16_t getRegSigned(uint8_t reg) {
  reg = reg & REGNUM_MASK;
  if ( reg == 0 ) return 0;  // R0 is always 0
  uint8_t *pReg = (uint8_t*)&REGISTER[reg];
  return (pReg[0]<<8) | pReg[1];
}

uint16_t getRegUnsigned(uint8_t reg) {
  reg = reg & REGNUM_MASK;
  if ( reg == 0 ) return 0;  // R0 is always 0
  uint8_t *pReg = (uint8_t*)&REGISTER[reg];
  return (pReg[0]<<8) | pReg[1];
}


uint8_t getRegByteUnsigned(uint8_t reg) {
  reg = reg & REGNUM_MASK;
  if ( reg == 0 ) return 0;  // R0 is always 0
  uint8_t *pReg = (uint8_t*)&REGISTER[reg];
  return pReg[1];
}

//------------------------------------------
// Memory access
//------------------------------------------

uint8_t fetchMemByte(uint16_t addr){
  addr &= MEMADDR_MASK;
  return MEMORY[addr];
}

uint16_t fetchMemWord(uint16_t addr) {
  return (fetchMemByte(addr)<<8) | fetchMemByte(addr+1);
}

void storeMemByte(uint16_t addr, uint8_t data) {
  addr &= MEMADDR_MASK;
  MEMORY[addr] = data;
}

void storeMemWord(uint16_t addr, uint16_t data) {
  storeMemByte(addr, (uint8_t)(data>>8));
  storeMemByte(addr+1, data);
}

//------------------------------------------
// PC access
//------------------------------------------

uint16_t getPC() {
  return PC;
}

void setPC(uint16_t val) {
  PC = val;
}

//------------------------------------------
// CC access
//------------------------------------------

uint8_t getCC() {
  return CC;
}

void setCC(uint8_t val) {
  CC = val;
}
