#ifndef Q_H
#define Q_H
#include <stdlib.h>
#include <stdio.h>
#include "PCB.h"

/* Prototypes */
void enqueue (PCB **pntrHN, PCB **pntrTL, PCB passedPCB);
PCB dequeue(PCB **pntrHN, PCB **pntrTL);
void print_queue(PCB *pntrTL);
PCB print_queue_recursive(PCB *pntrTL);
void clear_queue(PCB **pntrHN, PCB **pntrTL);
int size_of_queue(PCB *pntrTL);

#endif
