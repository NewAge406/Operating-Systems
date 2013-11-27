CFLAGS = -g -Wall -ansi -pedantic

C = gcc 

%.o: %.c
	$(C) -c -o $@ $(CFLAGS) $<

%.o: %.c %.h
	$(C) -c -o $@ $(CFLAGS) $<


OBJECT = testQueueMod.o queue.o PCB.o
PROJECT = test

main:	$(OBJECT) 
	$(C) -o $(PROJECT) $(CFLAGS) $(OBJECT)


clean:
	/bin/rm -fr $(OBJECT) $(PROJECT)  *.o *~ core* test *.rpo a.out; clear



