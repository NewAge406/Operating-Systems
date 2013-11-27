#include "kernelUts.h"

  


int main(int argc, char * argv[]){
  
  loadProgs();//loads programs into memory and PCBs into ready Q
 
  /*-------------------------------------------------
    -------------------------------------------------
  TODO: print the contents of the queue using the 
    print_queue routine you wrote in previous
    project. The pointer (to a pointer) for the
    head and tail of the ready Q is readyHead
    and readyTail
    -------------------------------------------------
    -----------------------------------------------*/
  print_queue(*readyTail);
  
  /*-------------------------------------------------
    -------------------------------------------------
  TODO: check that there are PCBs in the ready Q
    (with the size_of_queue command)
    If there are, go ahead and dequeue a PCB
    from the ready Q and store it in 
    currentRunningPCB (defined in kernelUts.h)
    Otherwise, indicate that there are no 
    processes to run and exit.
    -------------------------------------------------
    -----------------------------------------------*/
  if(size_of_queue(*readyTail) > 0){
	currentRunningPCB = dequeue(readyHead, readyTail);
  }
  else{
	printf("Notta");
  }

  
  cout << "dequeued " << currentRunningPCB.ID << endl;
  
  //~ the next command takes the info in the PCB and conditions the 
  //~ processor so that all the registers are as they appear
  //~ in the PCB. At this point, not much is going on so it is
  //~ really just the base, limit, and instruction register that 
  //~ get set (the instruction is the first instruction at this 
  //~ point so the PCB should indicate that the first 
  //~ instruction is at the base address
  dispatch(currentRunningPCB);
  
  //~ This initializes the interrupt service vector so that the
  //~ addresses for each of the interrupt service routines are stored
  //~ in the vector
  initializeISV();
  
  //~ This is the heart of the kernel. It is an infinite loop where 
  //~ the kernel tells the processor to run until interrupted. 
  //~ when an interrupt is encountered, the processor object returns
  //~ it. The interrupt service routine associated with that interrupt 
  //~ is then executed.
  while(1){
    int interrupt = myProc.run();
    cout << "received interupt: " << interrupt << endl;
    ISV[interrupt]();//the ISV is the interrupt service vector
    //it holds pointers to interrupt service routines
    //a common interrupt is a context switch 
    //the isr for a context switch removes the current process
    //from control of the processor and loads the processor with
    //the next PCB 
  }

  return(0);
}





void initializeISV(){
  //~ the ISV is the interrupt service vector
  //~ It contains addresses of interrupt service routines (ISR's)
  
  //~ start by initializing these addresses to 0. Note: NUMINTS is
  //~ in kernelUts.h
  for(int i = 0; i < NUMINTS; i++){
    ISV[i]=0;
  }
  
  //~ the following are the names of functions. When the name of a 
  //~ procedure is used in this kind of context it acts as an address 
  //~ to the location of the function within the compiled program 
  //~ (in this case, the kernel). These procedures can be found below,
  //~ and their prototypes can be found in kernelUts.h
  ISV[0] = performContextSwitch;
  ISV[1] = performAbend;
  ISV[2] = performNormalEnd;

}

//~ this just pulls current info from proc
//~ and stores in currentRunningPCB
void removeCurrentFromProc(){
  /*-------------------------------------------------
    -------------------------------------------------
  TODO: interrogate the processor (myProc) and learn
    what all the fields are. Store these fields in
    the currentRunningPCB. 
    There are getReg#() functions in the 
    processor object where the # is a number
    1 through 5. There is also a getPC(), 
    getBase(), and getLimit().
    The currentRunningPCB is a global 
    variable defined in the kernelUts.h file.
    -------------------------------------------------
    -----------------------------------------------*/
  currentRunningPCB.limit = myProc.getLimit();
  currentRunningPCB.PC = myProc.getPC();
  currentRunningPCB.base = myProc.getBase();
  currentRunningPCB.register1 = myProc.getReg1();
  currentRunningPCB.register2 = myProc.getReg2();
  currentRunningPCB.register3 = myProc.getReg3();
  currentRunningPCB.register4 = myProc.getReg4();
  currentRunningPCB.register5 = myProc.getReg5();
}

