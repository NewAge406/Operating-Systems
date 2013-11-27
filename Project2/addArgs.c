#include <stdio.h>
#include <stdlib.h>

int addIntArgs(int firstArg[], int secondArg);
void addArgs(char *arg[], int argc);

int main(int argc, char *argv[]){
	int x;
	int test;
	int intFromFunc;
	int sizeofArray = 50;
	int *newArray;

	newArray = malloc(sizeofArray * sizeof(int));
	printf("%d\n",argc);

	for(x=0; x<argc; x++){
		printf("%s\n",argv[x]);
		test = test + atoi(argv[x]);
		newArray[x] = atoi(argv[x]);
	}

	printf("The total from main is: %d\n",test);

	intFromFunc = addIntArgs(newArray, argc);

	printf("While the total from the function is: %d\n",intFromFunc);
	printf("Going to try to print by passing the args: %d\n",addIntArgs(newArray, argc));


	addArgs(argv, argc);

	return 0;
}

void addArgs(char *argv[], int argc)
{
	int x;
	int test = 0;

	for(x=0; x<argc; x++){
		test = test + atoi(argv[x]);
	}
	printf("And finally the new function is: %d\n",test);
}


int addIntArgs(int firstArg[], int secondArg){
	int x;
	int temp;
	int returnInt = 0;

	for(x=0; x<secondArg; x++){
		temp = firstArg[x];
		
		returnInt = returnInt + temp;
	/*	
		printf("The passed array int is: %d\n",firstArg[x]);
		printf("And the return int variable is: %d\n", returnInt);
		printf("And the temp: %d\n",temp); 
	*/
	}
	return returnInt;
}
