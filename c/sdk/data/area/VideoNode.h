#ifndef VIDEONODE_H
#define VIDEONODE_H

#include "ContentNode.h"
#include "FileInfo.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "posixPortMemory.h"
typedef struct VideoNode {
    ContentNode* base;
    char* localPath;           // Local path
    char* file;                // File URL
    int fileSize;              // File size
    char* fileMd5;             // File MD5
    bool aspectRatio;          // Aspect ratio logo
} VideoNode;

// Create an empty VideoNode
VideoNode* createVideoNode();

// Create a VideoNode via a local path
VideoNode* createWithPathVideoNode(const char* localPath);

VideoNode* createWithUrlFileSizeMd5VideoNode(const char* fileUrl, int fileSize, const char* fileMd5);

// Create a VideoNode with full parameters
VideoNode* createFullVideoNode(const char* localPath, const char* file,
    int fileSize, const char* fileMd5, bool aspectRatio);

// Copy the constructor
VideoNode* copyVideoNode(const VideoNode* other);

// Free up resources
void destroyVideoNode(VideoNode* node);

// Get file information (rewrite base class method)
FileInfo* getFilesInfoVideoNode(VideoNode* self, int* count);

// Update file information (rewrite base class methods)
void updateFilesInfoVideoNode(VideoNode* self, FileInfo** files, int count);

// Set the file URL
void setFileVideoNode(VideoNode* node, const char* file);

// Get the file URL
const char* getFileVideoNode(const VideoNode* node);

// Set the file size
void setFileSizeVideoNode(VideoNode* node, int fileSize);

// Get the file size
int getSizeVideoNodeFile(const VideoNode* node);

// Set file MD5
void setFileMd5VideoNode(VideoNode* node, const char* fileMd5);

// Get file MD5
const char* getFileMd5VideoNode(const VideoNode* node);

// Set the aspect ratio logo
void setAspectRatioVideoNode(VideoNode* node, bool aspectRatio);

// Get the aspect ratio logo
bool getAspectRatioVideoNode(const VideoNode* node);

// Serialized to JSON
cJSON* toJsonVideoNode(const VideoNode* node);

// deserialize from JSON
VideoNode* fromJsonVideoNode(const cJSON* json);

#endif // VIDEONODE_H