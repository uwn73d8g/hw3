#ifndef MACHINEACCESS_H
#define MACHINEACCESS_H

#include <stdint.h>
#include <stdint.h>

#include "machine_private.h"

//------------------------------------------
// Register access
//   * data is in host native format
//------------------------------------------
void     setReg(uint8_t reg, uint16_t data);
void     setRegByteUnsigned(uint8_t reg, uint8_t data); // sets reg to 0x0000[data]

uint16_t getRegUnsigned(uint8_t reg);
int16_t  getRegSigned(uint8_t reg);

uint8_t  getRegByteUnsigned(uint8_t reg);  // returns 0x0000[low order byte]
int8_t   getRegByteSigned(uint8_t reg);  // returns 0x0000[low order byte]

//------------------------------------------
// Memory access
//   * data is in host native format
//------------------------------------------
uint8_t   fetchMemByte(uint16_t addr);
uint16_t  fetchMemWord(uint16_t addr);  // returned value is host native format

void storeMemByte(uint16_t addr, uint8_t data);
void storeMemWord(uint16_t addr, uint16_t data);

//------------------------------------------
// PC & CC access
//    They're defined in machine.h.
//    Access them directly as C variables.
//------------------------------------------

#endif // MACHINEACCESS_H
