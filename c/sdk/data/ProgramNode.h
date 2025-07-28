#ifndef PROGRAMNODE_H
#define PROGRAMNODE_H
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "ContentNode.h"
#include "AreaNode.h"
#include "Border.h"
#include "PlayControl.h"
#include "posixPortMemory.h"
#include <stddef.h>
typedef struct ProgramNode {
    ContentNode* base;  // Base class

    AreaNode** areas;      // Array of regional nodes
    size_t areaCount;      // Number of zones
    Border* border;        // frame
    PlayControl* playControl; // Playback controls
} ProgramNode;

ProgramNode* createProgramNode();

ProgramNode* createProgramNodeWithArea(AreaNode* area);

ProgramNode* createProgramNodeWithAreas(AreaNode** areas, size_t count);

ProgramNode* createProgramNodeWithContent(ContentNode* content);

ProgramNode* createProgramNodeWithContents(ContentNode** contents, size_t count);

void destroyProgramNode(ProgramNode* node);

size_t getAreaCountProgramNode(const ProgramNode* node);

AreaNode* getAreaProgramNode(const ProgramNode* node, size_t index);

void setAreasProgramNode(ProgramNode* node, AreaNode** areas, size_t count);

Border* getBorderProgramNode(const ProgramNode* node);

void setBorderProgramNode(ProgramNode* node, Border* border);

PlayControl* getPlayControlProgramNode(const ProgramNode* node);

void setPlayControlProgramNode(ProgramNode* node, PlayControl* playControl);

cJSON* toJsonProgramNode(const ProgramNode* node);

ProgramNode* fromJsonProgramNode(const cJSON* json);

ProgramNode* fromJsonStringProgramNode(const char* jsonText);

#endif
