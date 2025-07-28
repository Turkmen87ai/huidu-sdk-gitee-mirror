#ifndef SCHEDULEDTASKINFO_H
#define SCHEDULEDTASKINFO_H
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "posixPortMemory.h"
typedef struct {
    char* timeRange;   ///< hh:mm:ss~hh:mm:ss
    char* dateRange;   ///< yyyy-MM-DD~yyyy-MM-DD
    char* weekFilter;  ///< Mon,Tue,Wed,Thu,Fri,Sat,Sun
    char* montFilter;  ///< Jan,Feb,Mar,Apr,May,Jun,Jul,Aug,Sep,Oct,Nov,Dec
    char* data;        ///< String data
} ScheduledTaskInfo;

// Create a new object.
ScheduledTaskInfo* createScheduledTaskInfo();

// copy constructor
ScheduledTaskInfo* copyScheduledTaskInfo(const ScheduledTaskInfo* other);

// Release memory
void destroyScheduledTaskInfo(ScheduledTaskInfo* obj);

// Set field value
void setTimeRangeScheduledTaskInfo(ScheduledTaskInfo* info, const char* value);
void setDateRangeScheduledTaskInfo(ScheduledTaskInfo* info, const char* value);
void setWeekFilterScheduledTaskInfo(ScheduledTaskInfo* info, const char* value);
void setMontFilterScheduledTaskInfo(ScheduledTaskInfo* info, const char* value);
void setDataScheduledTaskInfo(ScheduledTaskInfo* info, const char* value);

// Obtain field value
const char* getTimeRangeScheduledTaskInfo(const ScheduledTaskInfo* info);
const char* getDateRangeScheduledTaskInfo(const ScheduledTaskInfo* info);
const char* getWeekFilterScheduledTaskInfo(const ScheduledTaskInfo* info);
const char* getMontFilterScheduledTaskInfo(const ScheduledTaskInfo* info);
const char* getDataScheduledTaskInfo(const ScheduledTaskInfo* info);

// Serialized to a JSON string.
char* toJsonScheduledTaskInfo(const ScheduledTaskInfo* obj);

// Parse the object from JSON.
ScheduledTaskInfo* fromJsonScheduledTaskInfo(const char* json_str);

#endif
