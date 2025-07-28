#ifndef FILEINFO_H
#define FILEINFO_H
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON.h"
#include "posixPortMemory.h"
typedef struct {
    char* localFile;  // Local file path
    char* url;        // File URL
    int size;         // File size (bytes)
    char* md5;        // File MD5 value
} FileInfo;

FileInfo* createFileInfo(char* localFile);

void destroyFileInfo(FileInfo* info);

FileInfo* copyFileInfo(const FileInfo* src);

bool equalsFileInfo(const FileInfo* info1, const FileInfo* info2);

cJSON* toJsonFileInfo(const FileInfo* info);

FileInfo* FileInfo_fromJson(const cJSON* json);

#endif