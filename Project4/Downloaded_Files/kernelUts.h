#include "Processor.h"
#include "Memory.h"
#include "queue.h"
#include "Program.h"

#include <string>//need for C++ style string
#include <fstream>//needed for file io
#include <vector>//need for stl vector
#include <iomanip>//need for cout formatting

#define NUMINTS 16

//the following are useful for file system stuff
//directory listings, etc.
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>


/*------------------------------------------------------------
                        GLOBAL VARIABLES
------------------------------------------------------------*/
Memory mainMemory;
Processor myProc;

PCB **readyHead;
PCB **readyTail;

Program myProg;
PCB currentRunningPCB;


/*------------------------------------------------------------
                            PROTOTYPES
------------------------------------------------------------*/
void (*ISV[NUMINTS])(); //interrupt service vector
void initializeISV();
void performContextSwitch();
void performAbend();
void performNormalEnd();
void dispatch(PCB passedPCB);
void removeCurrentFromProc();
void loadProgs();
