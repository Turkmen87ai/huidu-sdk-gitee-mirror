#include "AreaNode.h"

AreaNode* createAreaNode() {
    AreaNode* node = (AreaNode*)hdmalloc(sizeof(AreaNode));
    if (!node) {
		return NULL;
	}
    node->base = createContentNode();

    node->x = 0;
    node->y = 0;
    node->width = 0;
    node->height = 0;
    node->border = NULL;
    node->items = NULL;
    node->itemCount = 0;

    return node;
}

AreaNode* createAreaNodeWithContent(ContentNode* content) {
    AreaNode* node = createAreaNode();
    if (node && content) {
        node->items = (ContentNodeUnion*)hdmalloc(sizeof(ContentNodeUnion));
        if (node->items) {
            node->items[0].base = content;
            node->itemCount = 1;
        }
    }
    return node;
}

AreaNode* createAreaNodeWithContents(ContentNode** contents, size_t count) {
    AreaNode* node = createAreaNode();
    if (node && contents && count > 0) {
        node->items = (ContentNodeUnion*)hdmalloc(sizeof(ContentNodeUnion) * count);
        if (node->items) {
            for (size_t i = 0; i < count; i++) {
                node->items[i].base = contents[i];
            }
            node->itemCount = count;
        }
    }
    return node;
}

AreaNode* copyAreaNode(AreaNode* other) {
    AreaNode* areaNode = createAreaNode();
    areaNode->x = other->x;
    areaNode->y = other->y;
    areaNode->width = other->width;
    areaNode->height = other->height;
    areaNode->border = other->border;
    return areaNode;
}

void destroyAreaNode(AreaNode* node) {
    if (!node) {
        return;
    }
    // Release content nodes
    if (node->items) {
        for (size_t i = 0; i < node->itemCount; i++) {
            if (node->items[i].text) {
                // Call the corresponding destroy function according to the type
                const char* type = getTypeContentNode(node->items[i].text->base);
                if (type) {
                    if (strcmp(type, "text") == 0) {
                        destroyTextNode(node->items[i].text);
                    }
                    else if (strcmp(type, "dynamic") == 0) {
                        destroyDynamicNode(node->items[i].dynamic);
                    }
                    else if (strcmp(type, "image") == 0) {
                        destroyImageNode(node->items[i].image);
                    }
                    else if (strcmp(type, "video") == 0) {
                        destroyVideoNode(node->items[i].video);
                    }
                    else if (strcmp(type, "digitalClock") == 0) {
                        destroyDigitalClockNode(node->items[i].digitalClock);
                    }
                    else if (strcmp(type, "dialClock") == 0) {
                        destroyDialClockNode(node->items[i].dialClock);
                    }
                    else {
                        destroyContentNode(node->items[i].base);
                    }
                }
                else {
                    destroyContentNode(node->items[i].base);
                }
            }
        }
        hdfree(node->items);
    }

    // Release the border
    if (node->border) destroyBorder(node->border);

    // Release base class
    destroyContentNode(node->base);

    hdfree(node);
}

int getXAreaNode(const AreaNode* node) {
    return node ? node->x : 0;
}

void setXAreaNode(AreaNode* node, int x) {
    if (node) {
        node->x = x;
    }
}

int getYAreaNode(const AreaNode* node) {
    return node ? node->y : 0;
}

void setYAreaNode(AreaNode* node, int y) {
    if (node) {
        node->y = y;
    }
}

int getWidthAreaNode(const AreaNode* node) {
    return node ? node->width : 0;
}

void setWidthAreaNode(AreaNode* node, int width) {
    if (node) {
        node->width = width;
    }
}

int getHeightAreaNode(const AreaNode* node) {
    return node ? node->height : 0;
}

void setHeightAreaNode(AreaNode* node, int height) {
    if (node) {
        node->height = height;
    }
}

Border* getBorderAreaNode(const AreaNode* node) {
    return node ? node->border : NULL;
}

void setBorderAreaNode(AreaNode* node, Border* border) {
    if (!node) {
        return;
    }
    if (node->border) {
        destroyBorder(node->border);
    }
    node->border = copyBorder(border);
}

size_t getItemCountAreaNode(const AreaNode* node) {
    return node ? node->itemCount : 0;
}

ContentNode* getItemAreaNode(const AreaNode* node, size_t index) {
    if (!node || index >= node->itemCount) {
        return NULL;
    }
    return node->items[index].base;
}

void setItemsAreaNode(AreaNode* node, ContentNode** contents, size_t count) {
    if (!node || !contents) {
        return;
    }

    // Unleash old content
    if (node->items) {
        for (size_t i = 0; i < node->itemCount; i++) {
            if (node->items[i].base) {
                destroyContentNode(node->items[i].base);
            }
        }
        hdfree(node->items);
    }

    // Set up new content
    node->items = (ContentNodeUnion*)hdmalloc(sizeof(ContentNodeUnion) * count);
    if (node->items) {
        for (size_t i = 0; i < count; i++) {
            node->items[i].base = copyContentNode(contents[i]);
        }
        node->itemCount = count;
    }
    else {
        node->items = NULL;
        node->itemCount = 0;
    }
}

