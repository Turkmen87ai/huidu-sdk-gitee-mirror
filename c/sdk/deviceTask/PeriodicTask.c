#include "PeriodicTask.h"

PeriodicTask* createPeriodicTask(const char* hostUrl) {
    PeriodicTask* task = (PeriodicTask*)hdmalloc(sizeof(PeriodicTask));
    if (!task) {
        return NULL;
    }

    task->baseClient = createWithHostBaseClient(hostUrl);
    if (!task->baseClient) {
        hdfree(task);
        return NULL;
    }
    return task;
}

void destroyPeriodicTask(PeriodicTask* task) {
    if (!task) {
        return;
    }

    if (task->baseClient) {
        destroyBaseClient(task->baseClient);
    }
    hdfree(task);
}

char* getPeriodicTaskSingle(PeriodicTask* task, const char* id) {
    return getPeriodicTask(task, &id, 1);
}

char* getPeriodicTask(PeriodicTask* task, const char** ids, int idCount) {
    if (!task || !task->baseClient) {
        return toJsonObject("{\"message\":\"failed\",\"data\":\"Invalid task\"}");
    }
    return deviceBaseClient(task->baseClient, ids, idCount, "getPeriodicTask", NULL);
}

char* setPeriodicTaskSingle(PeriodicTask* task, const char* id, PeriodicTaskInfo** taskInfos, int taskInfoCount) {
    return setPeriodicTask(task, &id, 1, taskInfos, taskInfoCount);
}

char* setPeriodicTask(PeriodicTask* task, const char** ids, int idCount, PeriodicTaskInfo** taskInfos, int taskInfoCount) {
    if (!task || !task->baseClient || !taskInfos || taskInfoCount <= 0) {
        return toJsonObject("{\"message\":\"failed\",\"data\":\"Invalid parameters\"}");
    }

    // Create a JSON array of task information
    cJSON* taskArray = cJSON_CreateArray();
    for (int i = 0; i < taskInfoCount; i++) {
        char* jsonStr = toJsonPeriodicTaskInfo(taskInfos[i]);
        cJSON* jsonObj = cJSON_Parse(jsonStr);
        hdfree(jsonStr);

        if (jsonObj) {
            cJSON_AddItemToArray(taskArray, jsonObj);
        }
    }

    char* dataStr = cJSON_PrintUnformatted(taskArray);
    cJSON_Delete(taskArray);

    // Calls the device operation method of the underlying client
    char* result = deviceBaseClient(task->baseClient, ids, idCount, "setPeriodicTask", dataStr);
    hdfree(dataStr);
    return result;
}

