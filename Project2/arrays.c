#include <stdio.h>
#include <stdlib.h>

float testMethod(int array[], int a);

int main(int argc, char *argv[]){
	int *myArray;
	int sizeOfArray = 50;
	float test;
	int i;

	myArray = malloc(sizeOfArray * sizeof(int));

	for(i=0; i<49; i++){
		myArray[i] = rand()%30000 + 20000;
	}

	for(i = 0; i<49; i++){
		printf("Cell %d contains value: %d\n", i, myArray[i]);
	}

	test = testMethod(myArray, sizeOfArray);

	printf("The average is: %f\n", test);

	return(0);
}

float testMethod(int array[], int a){
	int sum = 0;
	float total = 0.0;
	int i;

	for(i=0; i<a; i++){
		sum = sum + array[i];
	}

	return total = sum/a;

}
