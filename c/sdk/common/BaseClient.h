#ifndef BASECLIENT_H
#define BASECLIENT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "cJSON.h"
#include "HttpApi.h"
#include "ProgramNode.h"
#include "AreaNode.h"
#include "FileInfo.h"
#include "posixPortMemory.h"
#include <stddef.h>
// Basic Client Structure
typedef struct {
    HttpApi* httpClient;
} BaseClient;

// Convert the string into a JSON object string.
char* toJsonObject(const char* data);

// Create a base client
BaseClient* createBaseClient();

// Set the host URL
BaseClient* createWithHostBaseClient(const char* hostUrl);

// Free the base client
void destroyBaseClient(BaseClient* client);

// Get a list of devices
char* getDeviceBaseClient(BaseClient* client);

// Equipment operation
char* deviceBaseClient(BaseClient* client, const char** devIds, int devIdCount,
    const char* method, const char* data);
	
// File upload
char* fileBaseClient(BaseClient* client, const char* filePath);

// Upload and update files
cJSON* uploadAndUpdateFiles(BaseClient* bc, ProgramNode** programNodes, int nodeCount);

// Program operation
char* programBaseClient(BaseClient* client, const char** devIds, int devIdCount,
    const char* method, ProgramNode** programNodes, int nodeCount,
    const char* dataEx);

#endif
