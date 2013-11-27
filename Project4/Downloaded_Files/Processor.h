#ifndef PROC_H
#define PROC_H

#include <stdio.h>
#include <stdlib.h>

#include "Memory.h"
#include "Tokenize.h"

#include <iostream>
using namespace std;
#define QUANTUM 999

typedef long int word;


class Processor{ 
  public:
    Processor();
    ~Processor();
    int getMAR();
    void setMAR(int);
    string getMDR();
    void setMDR(string);
    int getPC();
    void setPC(int);
    string getIR();
    void setIR(string passedInst);
    int getBase();
    void setBase(int passedBase);
    int getLimit();
    void setLimit(int passedLimit);
    int run();
    int perform(string command);
  
    void setReg1(word);
    void setReg2(word);
    void setReg3(word);
    void setReg4(word);
    void setReg5(word);
    word getReg1();
    word getReg2();
    word getReg3();
    word getReg4();
    word getReg5();
    
    void incReg1();
    void incReg2();
    void incReg3();
    void incReg4();
    void incReg5();
    
    word getReg(string regDesignator);
    void setReg(string regDesignator, word val);
    int   testReg(string regDesignator);
  private:
    int MAR;//Memory Address Register
    string MDR;
    int PC;
    string IR;
    int base;
    int limit;
  
    word register1;
    word register2;
    word register3;
    word register4;
    word register5;
  
  
    Memory mainMemory;
  

};

#endif //PROC_H 

