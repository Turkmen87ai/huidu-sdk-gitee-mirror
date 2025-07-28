#ifndef FILE_H
#define FILE_H
#include <stdlib.h>
#include "BaseClient.h"
#include "posixPortMemory.h"
// File operation structure
typedef struct {
    BaseClient* baseClient;
} FileClient;

// Create a file client instance.
FileClient* createFileClient(const char* hostUrl);

// Release the file client instance.
void freeFileClient(FileClient* file);

// Set the host URL.
void setHostUrlFileClient(FileClient* file, const char* hostUrl);

// Upload file
char* uploadFileFileClient(FileClient* file, const char* filePath);

#endif
