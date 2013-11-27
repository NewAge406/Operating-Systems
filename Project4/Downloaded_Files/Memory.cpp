#include "Memory.h"
vector<Program> Memory::listOfProgs;
vector<string> Memory::rawListOfCommands;
    

Memory::Memory(){
  
}


Memory::~Memory(){
}



void Memory::load(Program &passedProg){
  //~ list of progs is a vector of already loaded programs
  //~ the program being loaded will be added to this list
  //~ in this simplistic OS simulator the program ID will be the program's 
  //~ index into this list (which is the list's size since indexes start at 0)
  passedProg.setID(listOfProgs.size());
  
  //~ rawListOfCommands is the raw contents of memory
  //~ this program will be loaded immediately following the previous 
  //~ program. Therefore the base for the new program will be equal
  //~ to the size of the current raw list
  int base = rawListOfCommands.size();
  
  //~ the list of commands is simply a vector of strings each of which
  //~ is a line in the text file version of the program (all comments
  //~ stripped out and all blank lines stripped out)
  vector<string> passedProgComs = passedProg.getListOfCommands();
  
  
  //limit will be from there to the number of commands in program
  //then less one so it will be address of last command
  int limit = base + passedProgComs.size() -1;
  passedProg.setBase(base);
  
  //~ cout << "setting limit to " << limit << endl;
  passedProg.setLimit(limit);
  
  //~ The text versions of the programs allow the use of flags (or variables)
  //~ as markers for locations within the program. This way the assembly-
  //~ like language can jump to other locations within the program without
  //~ knowing the absolute address of that location. The check syntax 
  //~ command below converts all of these flags to absolute addresses
  //~ based upon the now set base and limit values.
  cout << "about to check syntax\n";
  passedProg.checkSyntax();
  
  //~ need to get the coms again since have scrubbed it for addressing
  passedProgComs = passedProg.getListOfCommands();
  
  //~ cout << "checking limit " << passedProg.getLimit() << endl;
  //~ cout << "about to insert program raw text\n";
  //~ cout << "will add " << passedProgComs.size() << " commands\n";
  
  //~ Adding the program's commands to memory (remember, 
  //~ rawListOfCommands IS the memory. 
  rawListOfCommands.reserve( rawListOfCommands.size() + passedProgComs.size());
  rawListOfCommands.insert(rawListOfCommands.end(),
                                            passedProgComs.begin(),
                                            passedProgComs.end());
   
  //~ The program has now been properly conditioned (markers converted
  //~ to absolute addresses, the base and limits set, and added to memory)
  //~ so now we can place the passed program into the Memory's (you
  //~ know, this class) listOfProgs. This list is just a storage location so that
  //~ the PCBs can be built.
  listOfProgs.push_back(passedProg);
}

//~ this dumps the raw list of commands to the screen. The raw list of commands
//~ is literally the contents of memory.
void Memory::dumpMem(){
  cout << "\n\n -----------------------dumping memory to screen------------------------\n";
  
  for(uint i  = 0; i < rawListOfCommands.size(); i++){
    cout << i << " |" << rawListOfCommands[i] << endl;
  }
  
  cout << "\nsize of raw list is " << rawListOfCommands.size() << endl;
  
  cout << "\nProg ID | Base | Limit\n";
  for(uint i  = 0; i < listOfProgs.size(); i++){
    cout << "   " << setw(5) << left<< listOfProgs[i].getID() << 
      "|" << "   " << setw(3) << left << listOfProgs[i].getBase() 
      << "|" << "   " << listOfProgs[i].getLimit() << endl;
  }
  
  
}


//~ this is the command that processor uses to retrieve the contents of memory
//~ at some location. Because this is a simplistic simulator the retrieved value
//~ is an assembly-language-like line of code. If this were a true processor/memory
//~ interaction, the returned value would be in machine code.
string Memory::fetch(int address){
  if(address >= (int)rawListOfCommands.size()){
    cout << "simMem reports a segmentation fault\n";
  }
  return rawListOfCommands[address];
}


