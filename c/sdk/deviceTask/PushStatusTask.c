#include "PushStatusTask.h"

PushStatusTask* createPushStatusTask() {
    PushStatusTask* task = (PushStatusTask*)hdmalloc(sizeof(PushStatusTask));
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

void destroyPushStatusTask(PushStatusTask* task) {
    if (!task) {
        return;
    }
    if (task->baseClient) {
        destroyBaseClient(task->baseClient);
    }
    hdfree(task);
}

static char* keyValueToJson(const char* key, const char* value) {
    cJSON* json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, key, value);
    char* jsonStr = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);
    return jsonStr;
}

static char* keyValuesToJson(const char** keys, const char** values, int count) {
    cJSON* json = cJSON_CreateObject();
    for (int i = 0; i < count; i++) {
        cJSON_AddStringToObject(json, keys[i], values[i]);
    }
    char* jsonStr = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);
    return jsonStr;
}

char* pushStatusSingle(PushStatusTask* task, const char* id, const char* key, const char* value) {
    if (!task || !task->baseClient || !id || !key || !value) {
        return toJsonObject("{\"message\":\"failed\",\"data\":\"Invalid parameters\"}");
    }

    char* data = keyValueToJson(key, value);
    const char* ids[] = { id };
    char* result = deviceBaseClient(task->baseClient, ids, 1, "pushStatus", data);
    hdfree(data);
    return result;
}

char* pushStatusSingleMap(PushStatusTask* task, const char* id, const char** keys, const char** values, int count) {
    if (!task || !task->baseClient || !id || !keys || !values || count <= 0) {
        return toJsonObject("{\"message\":\"failed\",\"data\":\"Invalid parameters\"}");
    }

    char* data = keyValuesToJson(keys, values, count);
    const char* ids[] = { id };
    char* result = deviceBaseClient(task->baseClient, ids, 1, "pushStatus", data);
    hdfree(data);
    return result;
}

char* pushStatusMultiSingle(PushStatusTask* task, const char** ids, int idCount, const char* key, const char* value) {
    if (!task || !task->baseClient || !ids || idCount <= 0 || !key || !value) {
        return toJsonObject("{\"message\":\"failed\",\"data\":\"Invalid parameters\"}");
    }

    char* data = keyValueToJson(key, value);
    char* result = deviceBaseClient(task->baseClient, ids, idCount, "pushStatus", data);
    hdfree(data);
    return result;
}

char* pushStatusMultiMap(PushStatusTask* task, const char** ids, int idCount, const char** keys, const char** values, int kvCount) {
    if (!task || !task->baseClient || !ids || idCount <= 0 || !keys || !values || kvCount <= 0) {
        return toJsonObject("{\"message\":\"failed\",\"data\":\"Invalid parameters\"}");
    }

    char* data = keyValuesToJson(keys, values, kvCount);
    char* result = deviceBaseClient(task->baseClient, ids, idCount, "pushStatus", data);
    hdfree(data);
    return result;
}
