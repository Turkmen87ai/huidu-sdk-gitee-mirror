#include "DynamicNode.h"

DynamicNode* createDynamicNode() {
    DynamicNode* node = (DynamicNode*)hdmalloc(sizeof(DynamicNode));
    if (!node) {
        return NULL;
    }

    node->base = createContentNode();
    setTypeContentNode(node->base, "dynamic");

    node->string = NULL;
    node->keys = NULL;
    node->multiLine = 0; // Default single line

    // Create and initialize effects
    node->effect = createEffect();
    if (node->effect) {
        node->effect->effectType = IMMEDIATE_SHOW;
        node->effect->hold = 360000; // 360sec
    }

    return node;
}

DynamicNode* createDynamicNodeWithText(const char* text, const char* keys) {
    DynamicNode* node = createDynamicNode();
    if (!node) {
        return NULL;
    }
    if (text) {
        node->string = strdup(text);
    }
    if (keys) {
        node->keys = strdup(keys);
    }
    return node;
}

DynamicNode* copyDynamicNode(const DynamicNode* other) {
    if (!other) {
        return NULL;
    }
    DynamicNode* node = createDynamicNode();
    if (!node) {
        return NULL;
    }

    node->base = copyContentNode(other->base);

    if (other->string) {
		node->string = strdup(other->string);
	}
    if (other->keys) {
		node->keys = strdup(other->keys);
	}
    node->multiLine = other->multiLine;

    destroyEffect(node->effect);
    node->effect = copyEffect(other->effect);

    return node;
}

void destroyDynamicNode(DynamicNode* node) {
    if (!node) {
        return;
    }
    hdfree(node->string);
    hdfree(node->keys);

    if (node->effect) {
		destroyEffect(node->effect);
	}

    destroyContentNode(node->base);

    hdfree(node);
}

const char* getKeysDynamicNode(const DynamicNode* node) {
    return node ? node->keys : NULL;
}

void setKeysDynamicNode(DynamicNode* node, const char* keys) {
    if (!node) {
        return;
    }
    hdfree(node->keys);
    node->keys = keys ? strdup(keys) : NULL;
}

const char* getStringDynamicNode(const DynamicNode* node) {
    return node ? node->string : NULL;
}

void setStringDynamicNode(DynamicNode* node, const char* text) {
    if (!node) {
        return;
    }
    hdfree(node->string);
    node->string = text ? strdup(text) : NULL;
}

Effect* getEffectDynamicNode(DynamicNode* node) {
    return node ? node->effect : NULL;
}

void setEffectDynamicNode(DynamicNode* node, Effect* effect) {
    if (!node || !effect) {
        return;
    }
    if (node->effect) destroyEffect(node->effect);
    node->effect = copyEffect(effect);
}

int isMultiLineDynamicNode(const DynamicNode* node) {
    return node ? node->multiLine : 0;
}

void setMultiLineDynamicNode(DynamicNode* node, int multiLine) {
    if (node) {
        node->multiLine = multiLine;
    }
}

cJSON* toJsonDynamicNode(const DynamicNode* node) {
    if (!node) {
        return NULL;
    }
    cJSON* json = cJSON_CreateObject();

    toJsonContentNode(node->base, json);

    if (node->string) {
		cJSON_AddStringToObject(json, "string", node->string);
	}
    if (node->keys) {
		cJSON_AddStringToObject(json, "keys", node->keys);
	}
    cJSON_AddBoolToObject(json, "multiLine", node->multiLine);

    cJSON* effectJson = toJsonEffect(node->effect);
    if (effectJson) {
		cJSON_AddItemToObject(json, "effect", effectJson);
	}
    return json;
}

DynamicNode* fromJsonDynamicNode(const cJSON* json) {
    if (!json) {
        return NULL;
    }
    DynamicNode* node = createDynamicNode();
    if (!node) {
        return NULL;
    }

    if (node->base->uuid) {
        hdfree(node->base->uuid);
    }
    node->base->uuid = cJSON_GetStringValue(cJSON_GetObjectItem(json, "uuid"));

    if (node->base->name) {
        hdfree(node->base->name);
    }
    node->base->name = cJSON_GetStringValue(cJSON_GetObjectItem(json, "name"));

    if (node->base->type) {
        hdfree(node->base->type);
    }
    node->base->type = cJSON_GetStringValue(cJSON_GetObjectItem(json, "type"));

    if (node->base->bindType) {
        hdfree(node->base->bindType);
    }
    node->base->bindType = cJSON_GetStringValue(cJSON_GetObjectItem(json, "bindType"));

    // Resolve dynamic node-specific properties
    cJSON* textItem = cJSON_GetObjectItem(json, "text");
    if (textItem && cJSON_IsString(textItem)) {
        setStringDynamicNode(node, textItem->valuestring);
    }

    cJSON* keysItem = cJSON_GetObjectItem(json, "keys");
    if (keysItem && cJSON_IsString(keysItem)) {
        setKeysDynamicNode(node, keysItem->valuestring);
    }

    cJSON* multiLineItem = cJSON_GetObjectItem(json, "multiLine");
    if (multiLineItem && cJSON_IsBool(multiLineItem)) {
        node->multiLine = cJSON_IsTrue(multiLineItem);
    }

    // Parsing special effects
    cJSON* effectJson = cJSON_GetObjectItem(json, "effect");
    if (effectJson) {
        Effect* effect = fromJsonEffect(effectJson);
        if (effect) {
            setEffectDynamicNode(node, effect);
            destroyEffect(effect);
        }
    }

    return node;
}

