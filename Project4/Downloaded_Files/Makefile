CFLAGS = -g -Wall -ansi -pedantic 

C = gcc 
CC = g++

#to go from .c to .o execute the following command
#~ $< is the prereq, the .c, $@ is the target, .o, % is a wild card

%.o: %.c %.h
	$(CC) -c -o $@ $(CFLAGS) $<

%.o: %.cpp %.h
	$(CC) -c -o $@ $(CFLAGS) $<

%.o: %.cpp
	$(CC) -c -o $@ $(CFLAGS) $<


PROC_OBJ = Processor.o Memory.o PCB.o Program.o queue.o kernel.o Tokenize.o
PROJECT = kernel

kernel:	$(PROC_OBJ) 
	$(CC) -o $(PROJECT) $(CFLAGS) $(PROC_OBJ)

kernel.o: kernelUts.h queue.c queue.h kernel.cpp

clean:
	/bin/rm -fr $(PROC_OBJ) $(PROJECT) *.o *~ core* test *.rpo a.out; clear



