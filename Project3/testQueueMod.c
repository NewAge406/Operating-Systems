#include "queue.h"

/* My beautiful main */
int main(int argc, char * argv[]){
	/* Declare instance data */
	int i;
	PCB **headOfQueue;
	PCB **tailOfQueue;
	PCB pcbNode;

	/* allocate space on the stack for the head and tail */
	headOfQueue = (PCB**)malloc(sizeof(PCB*));
	tailOfQueue = (PCB**)malloc(sizeof(PCB*));

	/* Start the pointers out as null */
	*headOfQueue = 0;
	*tailOfQueue = 0;

	/* for loop to populate the gueue and assign ID a random value */
	for(i=0; i<100; i++){
		/* Initialize the PCB variable values to 0 */
		pcbNode.ID = rand()% 10000 + 1;
		enqueue(headOfQueue,tailOfQueue,pcbNode);
	}

	/* Prints the nodes ID in the queue */
	print_queue(*tailOfQueue);

	/* Prints the number of nodes in the queue*/
	printf("There are %d elements in the queue.\n", 		size_of_queue(*tailOfQueue));

	/* Clears the queue */
	clear_queue(headOfQueue,tailOfQueue);
	
	/* Reprints the number of nodes to ensure it was cleared*/
	printf("There are %d elements in the queue.\n", 		size_of_queue(*tailOfQueue));
	
	return(0);
}

