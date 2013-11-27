#ifndef PROG_H
#define PROG_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>//need for C++ style string
#include <string.h>//need for c style strings
#include <fstream>//needed for file io
#include <vector>//need for stl vector
#include <map>//need for stl vector

#include "Tokenize.h"
#include "PCB.h"


#define LINESIZE 1024
using namespace std;




class Program{ 
  public:
    Program();
    ~Program();
    PCB  getPCB();
    void load(string fileName);
    vector<string> getListOfCommands();
    void setBase(int);
    void setLimit(int);
    int getBase();
    int getLimit();
    int getID();
    void setID(int);
    void checkSyntax();
  private:
    PCB myPCB;
    int base;
    int limit;
    vector<string> listOfCommands;
    map<string,int> mapOfMarkers;
    int ID;
  
  
    //private helper functions
    void stripcomments(string &passedString, char *cstring);
    
    
};

#endif //PROG_H 

