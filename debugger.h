#ifndef DEBUGGER_H
#define DEBUGGER_H

typedef enum {DEBUGGER_HALT, DEBUGGER_STEP, DEBUGGER_CONTINUE} Debugger_Rcode;

Debugger_Rcode debuggerRun();

#endif // DEBUGGER_H
