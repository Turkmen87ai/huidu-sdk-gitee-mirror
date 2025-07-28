#include "ScheduledTask.h"

// 创建计划任务对象
ScheduledTask* createScheduledTask() {
    ScheduledTask* task = (ScheduledTask*)hdmalloc(sizeof(ScheduledTask));
    if (!task) {
        return NULL;
    }
    task->baseClient = createBaseClient();
    if (!task->baseClient) {
        hdfree(task);
        return NULL;
    }
    return task;
}

// 销毁计划任务对象
void destroyScheduledTask(ScheduledTask* task) {
    if (!task) {
        return;
    }
    if (task->baseClient) {
        destroyBaseClient(task->baseClient);
    }
    hdfree(task);
}

// 获取计划任务（单个设备ID）
char* getScheduledTaskSingle(ScheduledTask* task, const char* id) {
    return getScheduledTask(task, &id, 1, NULL, 0);
}

// 获取计划任务（多个设备ID）
char* getScheduledTask(ScheduledTask* task, const char** ids, int idCount, const char** taskNames, int taskNameCount) {
    if (!task || !task->baseClient || !ids || idCount <= 0) {
        return toJsonObject("{\"message\":\"failed\",\"data\":\"Invalid parameters\"}");
    }

    // 将任务名称数组转换为JSON数组
    cJSON* taskArray = NULL;
    if (taskNames && taskNameCount > 0) {
        taskArray = cJSON_CreateArray();
        for (int i = 0; i < taskNameCount; i++) {
            cJSON_AddItemToArray(taskArray, cJSON_CreateString(taskNames[i]));
        }
    }

    char* data = taskArray ? cJSON_PrintUnformatted(taskArray) : NULL;
    if (taskArray) {
        cJSON_Delete(taskArray);
    }
    char* result = deviceBaseClient(task->baseClient, ids, idCount, "getScheduledTask", data);
    if (data) {
        hdfree(data);
    }
    return result;
}

// 设置计划任务（单个设备ID）
char* setScheduledTaskSingle(ScheduledTask* task, const char* id, const char** keys, ScheduledTaskInfo*** taskInfos, const int* taskInfoCounts, int keyCount) {
    return setScheduledTask(task, &id, 1, keys, taskInfos, taskInfoCounts, keyCount);
}

// 设置计划任务（多个设备ID）
char* setScheduledTask(ScheduledTask* task, const char** ids, int idCount,
    const char** keys, ScheduledTaskInfo*** taskInfos,
    const int* taskInfoCounts, int keyCount) {
    if (!task || !task->baseClient || !ids || idCount <= 0 ||
        !keys || !taskInfos || !taskInfoCounts || keyCount <= 0) {
        return toJsonObject("{\"message\":\"failed\",\"data\":\"Invalid parameters\"}");
    }

    // 创建主JSON对象
    cJSON* root = cJSON_CreateObject();

    // 为每个键添加任务信息数组
    for (int i = 0; i < keyCount; i++) {
        cJSON* taskArray = cJSON_CreateArray();
        for (int j = 0; j < taskInfoCounts[i]; j++) {
            char* taskJson = toJsonScheduledTaskInfo(taskInfos[i][j]);
            cJSON* taskObj = cJSON_Parse(taskJson);
            hdfree(taskJson);
            if (taskObj) {
                cJSON_AddItemToArray(taskArray, taskObj);
            }
        }
        cJSON_AddItemToObject(root, keys[i], taskArray);
    }

    char* data = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);

    char* result = deviceBaseClient(task->baseClient, ids, idCount, "setScheduledTask", data);
    hdfree(data);

    return result;
}

