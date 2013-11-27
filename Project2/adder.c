#include <stdio.h>

int add(int a, int b);

int main(int argc, char *argv[]){
	int myInt;
	myInt = add(5,6);
	printf("My int is %d\n",myInt);
	return (0);
}

int add(int a, int b){
	return a+b;
}
