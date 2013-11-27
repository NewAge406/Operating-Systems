#include "Processor.h"



//~ constructor. nothing needed
Processor::Processor(){
  //~ cout << "emp constructor called\n";
}

//~ destructor. nothing needed
Processor::~Processor(){
}


int Processor::getMAR(){//Memory Address Register
  return MAR;
}

void Processor::setMAR(int passedMAR){//Memory Address Register
  MAR = passedMAR;
}

string Processor::getMDR(){//memory destination address register
  return MDR;
}

void Processor::setMDR(string passedMDR){
  MDR = passedMDR;
}

int Processor::getPC(){
  return PC;
}

void Processor::setPC(int passedPC){
  PC = passedPC;
}
    
string Processor::getIR(){
  return IR;
}


void Processor::setIR(string passedIR){
  IR = passedIR;
}


int Processor::getBase(){
  return base;
}

void Processor::setBase(int passedBase){
  base = passedBase;
}

int Processor::getLimit(){
  return limit;
}

void Processor::setLimit(int passedLimit){
  limit = passedLimit;
}

void Processor::setReg1(word passedWord){
  register1 = passedWord;
}
  
void Processor::setReg2(word passedWord){
  register2 = passedWord;
}

void Processor::setReg3(word passedWord){
  register3 = passedWord;
}

void Processor::setReg4(word passedWord){
  register4 = passedWord;
}

void Processor::setReg5(word passedWord){
  register5 = passedWord;
}

word Processor::getReg1(){
  return register1;
}

word Processor::getReg2(){
  return register2;
}

word Processor::getReg3(){
  return register3;
}

word Processor::getReg4(){
  return register4;
}

word Processor::getReg5(){
  return register5;
}

void Processor::incReg1(){register1 = register1 + 1;}
void Processor::incReg2(){register2 = register2 + 1;}
void Processor::incReg3(){register3 = register3 + 1;}
void Processor::incReg4(){register4 = register4 + 1;}
void Processor::incReg5(){register5 = register5 + 1;}


/*--------------------------------------------------------------------------------------
                   THIS IS THE BIG KAHUNA
this sets the processor free, it must have the pc set, but 
beyond that it's off to the races. The only way to context 
switch is through an interrupt. There is an implied 
interrupt at the end of a quantum which is nothing
more than a loop. Otherwise, I will have to come up
with a way to interrupt the loop, perhaps multi-
threading? How about mutli-threading and an interrupt
bit???
--------------------------------------------------------------------------------------*/
//~ PSEUDO CODE
//~ pc should be set, it is the "next" instruction to run
//~ load pc into mar (Memory Address Register)
//~ increment pc (program counter)
//~ check to ensure that pc is legal
//~ load mdr (Memory Data Register) based upon mar (Memory Address Register)
//~ move mdr to ir (Instruction Register)
//~ execute ir
//~ rinse and repeat (jump should work by simply changing pc)
//~ must ensure that context switch happens after execution
//~ The run routine will return an interrupt which tells the 
//~ interrupt handler what to do next
int Processor::run(){
  int interrupt = 0;
  for(uint i = 0; i < QUANTUM; i++){
    //~ load pc (Program Counter) into mar (Memory Address Register)
    MAR = PC;
    
    
    //~ increment pc
    PC++;
    
    
    //~ load mdr based upon mar (Memory Address Register)
    if(MAR > limit){
      cout << "simProc indicates a segmentation fault\n";
      cout << "simProc thinks limit is " << limit << endl;
      cout << "simProc thinks MAR is " << MAR << endl;
      
      return(1);
    }
    MDR = mainMemory.fetch(MAR); //Memory Address Register
    
    //~ move mdr (Memory Data Register) to ir (Instruction Register)
    IR = MDR;
    
    //~ execute ir (Instruction Register)
    //~ If run is the BIG KAHUNA for the processor in general, then
    //~ perform is the big kahuna within the run method.
    //~ this is where the command in the instruction register
    //~ actually causes an action to occur.
    interrupt = perform(IR);
    if(interrupt){//if not zero
      return interrupt;
    }
    //~ rinse and repeat (jump should work by simply changing pc)
    //~ must ensure that context switch happens AFTER execution
        
  }
  //~ quantum complete, so kernel is free to do a context switch 
  //~ back where it invoked run
  return 0;
  
}


