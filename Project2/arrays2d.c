# include <stdio.h>
# include <stdlib.h>

int main(int argc, char *argv[]){
	int numRows = 3;
	int numCols = 4;
	int i;
	int j;
	int **myTwoDArray;

	myTwoDArray = malloc(numRows*sizeof(*myTwoDArray));

	for(i=0; i<numRows; i++){
		myTwoDArray[i] = malloc(numCols*sizeof(int));
		for(j=0; j<numCols; j++){
			myTwoDArray[i][j] = j*i;
			printf("Row %d, Column %d holds the value %d\n",i,j,myTwoDArray[i][j]);
		}
	}
	return(0);
}
