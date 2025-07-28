#ifndef DYNAMICNODE_H
#define DYNAMICNODE_H

#include "ContentNode.h"
#include "Effect.h"
#include "cJSON.h"
#include "posixPortMemory.h"
// Dynamic node structure
typedef struct {
    ContentNode* base;     // Basic content nodes

    char* string;           // Text content
    char* keys;             // Dynamic key-value
    Effect* effect;         // special effect
    int multiLine;          // Multiple rows (0: single row, 1: multiple rows)
} DynamicNode;

// Create dynamic nodes
DynamicNode* createDynamicNode();

// Create dynamic nodes with text and values
DynamicNode* createDynamicNodeWithText(const char* text, const char* keys);

// Copy the constructor
DynamicNode* copyDynamicNode(const DynamicNode* other);

// Free up resources
void destroyDynamicNode(DynamicNode* node);

// Get/set key values
const char* getKeysDynamicNode(const DynamicNode* node);

void setKeysDynamicNode(DynamicNode* node, const char* keys);

const char* getStringDynamicNode(const DynamicNode* node);

void setStringDynamicNode(DynamicNode* node, const char* text);

Effect* getEffectDynamicNode(DynamicNode* node);

void setEffectDynamicNode(DynamicNode* node, Effect* effect);

int isMultiLineDynamicNode(const DynamicNode* node);

void setMultiLineDynamicNode(DynamicNode* node, int multiLine);

// Serialized to JSON
cJSON* toJsonDynamicNode(const DynamicNode* node);

// deserialize from JSON
DynamicNode* fromJsonDynamicNode(const cJSON* json);

#endif // DYNAMICNODE_H