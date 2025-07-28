#ifndef PUSHSTATUSTASK_H
#define PUSHSTATUSTASK_H
#include "BaseClient.h"
#include "cJSON.h"
#include <stdlib.h>
#include <string.h>
#include "posixPortMemory.h"
// Push state task structure
typedef struct {
    BaseClient* baseClient;
} PushStatusTask;

// Create a push status task object
PushStatusTask* createPushStatusTask();

// Destroy the push status task object
void destroyPushStatusTask(PushStatusTask* task);

// Convert key-value pairs to JSON strings
static char* keyValueToJson(const char* key, const char* value);

// Convert multiple key-value pairs to JSON strings
static char* keyValuesToJson(const char** keys, const char** values, int count);

// Push status (individual device ID, single key-value pair)
char* pushStatusSingle(PushStatusTask* task, const char* id, const char* key, const char* value);

// Push status (single device ID, multiple key-value pairs)
char* pushStatusSingleMap(PushStatusTask* task, const char* id, const char** keys, const char** values, int count);

// Push status (multiple device IDs, single key-value pairs)
char* pushStatusMultiSingle(PushStatusTask* task, const char** ids, int idCount, const char* key, const char* value);

// Push status (multiple device IDs, multiple key-value pairs)
char* pushStatusMultiMap(PushStatusTask* task, const char** ids, int idCount, const char** keys, const char** values, int kvCount);

#endif // PUSHSTATUSTASK_H