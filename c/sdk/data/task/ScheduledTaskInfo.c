#include "ScheduledTaskInfo.h"

ScheduledTaskInfo* createScheduledTaskInfo() {
    ScheduledTaskInfo* obj = (ScheduledTaskInfo*)hdmalloc(sizeof(ScheduledTaskInfo));
    if (obj) {
        obj->timeRange = NULL;
        obj->dateRange = NULL;
        obj->weekFilter = NULL;
        obj->montFilter = NULL;
        obj->data = NULL;
    }
    return obj;
}

ScheduledTaskInfo* copyScheduledTaskInfo(const ScheduledTaskInfo* other) {
    if (!other) return NULL;

    ScheduledTaskInfo* obj = createScheduledTaskInfo();
    if (obj) {
        if (other->timeRange) {
            obj->timeRange = strdup(other->timeRange);
        }
        if (other->dateRange) {
            obj->dateRange = strdup(other->dateRange);
        }
        if (other->weekFilter) {
            obj->weekFilter = strdup(other->weekFilter);
        }
        if (other->montFilter) {
            obj->montFilter = strdup(other->montFilter);
        }
        if (other->data) {
            obj->data = strdup(other->data);
        }
    }
    return obj;
}

void destroyScheduledTaskInfo(ScheduledTaskInfo* obj) {
    if (obj) {
        hdfree(obj->timeRange);
        hdfree(obj->dateRange);
        hdfree(obj->weekFilter);
        hdfree(obj->montFilter);
        hdfree(obj->data);
        hdfree(obj);
    }
}

void setTimeRangeScheduledTaskInfo(ScheduledTaskInfo* info, const char* value) {
    if (info) {
        hdfree(info->timeRange);
        info->timeRange = strdup(value);
    }
}

void setDateRangeScheduledTaskInfo(ScheduledTaskInfo* info, const char* value) {
    if (info) {
        hdfree(info->dateRange);
        info->dateRange = strdup(value);
    }
}

void setWeekFilterScheduledTaskInfo(ScheduledTaskInfo* info, const char* value) {
    if (info) {
        hdfree(info->weekFilter);
        info->weekFilter = strdup(value);
    }
}

void setMontFilterScheduledTaskInfo(ScheduledTaskInfo* info, const char* value) {
    if (info) {
        hdfree(info->montFilter);
        info->montFilter = strdup(value);
    }
}

void setDataScheduledTaskInfo(ScheduledTaskInfo* info, const char* value) {
    if (info) {
        hdfree(info->data);
        info->data = strdup(value);
    }
}

const char* getTimeRangeScheduledTaskInfo(const ScheduledTaskInfo* info) {
    return info ? info->timeRange : NULL;
}

const char* getDateRangeScheduledTaskInfo(const ScheduledTaskInfo* info) {
    return info ? info->dateRange : NULL;
}

const char* getWeekFilterScheduledTaskInfo(const ScheduledTaskInfo* info) {
    return info ? info->weekFilter : NULL;
}

const char* getMontFilterScheduledTaskInfo(const ScheduledTaskInfo* info) {
    return info ? info->montFilter : NULL;
}

const char* getDataScheduledTaskInfo(const ScheduledTaskInfo* info) {
    return info ? info->data : NULL;
}

char* toJsonScheduledTaskInfo(const ScheduledTaskInfo* obj) {
    if (!obj) {
        return NULL;
    }
    cJSON* json = cJSON_CreateObject();

    cJSON_AddStringToObject(json, "timeRange", obj->timeRange ? obj->timeRange : NULL);
    cJSON_AddStringToObject(json, "dateRange", obj->dateRange ? obj->dateRange : NULL);
    cJSON_AddStringToObject(json, "weekFilter", obj->weekFilter ? obj->weekFilter : NULL);
    cJSON_AddStringToObject(json, "montFilter", obj->montFilter ? obj->montFilter : NULL);
    cJSON_AddStringToObject(json, "data", obj->data ? obj->data : NULL);

    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);
    return json_str;
}

ScheduledTaskInfo* fromJsonScheduledTaskInfo(const char* json_str) {
    if (!json_str) {
        return NULL;
    }
    cJSON* json = cJSON_Parse(json_str);
    if (!json) {
        return NULL;
    }
    ScheduledTaskInfo* obj = createScheduledTaskInfo();
    if (obj) {
        cJSON* item = NULL;
        item = cJSON_GetObjectItemCaseSensitive(json, "timeRange");
        if (cJSON_IsString(item)) {
            obj->timeRange = strdup(item->valuestring);
        }

        item = cJSON_GetObjectItemCaseSensitive(json, "dateRange");
            if (cJSON_IsString(item)) {
                obj->dateRange = strdup(item->valuestring);
            }

        item = cJSON_GetObjectItemCaseSensitive(json, "weekFilter");
        if (cJSON_IsString(item)) {
            obj->weekFilter = strdup(item->valuestring);
        }

        item = cJSON_GetObjectItemCaseSensitive(json, "montFilter");
        if (cJSON_IsString(item)) {
            obj->montFilter = strdup(item->valuestring);
        }

        item = cJSON_GetObjectItemCaseSensitive(json, "data");
        if (cJSON_IsString(item)) {
            obj->data = strdup(item->valuestring);
        }
    }

    cJSON_Delete(json);
    return obj;
}

