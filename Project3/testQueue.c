#include <stdlib.h>
#include <stdio.h>

/* Define the PCB structure */
struct PCB{
	/*various data fields within the PCB structure*/
	int ID;
	struct PCB *next;
	struct PCB *prev;
} typedef PCB;

/*Prototypes*/
void enqueue (PCB **pntrHN, PCB **pntrTL, PCB passedPCB);
PCB dequeue(PCB **pntrHN, PCB **pntrTL);
void print_queue(PCB *pntrTL);
PCB print_queue_recursive(PCB *pntrTL);
void clear_queue(PCB **pntrHN, PCB **pntrTL);
int size_of_queue(PCB *pntrTL);

/* My beautiful main */
int main(int argc, char * argv[]){
	/* Declare instance data */
	int i;
	PCB **headOfQueue;
	PCB **tailOfQueue;
	PCB pcbNode;

	/* allocate space on the stack for the head and tail */
	headOfQueue = malloc(sizeof(PCB*));
	tailOfQueue = malloc(sizeof(PCB*));

	/* Start the pointers out as null */
	*headOfQueue = 0;
	*tailOfQueue = 0;

	/* for loop to populate the gueue and assign ID a random value */
	for(i=0; i<100; i++){
		/* Initialize the PCB variable values to 0 */
		pcbNode.ID = rand()% 10000 + 1;
		enqueue(headOfQueue,tailOfQueue,pcbNode);
	}

	/* prints the queue, duh */
	print_queue(*tailOfQueue);

	return(0);
}

/* Thanks for the enqueue function! */
void enqueue(PCB **pntrHN, PCB **pntrTL, PCB passedPCB){
	PCB *pntrToNodeToBeAdded;
	pntrToNodeToBeAdded = malloc(sizeof(PCB));
	*pntrToNodeToBeAdded = passedPCB;
	pntrToNodeToBeAdded->prev = 0;
	pntrToNodeToBeAdded->next = *pntrTL;

	if(*pntrTL != 0){
		(*pntrTL)->prev = pntrToNodeToBeAdded;
	}
	else
	{
		*pntrTL = pntrToNodeToBeAdded;
		*pntrHN = pntrToNodeToBeAdded;
	}

	*pntrTL = pntrToNodeToBeAdded;
}

/* Dequeue function */
PCB dequeue(PCB **pntrHN, PCB **pntrTL){
	/* Declare instance variables */
	PCB *tempHead;
	PCB returnVal;

	/* No queue was created */
	if((*pntrHN)->next != 0){
		printf("Bad stuff");
		exit(0);
	}

	/* Its an empty queue */
	if(*pntrHN == 0){
		printf("Bad stuff x2");
		exit(0);
	}

	/* Its an empty queue */
	if(*pntrTL == 0){
		printf("Bad stuff x3");
		exit(0);
	}	

	returnVal = **pntrHN;

	/* There's only one thing in the queue */
	if(*pntrHN == *pntrTL){
		*pntrTL = 0;
		tempHead = 0;
	}
	/* Or there is more than one */
	else{
		/* point the head to the previous node */
		tempHead = (*pntrHN)->prev;
		tempHead->next = 0;
	}
	
	/* free the space so it don't leak! */
	free(*pntrHN);
	*pntrHN = tempHead;

	return returnVal;
}

/* counts the number of non null elements */
int size_of_queue(PCB *pntrTL){	
	int k = 0;
	PCB *pntrToCount;
	pntrToCount = pntrTL;

	/* while loop that steps pntrToCount while its pointing at
	something. k is the counter thats returned */
	while(pntrToCount != 0){
		k ++;
		pntrToCount = pntrToCount->next;
	}
	return(k);
}

/* clear queue calls deque as many times as size of queue says */
void clear_queue(PCB **pntrHN, PCB **pntrTL){
	int i;
	i = size_of_queue(*pntrTL);

	printf("Clearing queue\n");
	while(i >= 1){
		dequeue(pntrHN,pntrTL);		
		i --;		
	}
}

/* Prints the position in the queue and ID of the node */
void print_queue(PCB *pntrTL){
	/* Declare function data */
	int i;
	PCB *pntrToPrint;
	
	/* assign them values */
	pntrToPrint = pntrTL;
	i = size_of_queue(pntrTL);
	
	printf("Printing\n");
	while(i >= 1){
		printf("This is #%d, ID: %d\n", i, pntrToPrint->ID);
		pntrToPrint = pntrToPrint->next;
		i --;
	}

}
