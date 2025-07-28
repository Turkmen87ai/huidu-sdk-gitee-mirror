#ifndef CONTENTNODE_H
#define CONTENTNODE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FileInfo.h"
#include "cJSON.h"
#include "posixPortMemory.h"
typedef struct ContentNode {
    char* uuid;
    char* name;
    char* type;
    char* bindType;
} ContentNode;

// Create an empty content node
ContentNode* createContentNode();

// Create a content node with an ID and name
ContentNode* createWithIdAndNameContentNode(const char* id, const char* name);

// Deep copy content nodes
ContentNode* copyContentNode(ContentNode* other);

// Free content node resources
void destroyContentNode(ContentNode* node);

// Obtain the node ID
const char* getIdContentNode(ContentNode* node);

// Set the node ID
void setIdContentNode(ContentNode* node, const char* uuid);

// Get the node name
const char* getNameContentNode(ContentNode* node);

// Set the node name
void setNameContentNode(ContentNode* node, const char* name);

// Get the node type
const char* getTypeContentNode(ContentNode* node);

// Set the node type
void setTypeContentNode(ContentNode* node, const char* type);

// Get the binding type
const char* getBindType(ContentNode* node);

// Set the binding type
void setBindType(ContentNode* node, const char* bindType);

// Convert the content node to a JSON object
void toJsonContentNode(ContentNode* node, cJSON* json);

// Parse content nodes from JSON
ContentNode* fromJsonContentNode(const cJSON* json);

#endif