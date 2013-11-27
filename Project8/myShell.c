#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <stdbool.h>

int main(){

  /* Declare instance data*/
  int x;
  char buf[1024];
  struct passwd* passwd_info;
  
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

    if (buf[0] == '!') {
      system(buf + 1);    
    }
    else if(strcmp(buf, "uid") == 0){
      /*do uid stuff here*/
      printf("Your UID is: %d\n", getuid());
    }
    else if(strcmp(buf, "user") == 0){
      printf("Current user is: ");
      passwd_info = getpwuid(getuid());
      printf("%s\n", passwd_info->pw_name);
    }
    else if(strcmp(buf, "quit") == 0){
      printf("Thank you come again!\n");
      exit(0);
    }
    else if(strcmp(buf, "q") == 0){
      printf("Thank you come again!\n");
      exit(0);
    }
    else{ printf("The shell has only the following cmds:\n");
      printf(" uid\n user\n quit \n q \n");
      printf("Start with ! to invoke a Unix shell cmd\n");
    }  
  }
  return 0;
}
