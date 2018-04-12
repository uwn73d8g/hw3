#include <ctype.h>

#include "loader.h"
#include "machine_private.h"

static int linenum;

//------------------------------------------------
// util fn:
//  Bytes are two hex digits
//  Return codes: 0: normal, >0: error
//------------------------------------------------
static int readByte(FILE *in, char c, uint8_t *val) {
  c = tolower(c);
  if ( c >= '0' && c <= '9' ) *val = c-'0';
  else if ( c >= 'a' && c <= 'f' ) *val = c-'a' + 10;
  else {
    fprintf(stderr, "Line %d: Invalid character in hex byte: '%c'\n", linenum, c);
    return 1;
  }

  c = fgetc(in);
  // special case this error for clarity of error message
  if ( isspace(c) ) {
    fprintf(stderr, "Line %d: Odd number of hex digits in file token: 0x%x\n", linenum, *val);
    return 2;
  }
  c = tolower(c);
  if ( c >= '0' && c <= '9' ) *val = (*val << 4) + (c-'0');
  else if ( c >= 'a' && c <= 'f' ) *val = (*val << 4) + (c-'a') + 10;
  else {
    if ( c == EOF )
      fprintf(stderr, "Line %d: EOF while reading data byte\n", linenum);
    else 
      fprintf(stderr, "Line %d: Invalid character in hex byte: '%c'\n", linenum, c);
    return 3;
  }

  return 0;
}

//------------------------------------------------
// helper fn:  Addresses are four hex digits
//------------------------------------------------
static int readAddress(FILE *in, uint16_t *val) {
  *val = 0;
  for (int i=0; i<4; i++) {
    char c = fgetc(in);
    c = tolower(c);
    if ( c >= '0' && c <= '9' ) *val = (*val << 4) + (c-'0');
    else if ( c >= 'a' && c <= 'f' ) *val = (*val << 4) + (c-'a') + 10;
    else {
      if ( c == EOF )
	fprintf(stderr, "Line %d: EOF while reading address\n", linenum);
      else 
	fprintf(stderr, "Line %d: Invalid character in address: '%c'\n", linenum, c);
      return 1;
    }
  }
  // we insist on a whitespace char here to detect plausible user error
  char c = fgetc(in);
  if ( !isspace(c) && c!=EOF) {
    fprintf(stderr, "Line %d: Address isn't four hex digits.  5th digit is '%c'\n", linenum, c);
    return 2;
  }
  if ( c == '\n' ) linenum++;
  
  return 0;
}

//-----------------------------------------------------------------
// loader()
//   loads data per executable file
//-----------------------------------------------------------------

int loader(FILE *exeFile) {

  typedef enum state {start, incomment} State;
  State state = start;
  
  char cRead;
  uint16_t loadAddress;
  int rcode;

  linenum = 1;  // editors seem to number starting at 1

  while ( (cRead = fgetc(exeFile)) != EOF ) {
    char c = tolower(cRead);

    switch (state) {
    case start:
      if ( c == '\n' ) linenum++;
      if ( isspace(c) ) continue;
      if ( c == '#' ) state = incomment;
      else if ( c == '@' ) {
	if ( readAddress(exeFile, &loadAddress) ) return 1;
      }
      else if ( c == '!' ) {
	if ( readAddress(exeFile, &PC) ) return 2;
      }
      else if ( (c>='0' && c<='9') || (c>='a' && c<='f') ) {
	rcode = readByte(exeFile, c, &MEMORY[loadAddress++] );
	if ( rcode > 0 ) return 3;
      }
      else {
	fprintf(stderr, "Line %d: Loader encountered unexpected character '%c'\n", linenum, cRead);
	return 4;
      }
      break;

    case incomment:
      if ( c == '\n' ) {
	state = start;
	linenum++;
      }
      break;
    }
  }
  return 0;
}
