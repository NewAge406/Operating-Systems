CFLAGS = -g -Wall -ansi -pedantic -D_XOPEN_SOURCE

CC = g++

.SUFFIXES: .cpp .o .C

.C.o:
	$(CC) $(CFLAGS) -c $<

.cpp.o:
	$(CC) $(CFLAGS) -c $<

CALCULATER_OBJ = requester.o supplier.o

calculator:	$(CALCULATER_OBJ)
	$(CC) -o requester $(CFLAGS) requester.o
	$(CC) -o supplier $(CFLAGS) supplier.o 



clean:
	/bin/rm -fr $(SENSOR_OBJ) $(PROJECT) *.o *~ core* requester supplier; clear


