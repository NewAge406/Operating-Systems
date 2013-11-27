
#include <sys/errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

//Tobias Kundig
//Section 1?
//Fall '13
//Project 5

//removed by doug
//#include "message.h"

int main(int argc,char *argv[]){
  struct {
    long priority;
    int number;
  } msgp;

  
  int msqid,status;
  int key,qidSupplier,i;
  
  msgp.priority= 2;
  msgp.number = 0;
  key = 20;
  
  printf("key is %i\n",key);
  printf("creating msquid\n");
  
  //--------------------------------------------------
  //~ YOU MUST SUPPLY CODE THAT PERFORMS THE FOLLOWING 
  //--------------------------------------------------
  
  //~ Create a Q for receiving information (you can use 
        //~ the variable key as the unique identifier)
  //~ Create a Q for sending information to the supplier 
        //~ (you can use key+1 as the unique identifier)
  //~ Loop 100 times
    //~ Generate a random number (between 0 and 500)
      //~ hint, rand() generates a number between 0 and RAND_MAX
      //~ if you take the random number and perform a modulo operation
      //~ (like randomNumber % 500) it will yield a number from 0 to 500
    //~ Send the number to the supplier
    //~ Receive the answer back from the supplier
    //~ Display the solution to the console

  //Q for sending information, key as unique identifier
  msqid = msgget(key+1,0660 | IPC_CREAT);

  //Create Q for receiving information, key + 1 used as unique
  //identifier with permission set properly to 0660
  qidSupplier = msgget(key,0660 | IPC_CREAT);

  //For loop that assigns the structs number to a random number
  // between 0 and 500
  for(i=0; i<100; i++){
	msgp.number = rand()%500 + 0;
 	
	//Prints the number to ensure proper operation
	printf("The sent number is: %d\n", msgp.number);

	//Sends the msgp structure containing random number
	//identified as the supplier
	status = msgsnd(qidSupplier,&msgp,sizeof(msgp)-sizeof(long),0);

	//Checks that the message was sent properly
	if (status < 0){
		printf("Status is negative. BooBoo");
	}
	if (status > 0){
		printf("Status is positive.");
	}
	
	//Receives the message from the supplier
	status = msgrcv(msqid,&msgp,sizeof(msgp)-sizeof(long),2,0);
	
	//Prints the solution
	printf("The solution is: %d\n", msgp.number);
  }
  
  printf("all done\n");
  return(0);

}
