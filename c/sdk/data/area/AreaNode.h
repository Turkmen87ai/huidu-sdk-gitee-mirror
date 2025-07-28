#ifndef AREANODE_H
#define AREANODE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ContentNode.h"
#include "TextNode.h"
#include "DynamicNode.h"
#include "ImageNode.h"
#include "VideoNode.h"
#include "DialClockNode.h"
#include "DigitalClockNode.h"
#include "Border.h"
#include "posixPortMemory.h"
#include <stddef.h>
// Content node type definitions
typedef enum {
    CONTENT_TYPE_TEXT,
    CONTENT_TYPE_DYNAMIC,
    CONTENT_TYPE_IMAGE,
    CONTENT_TYPE_VIDEO,
    CONTENT_TYPE_DIGITAL_CLOCK,
    CONTENT_TYPE_DIAL_CLOCK,
    CONTENT_TYPE_UNKNOWN
} ContentNodeType;

// Content node consortium
typedef union {
    ContentNode* base;
    TextNode* text;
    DynamicNode* dynamic;
    ImageNode* image;
    VideoNode* video;
    DigitalClockNode* digitalClock;
    DialClockNode* dialClock;
} ContentNodeUnion;

typedef struct AreaNode {
    ContentNode* base;  // Base class

    int x;              // X coordinates
    int y;              // Y coordinates
    int width;          // width
    int height;         // height
    Border* border;     // frame

    ContentNodeUnion* items; // Content node array
    size_t itemCount;        // Number of content nodes
} AreaNode;

// Create an empty zone node
AreaNode* createAreaNode();

// Create an area with a single content node
AreaNode* createAreaNodeWithContent(ContentNode* content);

// Create a region with multiple content nodes
AreaNode* createAreaNodeWithContents(ContentNode** contents, size_t count);

// Copy the constructor
AreaNode* copyAreaNode(AreaNode* other);

// Free up memory
void destroyAreaNode(AreaNode* node);

// Get/set position and dimensions
int getXAreaNode(const AreaNode* node);
void setXAreaNode(AreaNode* node, int x);
int getYAreaNode(const AreaNode* node);
void setYAreaNode(AreaNode* node, int y);
int getWidthAreaNode(const AreaNode* node);
void setWidthAreaNode(AreaNode* node, int width);
int getHeightAreaNode(const AreaNode* node);
void setHeightAreaNode(AreaNode* node, int height);

// Get/set borders
Border* getBorderAreaNode(const AreaNode* node);
void setBorderAreaNode(AreaNode* node, Border* border);

// Get/set content nodes
size_t getItemCountAreaNode(const AreaNode* node);
ContentNode* getItemAreaNode(const AreaNode* node, size_t index);
void setItemsAreaNode(AreaNode* node, ContentNode** contents, size_t count);

// Serialized as a JSON string
cJSON* toJsonAreaNode(const AreaNode* node);

// Parse the object from JSON
ContentNode* createSpecificNodeFromJson(const cJSON* json);

AreaNode* fromJsonAreaNode(const cJSON* json);

#endif
