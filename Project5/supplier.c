
#include <stdio.h>
#include <sys/errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

//Tobias Kundig
//Section 1?
//Fall '13
//Project 5

int main(int argc,char *argv[]){
  struct {
    long priority;
    int number;
  } msgp;

  msgp.priority= 2;
  msgp.number = 0;
  int key = 21;
  int msqid;
  int supplierQid;
  int status;
  
  
  //--------------------------------------------------
  //~ YOU MUST SUPPLY CODE THAT PERFORMS THE FOLLOWING 
  //--------------------------------------------------
  
  //~ Create a Q for receiving information (you can use key
      //~ as unique identifier)
  //~ Create a Q for sending information to the requester
      //~ (you can use key-1 as the unique identifier)
  //~ Loop
    //~ Receive number from requester
    //~ Calculate square of that number
    //~ Send that calculated number back to the requester  

  //Create Q for receiving information, key as unique identifier
  //same as requester
  msqid = msgget(key,0660 | IPC_CREAT);
  //Create Q for sending 
  supplierQid = msgget(key-1,0660 | IPC_CREAT);
 
  //Infinite loop that receives the message, calculates
  //the square and sends a message back
  while(true){
	status = msgrcv(supplierQid,&msgp,sizeof(msgp)-sizeof(long),2,0);
	
	//Check for negativeness
	if (status < 0){
		printf("Status is negative. BooBoo");
	}
	msgp.number = msgp.number * msgp.number;
	status = msgsnd(msqid,&msgp,sizeof(msgp)-sizeof(long),0);
}

  return 0;
}
