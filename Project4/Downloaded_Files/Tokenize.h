#ifndef TOK_H
#define TOK_H

#include <stdio.h>
#include <stdlib.h>
#include <string>//need for C++ style string
#include <fstream>//needed for file io
#include <vector>//need for stl vector
#include <iomanip>//need for cout formatting
using namespace std;

vector<string> Tokenize(string str,
                      string delimiters = " ");


#endif

