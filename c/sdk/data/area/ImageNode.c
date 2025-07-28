#include "ImageNode.h"

const char* fitToString(ImageFit fit) {
    switch (fit) {
    case FIT_FILL:    return "fill";
    case FIT_CENTER:  return "center";
    case FIT_STRETCH: return "stretch";
    case FIT_TILE:    return "tile";
    default:          return "stretch";
    }
}

ImageFit stringToFit(const char* str) {
    if (!str) {
        return FIT_STRETCH;
    }
    if (strcmp(str, "fill") == 0) return FIT_FILL;
    if (strcmp(str, "center") == 0) return FIT_CENTER;
    if (strcmp(str, "stretch") == 0) return FIT_STRETCH;
    if (strcmp(str, "tile") == 0) return FIT_TILE;
    return FIT_STRETCH;
}

ImageNode* createImageNode() {
    ImageNode* node = (ImageNode*)hdmalloc(sizeof(ImageNode));
    if (!node) {
        return NULL;
    }
    node->base = createContentNode();
    setTypeContentNode(node->base, "image");

    node->localPath = NULL;
    node->fileUrl = NULL;
    node->fileSize = 0;
    node->fileMd5 = NULL;
    node->effect = NULL;
    node->fit = FIT_STRETCH;  // Stretch by default
    return node;
}

ImageNode* copyImageNode(const ImageNode* other) {
    if (!other) {
        return NULL;
    }
    ImageNode* node = createImageNode();
    if (!node) {
        return NULL;
    }

    node->base = copyContentNode(other->base);

    node->localPath = node->localPath ? strdup(other->localPath) : NULL;
    node->fileUrl = node->fileUrl ? strdup(other->fileUrl) : NULL;
    node->fileSize = other->fileSize;
    node->fileMd5 = node->fileMd5 ? strdup(other->fileMd5) : NULL;

    if (other->effect) {
        if (node->effect) {
            destroyEffect(other->effect);
        }
        node->effect = copyEffect(other->effect);
    }

    node->fit = other->fit;

    return node;
}

void destroyImageNode(ImageNode* node) {
    if (!node) {
        return;
    }

    hdfree(node->localPath);
    hdfree(node->fileUrl);
    hdfree(node->fileMd5);

    if (node->effect) {
        destroyEffect(node->effect);
    }

    destroyContentNode(node->base);

    hdfree(node);
}

ImageNode* createWithLocalPathImageNode(const char* localPath) {
    ImageNode* node = createImageNode();
    if (node && localPath) {
        node->localPath = strdup(localPath);
    }
    return node;
}

ImageNode* createWithLocalPathAndFitImageNode(const char* localPath, ImageFit fit) {
    ImageNode* node = createWithLocalPathImageNode(localPath);
    node->fit = fit;
    return node;
}

ImageNode* createWithUrlFileSizeMd5ImageNode(const char* fileUrl, int fileSize, const char* fileMd5) {
    ImageNode* node = createImageNode();
    if (fileUrl) {
        node->fileUrl = strdup(fileUrl);
    }
    node->fileSize = fileSize;
    if (fileMd5) {
        node->fileMd5 = strdup(fileMd5);
    }
    return node;
}

ImageNode* createFullImageNode(const char* url, int fileSize, const char* fileMd5, ImageFit fit) {
    ImageNode* node = createWithUrlFileSizeMd5ImageNode(url, fileSize, fileMd5);
    node->fit = fit;
    return node;
}

const char* getFileUrlImageNode(ImageNode* node) {
    return node ? node->fileUrl : NULL;
}

void setFileUrlImageNode(ImageNode* node, const char* file) {
    if (!node) {
        return;
    }
    hdfree(node->fileUrl);
    node->fileUrl = strdup(file);
}

int getFileSizeImageNode(ImageNode* node) {
    return node ? node->fileSize : 0;
}

void setFileSizeImageNode(ImageNode* node, int fileSize) {
    if (node) {
		node->fileSize = fileSize;
	}
}

const char* getFileMd5ImageNode(ImageNode* node) {
    return node ? node->fileMd5 : NULL;
}

