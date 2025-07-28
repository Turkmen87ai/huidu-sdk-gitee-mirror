#include "ProgramNode.h"

ProgramNode* createProgramNode() {
    ProgramNode* node = (ProgramNode*)hdmalloc(sizeof(ProgramNode));
    if (!node) {
        return NULL;
    }
	
    node->base = createContentNode();

    node->areas = NULL;
    node->areaCount = 0;
    node->border = NULL;
    node->playControl = NULL;

    return node;
}

ProgramNode* createProgramNodeWithArea(AreaNode* area) {
    ProgramNode* node = createProgramNode();
    if (node && area) {
        node->areas = (AreaNode**)hdmalloc(sizeof(AreaNode*));
        if (node->areas) {
            node->areas[0] = area;
            node->areaCount = 1;
        }
    }
    return node;
}

ProgramNode* createProgramNodeWithAreas(AreaNode** areas, size_t count) {
    ProgramNode* node = createProgramNode();
    if (node && areas && count > 0) {
        node->areas = (AreaNode**)hdmalloc(sizeof(AreaNode*) * count);
        if (node->areas) {
            for (size_t i = 0; i < count; i++) {
                node->areas[i] = areas[i];
            }
            node->areaCount = count;
        }
    }
    return node;
}

ProgramNode* createProgramNodeWithContent(ContentNode* content) {
    // The Create Region node contains content
    AreaNode* area = createAreaNodeWithContent(content);
    if (!area) {
        return NULL;
    }
    // Create a program node that contains a region
    return createProgramNodeWithArea(area);
}

ProgramNode* createProgramNodeWithContents(ContentNode** contents, size_t count) {
    // Create a zone node contains multiple contents
    AreaNode* area = createAreaNodeWithContents(contents, count);
    if (!area) {
		return NULL;
	}
    // Create a program node that contains a region
    return createProgramNodeWithArea(area);
}

void destroyProgramNode(ProgramNode* node) {
    if (!node) {
        return;
    }
    // Release the regional node
    if (node->areas) {
        for (size_t i = 0; i < node->areaCount; i++) {
            if (node->areas[i]) {
                destroyAreaNode(node->areas[i]);
            }
        }
        hdfree(node->areas);
    }

    if (node->border) {
        destroyBorder(node->border);
    }

    if (node->playControl) {
        destroyPlayControl(node->playControl);
    }

    destroyContentNode(node->base);

    hdfree(node);
}

size_t getAreaCountProgramNode(const ProgramNode* node) {
    return node ? node->areaCount : 0;
}

AreaNode* getAreaProgramNode(const ProgramNode* node, size_t index) {
    if (!node || index >= node->areaCount) {
        return NULL;
    }
    return node->areas[index];
}

void setAreasProgramNode(ProgramNode* node, AreaNode** areas, size_t count) {
    if (!node || !areas) {
        return;
    }

    if (node->areas) {
        for (size_t i = 0; i < node->areaCount; i++) {
            if (node->areas[i]) {
                destroyAreaNode(node->areas[i]);
            }
        }
        hdfree(node->areas);
    }

    node->areas = (AreaNode**)hdmalloc(sizeof(AreaNode*) * count);
    if (node->areas) {
        for (size_t i = 0; i < count; i++) {
            node->areas[i] = copyAreaNode(areas[i]);
        }
        node->areaCount = count;
    }
    else {
        node->areaCount = 0;
    }
}

Border* getBorderProgramNode(const ProgramNode* node) {
    return node ? node->border : NULL;
}

void setBorderProgramNode(ProgramNode* node, Border* border) {
    if (!node) {
        return;
    }
    if (node->border) {
        destroyBorder(node->border);
    }
    node->border = border;
}

PlayControl* getPlayControlProgramNode(const ProgramNode* node) {
    return node ? node->playControl : NULL;
}

void setPlayControlProgramNode(ProgramNode* node, PlayControl* playControl) {
    if (!node) {
        return;
    }
    if (node->playControl) {
        destroyPlayControl(node->playControl);
    }
    node->playControl = playControl;
}

cJSON* toJsonProgramNode(const ProgramNode* node) {
    if (!node) {
        return NULL;
    }

    cJSON* json = cJSON_CreateObject();
    if (!json) {
        return NULL;
    }

    // 序列化基类
    // cJSON* baseJson = cJSON_CreateObject();
    // if (!baseJson) return NULL;
    //
    // node->base = toJsonContentNode(baseJson);

    if (node->border) {
        cJSON* borderJson = toJsonBorder(node->border);
        if (borderJson) {
            cJSON_AddItemToObject(json, "border", borderJson);
        }
    }

    if (node->playControl) {
        cJSON* playControlJson = toJsonPlayControl(node->playControl);
        if (playControlJson) {
            cJSON_AddItemToObject(json, "playControl", playControlJson);
        }
    }

    cJSON* areasArray = cJSON_CreateArray();
    if (areasArray) {
        for (size_t i = 0; i < node->areaCount; i++) {
            if (node->areas[i]) {
                cJSON* areaJson = toJsonAreaNode(node->areas[i]);
                if (areaJson) {
                    cJSON_AddItemToArray(areasArray, areaJson);
                }
            }
        }
        cJSON_AddItemToObject(json, "area", areasArray);
    }

    return json;
}

ProgramNode* fromJsonProgramNode(const cJSON* json) {
    if (!json) return NULL;

    ProgramNode* node = createProgramNode();
    if (!node) return NULL;

    // 反序列化基类
    //const cJSON* baseJson = cJSON_GetObjectItem(json, "base");
    //if (baseJson) {
    //    fromJsonContentNode(&node->base, baseJson);
    //}

    const cJSON* borderJson = cJSON_GetObjectItem(json, "border");
    if (borderJson) {
        Border* border = fromJsonBorder(borderJson);
        if (border) {
            setBorderProgramNode(node, border);
        }
    }

    const cJSON* playControlJson = cJSON_GetObjectItem(json, "playControl");
    if (playControlJson) {
        PlayControl* playControl = fromJsonPlayControl(playControlJson);
        if (playControl) {
            setPlayControlProgramNode(node, playControl);
        }
    }

    const cJSON* areasArray = cJSON_GetObjectItem(json, "area");
    if (areasArray && cJSON_IsArray(areasArray)) {
        size_t count = cJSON_GetArraySize(areasArray);
        if (count > 0) {
            node->areas = (AreaNode**)hdmalloc(sizeof(AreaNode*) * count);
            if (node->areas) {
                node->areaCount = 0;

                for (size_t i = 0; i < count; i++) {
                    const cJSON* areaJson = cJSON_GetArrayItem(areasArray, i);
                    if (areaJson) {
                        AreaNode* area = fromJsonAreaNode(areaJson);
                        if (area) {
                            node->areas[node->areaCount] = area;
                            node->areaCount++;
                        }
                    }
                }
            }
        }
    }

    return node;
}

ProgramNode* fromJsonStringProgramNode(const char* jsonText) {
    if (!jsonText) {
        return NULL;
    }
    cJSON* json = cJSON_Parse(jsonText);
    if (!json) {
        return NULL;
    }
    ProgramNode* node = fromJsonProgramNode(json);
    cJSON_Delete(json);
    return node;
}