//~ must  return a zero on any successful completion of command
//~ if unsuccessful, return a 1 which is an abend interrupt, the OS
//~ will remove the process from the processor and kill it.
int Processor::perform(string command){
  vector<string> tokens;
  
  //~ tokenize is defined within Tokenize.h It tokenizes the 
  //~ string and inserts the tokens in the returned vector.
  tokens = Tokenize(command, " \t");
  
  //~ cout << "performing command: " << command << endl;
  //~ for(uint i = 0; i < tokens.size(); i++){
    //~ cout << "\ttoken " << i << ": " << tokens[i] << endl;
  //~ }
  
  if(tokens[0] == "noop"){
    //~ do nothing
    return 0;
  }
  else if(tokens[0] == "jmp"){
    //~ Just change the PC, it is that simple
    //~ this one should really take an address, a 
    //~ register, or an indirect address 
    //~ printf("jumping to %s\n",tokens[1].c_str());
    PC = atoi(tokens[1].c_str());
    return 0;
  }else if(tokens[0] == "mov"){
    //~ MOV AL, 61h 
    //~ Move (really a copy) the hexadecimal value '61' into 
    //~ the processor register known as "AL". (The h-suffix means     
    //~ hexadecimal or = 97 in decimal)  */
    if(testReg(tokens[1])){
      return 1; //this is the interrupt that should occur
    }else{        //given a bad command (abbend)
      setReg(tokens[1], (word)atoi(tokens[2].c_str()));
      return 0;
    }
    
  }else if(tokens[0] == "inc"){
    if(testReg(tokens[1])){
      return 1; // returned int for bad command
    }else{
      word regVal = getReg(tokens[1]);
      regVal++;
      setReg(tokens[1],regVal);
      return 0;
    }
  
  }else if(tokens[0] == "dec"){
    if(testReg(tokens[1])){
      return 1; // returned int for bad command
    }else{
      word regVal = getReg(tokens[1]);
      regVal--;
      //~ printf("decrementing %s. ",tokens[1].c_str());
      //~ printf("It is now %d\n",(int)regVal);
      
      setReg(tokens[1],regVal);
      return 0;
    }
  
  }else if(tokens[0] == "add"){
    if(testReg(tokens[1]) || testReg(tokens[2])){
      return 1;// returned int for bad command
    }else{
      int addFrom = getReg(tokens[2]);
      int addTo = getReg(tokens[1]);
      setReg(tokens[1],addFrom+addTo);
      return 0;
    }

  }else if(tokens[0] == "mul"){
    if(testReg(tokens[1]) || testReg(tokens[2])){
      return 1;
    }else{
      int multFrom = getReg(tokens[2]);
      int multTo = getReg(tokens[1]);
      setReg(tokens[1],multFrom * multTo);
      return 0;
    }

  }else if(tokens[0] == "div"){
    if(testReg(tokens[1]) || testReg(tokens[2]) || getReg(tokens[2] )== 0){
      return 1;//this is an abend 
    }else{
      int divFrom = getReg(tokens[2]);
      int divTo = getReg(tokens[1]);
      setReg(tokens[1],divFrom * divTo);
      return 0;
    }

  }else if(tokens[0] == "jz"){
    //~ if the first register is zero jump to the address in sec reg
    //~ printf("got a jz\n");
    if(testReg(tokens[1]) || testReg(tokens[2])) {
      return 1;//this is an abend 
    }else{
      //~ printf("checking whether %s is zero\n",tokens[1].c_str());
      //~ printf("its contents is %d\n",(int)getReg(tokens[1]));
      if((int)getReg(tokens[1]) == 0){
        PC = getReg(tokens[2]);
      }
      return 0;
    }

  }else if(tokens[0] == "end"){
    return 2;// returned int for normal end of program
  }else{
    cout << "simProc reports unrecognized command: " << command << endl;
    return 1;
  }
  
}
  


//~ helper function. can just pass a string designation of register
word Processor::getReg(string regDesignator){
    if(regDesignator == "r1"){
      return getReg1();
    }else if(regDesignator == "r2"){
      return getReg2();
    }else if(regDesignator == "r3"){
      return getReg3();
    }else if(regDesignator == "r4"){
      return getReg4();
    }else if(regDesignator == "r5"){
      return getReg5();
    }else{
      printf("illegal register designator in setReg command\n");
      exit(1);//need to switch this to an abend interrupt
    }
  
}

//~ helper function. can just pass a string designation of register
void Processor::setReg(string regDesignator, word val){
    if(regDesignator == "r1"){
      setReg1(val);
    }else if(regDesignator == "r2"){
      setReg2(val);
    }else if(regDesignator == "r3"){
      setReg3(val);
    }else if(regDesignator == "r4"){
      setReg4(val);
    }else if(regDesignator == "r5"){
      setReg5(val);
    }else{
      printf("illegal register designator in setReg command\n");
      exit(1);//need to switch this to an abend interrupt
    }
  
}

//~ testReg returns zero if the passed register designator
//~ is proper (r1 through r5). This just made the logic cleaner.
//~ I could do a test reg, and if it is true I could return an 
//~ appropriate interrupt.
int   Processor::testReg(string regDesignator){
    if( regDesignator == "r1" ||
        regDesignator == "r2" ||
        regDesignator == "r3" ||
        regDesignator == "r4" ||
        regDesignator == "r5"){
      return 0;
    }else{
      return 1;
    }
  
}

