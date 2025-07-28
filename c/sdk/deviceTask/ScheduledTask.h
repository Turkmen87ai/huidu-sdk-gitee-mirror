#ifndef SCHEDULEDTASK_H
#define SCHEDULEDTASK_H

#include "BaseClient.h"
#include "ScheduledTaskInfo.h"
#include "cJSON.h"
#include <stdlib.h>
#include <string.h>
#include "posixPortMemory.h"
// Planned task structure
typedef struct {
    BaseClient* baseClient;
} ScheduledTask;

// Create a scheduled task object
ScheduledTask* createScheduledTask();

// Destroy the planned task object
void destroyScheduledTask(ScheduledTask* task);

// Get a scheduled task (individual device ID)
char* getScheduledTaskSingle(ScheduledTask* task, const char* id);

// Get Scheduled Tasks (Multiple Device IDs)
char* getScheduledTask(ScheduledTask* task, const char** ids, int idCount, const char** taskNames, int taskNameCount);

// Set up scheduled tasks (individual device IDs)
char* setScheduledTaskSingle(ScheduledTask* task, const char* id, const char** keys, ScheduledTaskInfo*** taskInfos, const int* taskInfoCounts, int keyCount);

// Set up scheduled tasks (multiple device IDs)
char* setScheduledTask(ScheduledTask* task, const char** ids, int idCount,
    const char** keys, ScheduledTaskInfo*** taskInfos,
    const int* taskInfoCounts, int keyCount);

#endif // SCHEDULEDTASK_H