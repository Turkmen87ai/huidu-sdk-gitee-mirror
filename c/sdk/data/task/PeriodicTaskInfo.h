#ifndef PERIODICTASKINFO_H
#define PERIODICTASKINFO_H
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "posixPortMemory.h"
typedef struct {
    char* url;
    char* rege;
    int interval;
} PeriodicTaskInfo;

// Create a new object
PeriodicTaskInfo* createPeriodicTaskInfo();

// Deep copy constructors
PeriodicTaskInfo* copyPeriodicTaskInfo(const PeriodicTaskInfo* other);

// Free up memory
void destroyPeriodicTaskInfo(PeriodicTaskInfo* obj);

// Serialized as a JSON string
char* toJsonPeriodicTaskInfo(const PeriodicTaskInfo* obj);

// Parse the object from JSON
PeriodicTaskInfo* fromJsonPeriodicTaskInfo(const char* json_str);

#endif