//~ this just sets up the proc for execution
//~ must still execute the run command
void dispatch(PCB passedPCB){
  /*-------------------------------------------------
    -------------------------------------------------
  TODO: Store all the passed PCB fields in the 
    processor. The processor is a global 
    variable called myProc. Just as there 
    were get functions that you used above 
    in the remove function, there are also 
    set methods.
    
    -------------------------------------------------
    -----------------------------------------------*/
  myProc.setLimit(passedPCB.limit);
  myProc.setPC(passedPCB.PC);
  myProc.setBase(passedPCB.base);
  myProc.setReg1(passedPCB.register1);
  myProc.setReg2(passedPCB.register2);
  myProc.setReg3(passedPCB.register3);
  myProc.setReg4(passedPCB.register4);
  myProc.setReg5(passedPCB.register5);
}
void performContextSwitch(){
  //~ jobs should be in the Q
  //~ get new pc for current running proc
  
  /*-------------------------------------------------
    -------------------------------------------------
  TODO: extract the current information about the 
        processor and store it in the currentRunningPCB
        data structure. Remember, there is a function
        already defined that will do this for you.
    -------------------------------------------------
    -----------------------------------------------*/
  removeCurrentFromProc();
  
  cout << "context switch|curr proc: " << currentRunningPCB.ID << "|curr PC: "
    << currentRunningPCB.PC << "|curr base: " << currentRunningPCB.base << "|";
  
  /*-------------------------------------------------
    -------------------------------------------------
  TODO: put the PCB just removed from the processor
    in the ready queue 
    (enqueue currentRunningPCB)
    -------------------------------------------------
    -----------------------------------------------*/

  enqueue(readyHead, readyTail, currentRunningPCB);

  /*-------------------------------------------------
    -------------------------------------------------
  TODO: remove the next PCB from the ready Q 
    and store it in currentRunningPCB
    -------------------------------------------------
    -----------------------------------------------*/
  currentRunningPCB = dequeue(readyHead, readyTail);  
  
  cout << "new proc: " << currentRunningPCB.ID << "|new PC: " <<
    currentRunningPCB.PC << "|new base: " << currentRunningPCB.base << endl;
  
  /*-------------------------------------------------
    -------------------------------------------------
  TODO: take the info in the current PCB and condition the 
        processor so that all the registers are as they were 
        when the process that is represented by the PCB
        was last removed from control of the processor.
        Remember, there is a function already defined
        that will do this.
    -------------------------------------------------
    -----------------------------------------------*/
  
  dispatch(currentRunningPCB);
  
}


//~ this is one of the interrupt service routines. If something illegal happens
//~ like the program tries to access an address below its base or above its 
//~ limit then this interrupt should occur.
void performAbend(){
  
  //~ this extracts the current information about the 
  //~ processor and stores it in the currentRunningPCB
  //~ data structure. This one was used because it is 
  //~ the same one that was placed in control of the 
  //~ processor, so it has the correct process ID.
  //~ All we have done here is update it with the current
  //~ register contents of the processor.
  removeCurrentFromProc();
  
  cout << "ABEND|curr proc: " << currentRunningPCB.ID << "|curr PC: "
    << currentRunningPCB.PC << "|curr base: " << currentRunningPCB.base << "|";
  
  
    /*-------------------------------------------------
    -------------------------------------------------
  TODO: The just removed process control block 
    represents a program that we do not 
    wish to continue running. For this reason
    we will not re-enqueue it in the ready q.
    That's really all there is to it. That will 
    kill the current process.
    We do need to start the next process. 
    Check to see if there is anything in the Q
    (with size_of_queue). If there is dequeue
    the next PCB and store it in 
    currentRunningPCB. Otherwise output
    a message that all processes have run
    to completion. 
    -------------------------------------------------
    -----------------------------------------------*/
  if(size_of_queue(*readyTail) > 0){
	currentRunningPCB = dequeue(readyHead, readyTail);
  }
  else{
	printf("All processes have run to completion.\n");
	exit(0);
  }
  
  cout << "new proc: " << currentRunningPCB.ID << "|new PC: " <<
    currentRunningPCB.PC << "|new base: " << currentRunningPCB.base << endl;
  dispatch(currentRunningPCB);
  
  
}

