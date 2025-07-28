#ifndef PROGRAM_H
#define PROGRAM_H
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "BaseClient.h"
#include "ProgramNode.h"
#include "posixPortMemory.h"

// Program client structure
typedef struct {
    BaseClient* baseClient;
    char* dataEx; // A JSON string for storing additional data.
} ProgramClient;

// Create program client.
ProgramClient* createProgramClient();

// Release program client
void destroyProgramClient(ProgramClient* program);

// Set additional data.
void setDataExProgramClient(ProgramClient* program, const char* dataEx);

// Additional programs (multiple programs)
char* appendProgramClient(ProgramClient* program, const char** ids, int idCount,
    ProgramNode** nodes, int nodeCount);

// Additional Program (Single Program)
char* appendSingleProgramClient(ProgramClient* program, const char** ids, int idCount,
    ProgramNode* node);

// Update programs (multiple programs)
char* updateProgramClient(ProgramClient* program, const char** ids, int idCount,
    ProgramNode** nodes, int nodeCount);

// Update Program (Single Program)
char* updateSingleProgramClient(ProgramClient* program, const char** ids, int idCount,
    ProgramNode* node);

// Replace Programs (Multiple Programs)
char* replaceProgramClient(ProgramClient* program, const char** ids, int idCount,
    ProgramNode** nodes, int nodeCount);

// Replace Program (Single Program)
char* replaceSingleProgramClient(ProgramClient* program, const char** ids, int idCount,
    ProgramNode* node);

// Delete the program
char* removeProgramClient(ProgramClient* program, const char** ids, int idCount,
    const char** programIds, int programIdCount);

// Obtain the list of program IDs.
char* getProgramIdsProgramClient(ProgramClient* program, const char** ids, int idCount);

#endif

