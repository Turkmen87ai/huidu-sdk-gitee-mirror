#ifndef PERIODICTASK_H
#define PERIODICTASK_H

#include "BaseClient.h"
#include "PeriodicTaskInfo.h"
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "posixPortMemory.h"
// Periodic task structure
typedef struct {
    BaseClient* baseClient;  // Base client object
} PeriodicTask;

// Create a recurring task object
PeriodicTask* createPeriodicTask(const char* hostUrl);

// Destroy periodic task objects
void destroyPeriodicTask(PeriodicTask* task);

// Get a recurring task (individual device ID)
char* getPeriodicTaskSingle(PeriodicTask* task, const char* id);

// Get recurring tasks (multiple device IDs)
char* getPeriodicTask(PeriodicTask* task, const char** ids, int idCount);

// Set up recurring tasks (individual device IDs)
char* setPeriodicTaskSingle(PeriodicTask* task, const char* id, PeriodicTaskInfo** taskInfos, int taskInfoCount);

// Set up recurring tasks (multiple device IDs)
char* setPeriodicTask(PeriodicTask* task, const char** ids, int idCount, PeriodicTaskInfo** taskInfos, int taskInfoCount);

#endif // PERIODICTASK_H

