#include "Program.h"

//~ constructor. all have to do is initialize this programs associated
//~ PCB
Program::Program(){
  initializePCB(&myPCB);
}

PCB Program::getPCB(){
  return myPCB;
}

//~ destructor. no action needed
Program::~Program(){
  
}


//~ load the program from the designated file.
//~ put each line of code in the listOfCommands 
//~ data structure.
void Program::load(string fileName){
  ifstream inputStream;
  
  inputStream.open(fileName.c_str());
  //theProg is a vector of strings
  
  if( !inputStream ) {
    cerr << "Error opening input stream" << endl;
    exit(0);
  }
  
  //we are loading so clear out any prog that was around before
  listOfCommands.clear();
  
  
  string inputString;
  char cstring[LINESIZE];
  
  //use getline because stream indirection (>>) ignors white space like
  //newlines and tabs
  while(inputStream.getline(cstring, LINESIZE)){
    //~ convert c style string into string class
    inputString = cstring;
    
    //strip comments
    stripcomments(inputString,cstring);

    //~ if blank line  can ignore. Can tell blank if first char is null
    if(cstring[0]  != (char)0){//null char first char so get rid of
      listOfCommands.push_back(inputString);
    }
    
    //~ so the list of commands is simply a list of the raw strings 
    //~ that were in the program text file

    
  }
  
  
  inputStream.close();
  
  //~ //The following was for validation purposes
  //~ for(uint i = 0; i < listOfCommands.size(); i++){
    //~ cout << listOfCommands[i] << endl;
  //~ }
  
  
  
}

void Program::stripcomments(string &passedString, char *cstring){
  string comment;
          
  if(passedString.find("#") != string::npos){
    //~ found a comment
    string::size_type loc = passedString.find("#");
    comment = passedString.substr(loc);
    //~ cout << "found a comment:"<< comment << endl;
    cstring[loc] = 0;
    passedString = cstring;

  }
}


//~ this is like the compiler. It looks for flags/markers
//~ in the assembly code, determines which memory 
//~ address they represent (relative to the base)
//~ and then replaces all instances where that marker
//~ is referenced with that address. Allows for the use
//~ of a variable name in jump statements.
void Program::checkSyntax(){
  
  string workingString;
  char cstring[LINESIZE];
  string command;
  char *nextTok = 0;
  
  //~ make a pass to find markers and put in map
  cout << "making a pass to find markers\n";
  for(uint i = 0; i < listOfCommands.size(); i++){
    workingString = listOfCommands[i];
    strcpy(cstring,workingString.c_str());
    if(cstring[0]  == '\t'){//first char is a tab, so it is a command
      //~ cout << "first char is a tab\n";
      //~ This is an actual command
      //~ nextTok = strtok(cstring," \t");
      //~ cout << "-----------found a command. The first token is: " << nextTok << endl;
      listOfCommands[i] = cstring + 1;//get rid of \t and get rid of strtok can inserts 0's
      
    }else{
      //~ found a marker, stick it in a map
      nextTok = strtok(cstring," \t");
      cout<< "\tfound a marker, it is: " << nextTok << endl;
      //~ address is i
      //~ map the token to the address
      string marker = nextTok;
      
      if(mapOfMarkers.find(marker) == mapOfMarkers.end()){//not in map
        cout << "\tputting the marker in the map\n";
        mapOfMarkers.insert(make_pair(marker,i));
        
        listOfCommands[i] = ""; //empty the line
        while( (nextTok = strtok(NULL," \t")) ){
          //~ cout << "in while, nextTok is: " << nextTok << endl;
          listOfCommands[i] += nextTok;
          listOfCommands[i] += " ";
        }
        
        cout << "\tremoved the marker\n";
        cout << "\tcommand is now: " << listOfCommands[i] << endl;
      }else{
        cout << "marker was already in the map\n";
        cout << "this is a compile error!!!!\n\n\n";
        exit(0);return;
      }
    }
  }
  
  cout << "making a pass to replace markers with addresses\n";
  for(uint i = 0; i < listOfCommands.size(); i++){
    string command = listOfCommands[i];
    map<string,int>::iterator iter;
    char cstring[LINESIZE];
    
    for(iter = mapOfMarkers.begin(); iter != mapOfMarkers.end(); iter++){
      string marker = iter->first;
      int val = iter->second;
      //~ cout << marker << " " << val << endl;
      string::size_type loc = command.find( marker);
      
      if(loc != string::npos){//found it
        cout << "\tfound an instance of " << marker << endl;
        cout << "\treplacing it\n";
        cout << "\tthe command begins as: " << command << endl;
        sprintf(cstring,"%d",val+base);
        command.replace(loc,marker.size(),cstring);
        cout << "\tthe command is now: " << command << endl;
        listOfCommands[i] = command;
        
      }
    }
  }
  
  cout << "\n\ndump of program\n";
  for(uint i = 0; i < listOfCommands.size(); i++){
    
    cout << i << " " << listOfCommands[i] << endl;
  }
  
  

  
  
}


vector<string> Program::getListOfCommands(){
  return listOfCommands;
}
  


void Program::setBase(int passedBase){
  base = passedBase;
    /*-----------------------------------------------------------------------------------------
    -----------------------------------------------------------------------------------------
            TODO: Set the base field for this program's PCB to 
                        the passed base value. Also, set the PCB's 
                        PC (program counter) field to the passed 
                        base value. This makes sense because if we
                        are setting the base it has not run yet and 
                        therefore the first instruction will reside 
                        at the address of the base.
                        The program's PCB is called myPCB
    -----------------------------------------------------------------------------------------
 ---------------------------------------------------------------------------------------*/
   myPCB.PC = base;
   myPCB.base = base;
}

void Program::setLimit(int passedLimit){
  limit = passedLimit;
    /*-----------------------------------------------------------------------------------------
    -----------------------------------------------------------------------------------------
            TODO: Set the limit field for this program's PCB to 
                        the passed limit value. 
    -----------------------------------------------------------------------------------------
    ---------------------------------------------------------------------------------------*/
  
  myPCB.limit = limit;
}

int Program::getBase(){
  return base;
}
int Program::getLimit(){
  return limit;
}


int Program::getID(){
  return ID;
}

void Program::setID(int passedID){
  ID = passedID;
    /*-----------------------------------------------------------------------------------------
    -----------------------------------------------------------------------------------------
            TODO: Set the ID field for this program's PCB to 
                        the passed ID value. 
    -----------------------------------------------------------------------------------------
    ---------------------------------------------------------------------------------------*/
  myPCB.ID = ID;
  
}


