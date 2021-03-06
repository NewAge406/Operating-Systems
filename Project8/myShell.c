#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <stdbool.h>

/*Tobias Kundig
  section 1
  Fall '13
  Project 8 */
  
/* Prototypes */ 
void parseCommand(char *buff);

int main(){

  /* Declare instance data*/
  int x;
  char buf[1024];
  
  /*Setup an infinite loop 
    Display a prompt
    Read in the user input from standard in
    If first char is ! Cause Unix to execute the invoked command
    Otherwise
      Determine which legal command the user invoked
      Run the code to make that command happen
      If the command was not legal then display the proper usage message*/
  while(true){
    write(1, "myShell% ", 9);
    x = read(1, buf, sizeof(buf));

    buf[x-1] = 0;

    /* Start if/else checks*/
    if (buf[0] == '!') {
      system(buf + 1);    
    }
    else{parseCommand(buf);}
  }
  return 0;
}

/* After reading the ruberic I created this function to do the
   logic of figuring IT out*/
void parseCommand(char *buffer){
  
  struct passwd* passwd_info;
  
    if(strcmp(buffer, "uid") == 0){
      /*do uid stuff here*/
      printf("Your UID is: %d\n", getuid());
    }
    else if(strcmp(buffer, "user") == 0){
      /* Print user information*/
      printf("Current user is: ");
      passwd_info = getpwuid(getuid());
      printf("%s\n", passwd_info->pw_name);
    }
    else if(strcmp(buffer, "quit") == 0){
      /* Exit */
      printf("Thank you come again!\n");
      exit(0);
    }
    else if(strcmp(buffer, "q") == 0){
      /* Exit */
      printf("Thank you come again!\n");
      exit(0);
    }
    else{ printf("The shell has only the following cmds:\n");
      /* Print the shells commands */
      printf(" uid\n user\n quit \n q \n");
      printf("Start with ! to invoke a Unix shell cmd\n");
    }
}
