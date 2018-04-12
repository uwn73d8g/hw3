CC = gcc
CFLAGS = -Wall -std=c11 -g
SRC = simMain.c loader.c machine.c machineAccess.c debugger.c disassembler-distribution.c simulator-distribution.c
INC = loader.h machine.h simulator.h machineAccess.h opcodes.h debugger.h disassembler.h

sim: $(SRC) $(INC)
	$(CC) $(CFLAGS) $(SRC) -o sim -lreadline


clean:
	rm -f *~ *.o sim

