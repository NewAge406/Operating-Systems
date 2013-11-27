#ifndef HOUR_H
#define HOUR_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>//need for cout formatting
#include "Program.h"


using namespace std;




class Memory{ 
  public:
    Memory();
    ~Memory();
    static void load(Program &passedProg);
    static void dumpMem();
    static string fetch(int address);
  
  private:
    static vector<Program> listOfProgs;
    static vector<string> rawListOfCommands;
    
};

#endif //HOUR_H 

