#include "PeriodicTaskInfo.h"

PeriodicTaskInfo* createPeriodicTaskInfo() {
    PeriodicTaskInfo* obj = (PeriodicTaskInfo*)hdmalloc(sizeof(PeriodicTaskInfo));
    if (obj) {
        obj->url = NULL;
        obj->rege = NULL;
        obj->interval = 0;
    }
    return obj;
}

PeriodicTaskInfo* copyPeriodicTaskInfo(const PeriodicTaskInfo* other) {
    if (!other) return NULL;

    PeriodicTaskInfo* obj = createPeriodicTaskInfo();
    if (obj) {
        if (other->url) {
            obj->url = strdup(other->url);
        }
        if (other->rege) {
            obj->rege = strdup(other->rege);
        }
        obj->interval = other->interval;
    }
    return obj;
}

void destroyPeriodicTaskInfo(PeriodicTaskInfo* obj) {
    if (obj) {
        hdfree(obj->url);
        hdfree(obj->rege);
        hdfree(obj);
    }
}

char* toJsonPeriodicTaskInfo(const PeriodicTaskInfo* obj) {
    if (!obj) return NULL;

    cJSON* json = cJSON_CreateObject();
    if (obj->url) {
        cJSON_AddStringToObject(json, "url", obj->url);
    }
    else {
        cJSON_AddNullToObject(json, "url");
    }

    if (obj->rege) {
        cJSON_AddStringToObject(json, "rege", obj->rege);
    }
    else {
        cJSON_AddNullToObject(json, "rege");
    }

    cJSON_AddNumberToObject(json, "interval", obj->interval);

    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);
    return json_str;
}

PeriodicTaskInfo* fromJsonPeriodicTaskInfo(const char* json_str) {
    if (!json_str) return NULL;

    cJSON* json = cJSON_Parse(json_str);
    if (!json) return NULL;

    PeriodicTaskInfo* obj = createPeriodicTaskInfo();
    if (obj) {
        cJSON* item = cJSON_GetObjectItem(json, "url");
        if (item && !cJSON_IsNull(item)) {
            obj->url = strdup(item->valuestring);
        }

        item = cJSON_GetObjectItem(json, "rege");
        if (item && !cJSON_IsNull(item)) {
            obj->rege = strdup(item->valuestring);
        }

        item = cJSON_GetObjectItem(json, "interval");
        if (item) {
            obj->interval = item->valueint;
        }
    }

    cJSON_Delete(json);
    return obj;
}

