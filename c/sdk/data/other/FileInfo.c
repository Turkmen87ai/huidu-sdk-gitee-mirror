#include "FileInfo.h"

FileInfo* createFileInfo(char* localFile) {
    FileInfo* info = (FileInfo*)hdmalloc(sizeof(FileInfo));
    if (info) {
        info->localFile = localFile ? strdup(localFile) : NULL;
        info->url = NULL;
        info->size = 0;
        info->md5 = NULL;
    }
    return info;
}

void destroyFileInfo(FileInfo* info) {
    if (!info) {
        return;
    }
    hdfree(info->localFile);
    hdfree(info->url);
    hdfree(info->md5);
    hdfree(info);
}

FileInfo* copyFileInfo(const FileInfo* src) {
    if (!src) {
        return NULL;
    }
    FileInfo* dest = createFileInfo(src->localFile);
    if (dest) {
        if (src->url) dest->url = strdup(src->url);
        dest->size = src->size;
        if (src->md5) dest->md5 = strdup(src->md5);
    }
    return dest;
}

bool equalsFileInfo(const FileInfo* info1, const FileInfo* info2) {
    if (info1 == info2) {
        return true;
    }
    if (!info1 || !info2) {
        return false;
    }

    if (info1->localFile == info2->localFile) {
        return true;
    }
    if (info1->localFile && info2->localFile) {
        bool equal = (strcmp(info1->localFile, info2->localFile) == 0);
        if (equal && strlen(info1->localFile) > 0) {
            return true;
        }
    }

    if (info1->url && info2->url && strcmp(info1->url, info2->url) == 0) {
        return true;
    }

    if (info1->md5 && info2->md5 && strcmp(info1->md5, info2->md5) == 0) {
        return true;
    }

    return false;
}

cJSON* toJsonFileInfo(const FileInfo* info) {
    if (!info) {
        return NULL;
    }
    cJSON* json = cJSON_CreateObject();
    if (info->localFile) {
        cJSON_AddStringToObject(json, "localFile", info->localFile);
    }
    if (info->url) {
        cJSON_AddStringToObject(json, "url", info->url);
    }
    cJSON_AddNumberToObject(json, "size", info->size);
    if (info->md5) {
        cJSON_AddStringToObject(json, "md5", info->md5);
    }
    return json;
}

FileInfo* FileInfo_fromJson(const cJSON* json) {
    if (!json) {
        return NULL;
    }
    const cJSON* localFile = cJSON_GetObjectItem(json, "localFile");
    if (!localFile || !cJSON_IsString(localFile)) {
        return NULL;
    }
    FileInfo* info = createFileInfo(localFile->valuestring);
    if (!info) {
        return NULL;
    }
    const cJSON* url = cJSON_GetObjectItem(json, "url");
    if (url && cJSON_IsString(url)) {
        info->url = strdup(url->valuestring);
    }

    const cJSON* size = cJSON_GetObjectItem(json, "size");
    if (size && cJSON_IsNumber(size)) {
        info->size = size->valueint;
    }

    const cJSON* md5 = cJSON_GetObjectItem(json, "md5");
    if (md5 && cJSON_IsString(md5)) {
        info->md5 = strdup(md5->valuestring);
    }

    return info;
}

