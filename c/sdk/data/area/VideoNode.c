#include "VideoNode.h"

VideoNode* createVideoNode() {
    VideoNode* node = (VideoNode*)hdmalloc(sizeof(VideoNode));
    if (!node) {
        return NULL;
    }

    node->base = createContentNode();
    setTypeContentNode(node->base, "video");

    node->localPath = NULL;
    node->file = NULL;
    node->fileSize = 0;
    node->fileMd5 = NULL;
    node->aspectRatio = false;
    return node;
}

VideoNode* createWithPathVideoNode(const char* localPath) {
    VideoNode* node = createVideoNode();
    if (node && localPath) {
        node->localPath = strdup(localPath);
    }
    return node;
}

VideoNode* createWithUrlFileSizeMd5VideoNode(const char* fileUrl, int fileSize, const char* fileMd5) {
    VideoNode* node = createVideoNode();
    if (fileUrl) {
        node->file = strdup(fileUrl);
    }
    node->fileSize = fileSize;
    if (fileMd5) {
        node->fileMd5 = strdup(fileMd5);
    }
    return node;
}

VideoNode* createFullVideoNode(const char* localPath, const char* file,
    int fileSize, const char* fileMd5, bool aspectRatio) {
    VideoNode* node = createWithPathVideoNode(localPath);
    if (node) {
        if (file) {
            node->file = strdup(file);
        }
        node->fileSize = fileSize;
        if (fileMd5) {
            node->fileMd5 = strdup(fileMd5);
        }
        node->aspectRatio = aspectRatio;
    }
    return node;
}

VideoNode* copyVideoNode(const VideoNode* other) {
    if (!other) {
        return NULL;
    }
    VideoNode* node = createVideoNode();
    if (!node) {
        return NULL;
    }
    node->localPath = node->localPath ? strdup(other->localPath) : NULL;
    node->file = node->file ? strdup(other->file) : NULL;
    node->fileSize = other->fileSize;
    node->fileMd5 = node->fileMd5 ? strdup(other->fileMd5) : NULL;

    if (!node) {
        return NULL;
    }

    node->base = copyContentNode(other->base);

    return node;
}

void destroyVideoNode(VideoNode* node) {
    if (!node) {
        return;
    }

    hdfree(node->localPath);
    hdfree(node->file);
    hdfree(node->fileMd5);

    destroyContentNode(node->base);

    hdfree(node);
}

FileInfo* getFilesInfoVideoNode(VideoNode* node, int* count) {
    if (!node || !node->localPath) {
        if (count) {
            *count = 0;
        }
        return NULL;
    }

    // Create a file information structure
    FileInfo* info = createFileInfo(node->localPath);
    if (!info) {
        if (count) {
            *count = 0;
        }
        return NULL;
    }

    // Set file information
    info->url = node->file ? strdup(node->file) : NULL;
    info->size = node->fileSize;
    info->md5 = node->fileMd5 ? strdup(node->fileMd5) : NULL;

    if (count) {
        *count = 1;
    }
    return info;
}

void updateFilesInfoVideoNode(VideoNode* self, FileInfo** files, int count) {
    if (!self || !files || count <= 0) {
        return;
    }
    FileInfo* locFileInfo = createFileInfo(self->localPath);
    if (!locFileInfo) {
        return;
    }
    for (int i = 0; i < count; i++) {
        if (equalsFileInfo(locFileInfo, files[i])) {
            setFileMd5VideoNode(self, files[i]->md5);
            setFileSizeVideoNode(self, files[i]->size);
            setFileVideoNode(self, files[i]->url);
            break;
        }
    }

    destroyFileInfo(locFileInfo);
}

void setFileVideoNode(VideoNode* node, const char* file) {
    if (!node) {
        return;
    }
    hdfree(node->file);
    node->file = file ? strdup(file) : NULL;
}

const char* getFileVideoNode(const VideoNode* node) {
    return node ? node->file : NULL;
}

void setFileSizeVideoNode(VideoNode* node, int fileSize) {
    if (node) {
        node->fileSize = fileSize;
    }
}

int getFileSizeVideoNode(const VideoNode* node) {
    return node ? node->fileSize : 0;
}

void setFileMd5VideoNode(VideoNode* node, const char* fileMd5) {
    if (!node) {
        return;
    }
    hdfree(node->fileMd5);
    node->fileMd5 = fileMd5 ? strdup(fileMd5) : NULL;
}

const char* getFileMd5VideoNode(const VideoNode* node) {
    return node ? node->fileMd5 : NULL;
}

void setAspectRatioVideoNode(VideoNode* node, bool aspectRatio) {
    if (node) {
        node->aspectRatio = aspectRatio;
    }
}

bool getAspectRatioVideoNode(const VideoNode* node) {
    return node ? node->aspectRatio : false;
}

cJSON* toJsonVideoNode(const VideoNode* node) {
    if (!node) {
        return NULL;
    }
    cJSON* json = cJSON_CreateObject();
    if (!json) {
        return NULL;
    }

    toJsonContentNode(node->base, json);

    //if (node->localPath) {
    //    cJSON_AddStringToObject(json, "localPath", node->localPath);
    //}
    if (node->file) {
        cJSON_AddStringToObject(json, "file", node->file);
    }
    cJSON_AddNumberToObject(json, "fileSize", node->fileSize);
    if (node->fileMd5) {
        cJSON_AddStringToObject(json, "fileMd5", node->fileMd5);
    }
    cJSON_AddBoolToObject(json, "aspectRatio", node->aspectRatio);

    return json;
}

VideoNode* fromJsonVideoNode(const cJSON* json) {
    if (!json) {
        return NULL;
    }
    const cJSON* localPath = cJSON_GetObjectItemCaseSensitive(json, "localPath");
    if (!localPath || !cJSON_IsString(localPath)) {
        return NULL;
    }

    VideoNode* node = createWithPathVideoNode(localPath->valuestring);
    if (!node) {
        return NULL;
    }

    ContentNode* base = (ContentNode*)node;
    const cJSON* uuid = cJSON_GetObjectItemCaseSensitive(json, "uuid");
    if (uuid && cJSON_IsString(uuid)) {
        base->uuid = strdup(uuid->valuestring);
    }

    const cJSON* name = cJSON_GetObjectItemCaseSensitive(json, "name");
    if (name && cJSON_IsString(name)) {
        base->name = strdup(name->valuestring);
    }

    const cJSON* bindType = cJSON_GetObjectItemCaseSensitive(json, "bindType");
    if (bindType && cJSON_IsString(bindType)) {
        base->bindType = strdup(bindType->valuestring);
    }

    const cJSON* file = cJSON_GetObjectItemCaseSensitive(json, "file");
    if (file && cJSON_IsString(file)) {
        node->file = strdup(file->valuestring);
    }

    const cJSON* fileSize = cJSON_GetObjectItemCaseSensitive(json, "fileSize");
    if (fileSize && cJSON_IsNumber(fileSize)) {
        node->fileSize = fileSize->valueint;
    }

    const cJSON* fileMd5 = cJSON_GetObjectItemCaseSensitive(json, "fileMd5");
    if (fileMd5 && cJSON_IsString(fileMd5)) {
        node->fileMd5 = strdup(fileMd5->valuestring);
    }

    const cJSON* aspectRatio = cJSON_GetObjectItemCaseSensitive(json, "aspectRatio");
    if (aspectRatio && cJSON_IsBool(aspectRatio)) {
        node->aspectRatio = cJSON_IsTrue(aspectRatio);
    }

    return node;
}