//~ this is one of the interrupt service routines. If the program completes
//~ normally then this interrupt should occur.
void performNormalEnd(){
  
  //~ this extracts the current information about the 
  //~ processor and stores it in the currentRunningPCB
  //~ data structure. This one was used because it is 
  //~ the same one that was placed in control of the 
  //~ processor, so it has the correct process ID.
  //~ All we have done here is update it with the current
  //~ register contents of the processor.
  removeCurrentFromProc();
  
  cout << "Normal End|curr proc: " << currentRunningPCB.ID << "|curr PC: "
    << currentRunningPCB.PC << "|curr base: " << currentRunningPCB.base << "|";
  
    /*-------------------------------------------------
    -------------------------------------------------
  TODO: The just removed process control block 
    represents a program that we do not 
    wish to continue running. For this reason
    we will not re-enqueue it in the ready q.
    That's really all there is to it. That will 
    kill the current process.
    We do need to start the next process. 
    Check to see if there is anything in the Q
    (with size_of_queue). If there is dequeue
    the next PCB and store it in 
    currentRunningPCB. Otherwise output
    a message that all processes have run
    to completion. 
    -------------------------------------------------
    -----------------------------------------------*/
 if(size_of_queue(*readyTail) > 0){
	currentRunningPCB = dequeue(readyHead, readyTail);
  }
  else{
	printf("All processes have run to completion.\n");
	exit(0);
  }
  
  cout << "new proc: " << currentRunningPCB.ID << "|new PC: " <<
    currentRunningPCB.PC << "|new base: " << currentRunningPCB.base << endl;
  dispatch(currentRunningPCB);
  
  
}

void loadProgs(){
  //iniialize the ready q (nothing in it 
  //so head and tail pointers to zero)
  //these are global variables--see above
  readyHead = new PCB*;
  readyTail = new PCB*;
  *readyHead = 0;
  *readyTail = 0;
  
  //~ build a vector of file names (strings)
  //~ the opendir, dirent, DIR, closedir functions and data 
  //~ structures  are all in dirent.h which is loaded in kernelUts.h
  vector<string> files;
  DIR *dp;
  struct dirent *dirp;
  string dir = ".";
  if((dp  = opendir(dir.c_str())) == NULL) {
      cout << "Error(" << errno << ") opening " << dir << endl;
      exit(errno);
  }

  while ((dirp = readdir(dp)) != NULL) {
    string fileName =  string(dirp->d_name);
    if(fileName.find(".txt") < fileName.length()){
      files.push_back(fileName);
    }
  }
  closedir(dp);
  
  //~ for(uint i = 0; i < files.size(); i++){
    //~ cout << files[i] << endl;
  //~ }
  
  
  //~ create instances of program objects which hold
  //~ the code of the assembly language programs loaded
  //~ previously. These are loaded into main memory.
  //~ The program objects are really just handy containers for 
  //~ the raw textual commands and aren't really needed after
  //~ the programs are loaded into memory.
  //~ Once loaded into memory, a representative PCB is placed
  //~ in the ready Q
  Program *myProg;
  for(uint i = 0; i < files.size(); i++){
    myProg = new Program;
    myProg->load(files[i]);
    mainMemory.load(*myProg);
    
  /*-------------------------------------------------
    -------------------------------------------------
  TODO: The PCB for the program that was just loaded 
    in main memory needs to be placed in the 
    ready Q. You can get the PCB from the 
    program with the "getPCB" function. 
    the program is a pointer so you will need 
    to use the "->" notation.
    -------------------------------------------------
    -----------------------------------------------*/
    enqueue(readyHead, readyTail, myProg->getPCB());
  }
  
  
  
  
  mainMemory.dumpMem();
  char tempChar;
  cout << "Above is memory dump prior to running\n";
  cout << "press enter to continue\n";
  //~ cin >> tempString;
  tempChar = getc(stdin);
  
}