cJSON* toJsonAreaNode(const AreaNode* node) {
    if (!node) {
        return NULL;
    }

    cJSON* json = cJSON_CreateObject();
    if (!json) return NULL;

    // Serialization base classes
    toJsonContentNode(node->base, json);


    // Serialize position and size
    cJSON_AddNumberToObject(json, "x", node->x);
    cJSON_AddNumberToObject(json, "y", node->y);
    cJSON_AddNumberToObject(json, "width", node->width);
    cJSON_AddNumberToObject(json, "height", node->height);

    // Serialize borders
    if (node->border) {
        cJSON* borderJson = toJsonBorder(node->border);
        if (borderJson) {
            cJSON_AddItemToObject(json, "border", borderJson);
        }
    }

    // Serialize content items
    cJSON* itemsArray = cJSON_CreateArray();
    if (itemsArray) {
        for (size_t i = 0; i < node->itemCount; i++) {
            if (node->items[i].text) {
                // Call the corresponding serialization function according to the type
                const char* type = getTypeContentNode(node->items[i].text->base);
                cJSON* itemJson = NULL;

                if (type) {
                    if (strcmp(type, "text") == 0) {
                        itemJson = toJsonTextNode(node->items[i].text);
                    }
                    else if (strcmp(type, "dynamic") == 0) {
                        itemJson = toJsonDynamicNode(node->items[i].dynamic);
                    }
                    else if (strcmp(type, "image") == 0) {
                        itemJson = toJsonImageNode(node->items[i].image);
                    }
                    else if (strcmp(type, "video") == 0) {
                        itemJson = toJsonVideoNode(node->items[i].video);
                    }
                    else if (strcmp(type, "digitalClock") == 0) {
                        itemJson = toJsonDigitalClockNode(node->items[i].digitalClock);
                    }
                    else if (strcmp(type, "dialClock") == 0) {
                        itemJson = toJsonDialClockNode(node->items[i].dialClock);
                    }
                }

                // If there is no specific type of serialization function, use the generic approach
                if (!itemJson) {
                    toJsonContentNode(node->items[i].base, itemJson);
                }

                if (itemJson) {
                    cJSON_AddItemToArray(itemsArray, itemJson);
                }
            }
        }
        cJSON_AddItemToObject(json, "item", itemsArray);
    }

    return json;
}

ContentNode* createSpecificNodeFromJson(const cJSON* json) {
    if (!json) {
        return NULL;
    }

    // Get the node type
    const cJSON* typeJson = cJSON_GetObjectItem(json, "type");
    if (!typeJson || !cJSON_IsString(typeJson)) {
        return NULL;
    }
    const char* type = typeJson->valuestring;
    if (!type) {
        return NULL;
    }
    // Create the corresponding node according to the type
    if (strcmp(type, "text") == 0) {
        return (ContentNode*)fromJsonTextNode(json);
    }
    else if (strcmp(type, "dynamic") == 0) {
        return (ContentNode*)fromJsonDynamicNode(json);
    }
    else if (strcmp(type, "image") == 0) {
        return (ContentNode*)fromJsonImageNode(json);
    }
    else if (strcmp(type, "video") == 0) {
        return (ContentNode*)fromJsonVideoNode(json);
    }
    else if (strcmp(type, "digitalClock") == 0) {
        return (ContentNode*)fromJsonDigitalClockNode(json);
    }
    else if (strcmp(type, "dialClock") == 0) {
        return (ContentNode*)fromJsonDialClockNode(json);
    }

    return NULL;
}

AreaNode* fromJsonAreaNode(const cJSON* json) {
    if (!json) {
        return NULL;
    }

    AreaNode* node = createAreaNode();
    if (!node) {
        return NULL;
    }
    // deserialization base class
    const cJSON* baseJson = cJSON_GetObjectItem(json, "base");
    if (baseJson) {
        node->base = fromJsonContentNode(baseJson);
    }

    // deserialize position and size
    const cJSON* x = cJSON_GetObjectItem(json, "x");
    if (x && cJSON_IsNumber(x)) {
        node->x = x->valueint;
    }

    const cJSON* y = cJSON_GetObjectItem(json, "y");
    if (y && cJSON_IsNumber(y)) {
        node->y = y->valueint;
    }

    const cJSON* width = cJSON_GetObjectItem(json, "width");
    if (width && cJSON_IsNumber(width)) {
        node->width = width->valueint;
    }

    const cJSON* height = cJSON_GetObjectItem(json, "height");
    if (height && cJSON_IsNumber(height)) {
        node->height = height->valueint;
    }

    // deserialized borders
    const cJSON* borderJson = cJSON_GetObjectItem(json, "border");
    if (borderJson) {
        Border* border = fromJsonBorder(borderJson);
        if (border) {
            setBorderAreaNode(node, border);
        }
    }

    // deserialize content items
    const cJSON* itemsArray = cJSON_GetObjectItem(json, "item");
    if (itemsArray && cJSON_IsArray(itemsArray)) {
        size_t count = cJSON_GetArraySize(itemsArray);
        if (count > 0) {
            node->items = (ContentNodeUnion*)hdmalloc(sizeof(ContentNodeUnion) * count);
            if (node->items) {
                node->itemCount = 0;

                for (size_t i = 0; i < count; i++) {
                    const cJSON* itemJson = cJSON_GetArrayItem(itemsArray, i);
                    if (itemJson) {
                        ContentNode* content = createSpecificNodeFromJson(itemJson);
                        if (content) {
                            node->items[node->itemCount].base = content;
                            node->itemCount++;
                        }
                    }
                }
            }
        }
    }

    return node;
}

