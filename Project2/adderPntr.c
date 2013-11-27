# include <stdio.h>

int add(int *a, int *b);

int main(int argc, char *argv[]){
	int mySum;
	int a;
	int b;

	a = 5;
	b = 6;

	mySum = add(&a,&b);
	printf("My int is %d\n",mySum);
	printf("a is now: %d\n",a);
	return(0);
}

int add(int *a, int *b){
	int sum;
	sum = *a + *b;
	*a = 999
	return sum;
}
