#ifndef IMAGENODE_H
#define IMAGENODE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Effect.h"
#include "FileInfo.h"
#include "ContentNode.h"
#include "posixPortMemory.h"
typedef enum ImageFit{
    FIT_FILL,     // padding
    FIT_CENTER,   // Center
    FIT_STRETCH,  // Stretch
    FIT_TILE      // Tile
} ImageFit;

// Enumerate the conversion string
const char* fitToString(ImageFit fit);

// String to enumerate
ImageFit stringToFit(const char* str);

typedef struct {
    ContentNode* base;  // Base class

    char* localPath;    // Local path
    char* fileUrl;      // File URL
    int fileSize;       // File size
    char* fileMd5;      // MD5 value
    Effect* effect;     // effect
    ImageFit fit;       // Adaptation mode
} ImageNode;

ImageNode* createImageNode();

ImageNode* copyImageNode(const ImageNode* other);

void destroyImageNode(ImageNode* node);

ImageNode* createWithLocalPathImageNode(const char* localPath);

ImageNode* createWithLocalPathAndFitImageNode(const char* localPath, ImageFit fit);

ImageNode* createWithUrlFileSizeMd5ImageNode(const char* fileUrl, int fileSize, const char* fileMd5);

ImageNode* createFullImageNode(const char* url, int fileSize, const char* fileMd5, ImageFit fit);

const char* getFileUrlImageNode(ImageNode* node);

void setFileUrlImageNode(ImageNode* node, const char* file);

int getFileSizeImageNode(ImageNode* node);

void setFileSizeImageNode(ImageNode* node, int fileSize);

const char* getFileMd5ImageNode(ImageNode* node);

void setFileMd5ImageNode(ImageNode* node, const char* fileMd5);

Effect* getEffectImageNode(ImageNode* node);

void setEffectImageNode(ImageNode* node, Effect* effect);

const char* getFitImageNode(ImageNode* node);

void setFitImageNode(ImageNode* node, ImageFit fit);

FileInfo* getFilesInfoImageNode(ImageNode* node, int* count);

void updateFilesInfoImageNode(ImageNode* self, FileInfo** files, int count);

cJSON* toJsonImageNode(const ImageNode* node);

ImageNode* fromJsonImageNode(const cJSON* json);

#endif
