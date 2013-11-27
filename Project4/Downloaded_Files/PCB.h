#ifndef PCB_H
#define PCB_H

/* Defines the structure PCB */
struct PCB{
	/*various data fields within the PCB structure*/
	int ID;
	int limit, PC, base, register1, register2, register3, register4, register5;

	struct PCB *next;
	struct PCB *prev;
} typedef PCB;

/* Used in the next Project. Can't make this work yet */
void initializePCB(PCB *passedPCB);

#endif