void setFileMd5ImageNode(ImageNode* node, const char* fileMd5) {
    if (!node) {
        return;
    }
    hdfree(node->fileMd5);
    node->fileMd5 = fileMd5 ? strdup(fileMd5) : NULL;
}

Effect* getEffectImageNode(ImageNode* node) {
    return node ? node->effect : NULL;
}

void setEffectImageNode(ImageNode* node, Effect* effect) {
    if (!node) {
        return;
    }
    if (node->effect) {
        destroyEffect(node->effect);
    }
    node->effect = effect;
}

const char* getFitImageNode(ImageNode* node) {
    if (!node) return "stretch";

    switch (node->fit) {
    case FIT_FILL:    return "fill";
    case FIT_CENTER:  return "center";
    case FIT_STRETCH: return "stretch";
    case FIT_TILE:    return "tile";
    default:          return "stretch";
    }
}

void setFitImageNode(ImageNode* node, ImageFit fit) {
    if (node) {
        node->fit = fit;
    }
}

FileInfo* getFilesInfoImageNode(ImageNode* node, int* count) {
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
    info->url = node->fileUrl ? strdup(node->fileUrl) : NULL;
    info->size = node->fileSize;
    info->md5 = node->fileMd5 ? strdup(node->fileMd5) : NULL;

    if (count) {
        *count = 1;
    }
    return info;
}

void updateFilesInfoImageNode(ImageNode* self, FileInfo** files, int count) {
    if (!self || !files || count <= 0) {
        return;
    }
    FileInfo* locFileInfo = createFileInfo(self->localPath);
    if (!locFileInfo) {
        return;
    }
    // Find matching file information
    for (int i = 0; i < count; i++) {
        if (equalsFileInfo(locFileInfo, files[i])) {
            setFileMd5ImageNode(self, files[i]->md5);
            setFileSizeImageNode(self, files[i]->size);
            setFileUrlImageNode(self, files[i]->url);
            break;
        }
    }
}

cJSON* toJsonImageNode(const ImageNode* node) {
    if (!node) {
        return NULL;
    }
    cJSON* json = cJSON_CreateObject();
    if (!json) {
        return NULL;
    }

    toJsonContentNode(node->base, json);

    if (node->localPath) {
        cJSON_AddStringToObject(json, "localPath", node->localPath);
    }
    if (node->fileUrl) {
        cJSON_AddStringToObject(json, "file", node->fileUrl);
    }
    cJSON_AddNumberToObject(json, "fileSize", node->fileSize);

    if (node->fileMd5) {
        cJSON_AddStringToObject(json, "fileMd5", node->fileMd5);
    }
    cJSON_AddStringToObject(json, "fit", fitToString(node->fit));
    return json;
}

ImageNode* fromJsonImageNode(const cJSON* json) {
    if (!json) {
        return NULL;
    }
    // Validation type field
    cJSON* typeItem = cJSON_GetObjectItem(json, "type");
    if (!typeItem || !cJSON_IsString(typeItem) ||
        strcmp(typeItem->valuestring, "image") != 0) {
        return NULL;
    }

    ImageNode* node = createImageNode();
    if (!node) {
        return NULL;
    }
    // Parse the fields
    cJSON* localPath = cJSON_GetObjectItem(json, "localPath");
    if (localPath && cJSON_IsString(localPath)) {
        hdfree(node->localPath);
        node->localPath = strdup(localPath->valuestring);
    }

    cJSON* file = cJSON_GetObjectItem(json, "file");
    if (file && cJSON_IsString(file)) {
        hdfree(node->fileUrl);
        node->fileUrl = strdup(file->valuestring);
    }

    cJSON* fileSize = cJSON_GetObjectItem(json, "fileSize");
    if (fileSize && cJSON_IsNumber(fileSize)) {
        node->fileSize = fileSize->valueint;
    }

    cJSON* fileMd5 = cJSON_GetObjectItem(json, "fileMd5");
    if (fileMd5 && cJSON_IsString(fileMd5)) {
        hdfree(node->fileMd5);
        node->fileMd5 = strdup(fileMd5->valuestring);
    }

    cJSON* fit = cJSON_GetObjectItem(json, "fit");
    if (fit && cJSON_IsString(fit)) {
        node->fit = stringToFit(fit->valuestring);
    }

    return node;
}

