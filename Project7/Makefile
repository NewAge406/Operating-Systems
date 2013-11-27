CFLAGS = -g -Wall -pthread 

CC = g++

%.o:   %.cpp %h
	$(CC) $(CFLAGS) -c $<
%.o:   %.cpp
	$(CC) $(CFLAGS) -c $<

OBJFILES = jobHandler.o
SOURCE = jobHandler.cpp
PROJECT = doJobs
doJobs:      $(OBJFILES)
	$(CC) -o $(PROJECT) $(CFLAGS) $(SOURCE)

clean:
	/bin/rm -fr $(OBJ) $(PROJECT) *.o *~ core*; clear
