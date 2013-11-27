#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int *myInt = 0;

	printf("The pointer before malloc command is %p\n",(void *)myInt);

	printf("myInt has the following value %d\n", *myInt);

	myInt = malloc(sizeof(int));

	*myInt = 2;

	printf("Size of int is %li\n",sizeof(int));

	printf("The pointer is %p\n",(void *)myInt);

	printf("myInt has the following value %d\n", *myInt);

	free(myInt);

	return(0);
}
