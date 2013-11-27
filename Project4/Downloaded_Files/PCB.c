#include "PCB.h"
#include <stdlib.h>
#include <stdio.h>

void initializePCB(PCB *passedPCB){
	passedPCB->limit = 0;
	passedPCB->next = 0;
	passedPCB->prev = 0;
	passedPCB->ID = 0;
	passedPCB->PC = 0;
	passedPCB->base = 0;
	passedPCB->register1 = 0;
	passedPCB->register2 = 0;
	passedPCB->register3 = 0;
	passedPCB->register4 = 0;
	passedPCB->register5 = 0;
}

