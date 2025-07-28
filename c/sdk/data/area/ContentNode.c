#include "AreaNode.h"

ContentNode* createContentNode() {
    ContentNode* node = (ContentNode*)hdmalloc(sizeof(ContentNode));
    if (!node) {
        return NULL;
    }
    node->uuid = NULL;
    node->name = NULL;
    node->type = NULL;
    node->bindType = NULL;
    return node;
}

ContentNode* createWithIdAndNameContentNode(const char* id, const char* name) {
    ContentNode* node = createContentNode();
    if (!node) {
        return NULL;
    }
    node->uuid = id ? strdup(id) : NULL;
    node->name = name ? strdup(name) : NULL;
    return node;
}

ContentNode* copyContentNode(ContentNode* other) {
    if (!other) {
        return NULL;
    }
    ContentNode* node = createWithIdAndNameContentNode(other->uuid, other->name);
    if (!node) {
        return NULL;
    }
    node->type = other->type ? strdup(other->type) : NULL;
    node->bindType = other->bindType ? strdup(other->bindType) : NULL;
    return node;
}

void destroyContentNode(ContentNode* node) {
    if (!node) {
        return;
    }

    hdfree(node->uuid);
    hdfree(node->name);
    hdfree(node->type);
    hdfree(node->bindType);
    hdfree(node);
}

const char* getIdContentNode(ContentNode* node) {
    return node ? node->uuid : NULL;
}

void setIdContentNode(ContentNode* node, const char* uuid) {
    if (!node) {
        return;
    }
    hdfree(node->uuid);
    node->uuid = uuid ? strdup(uuid) : NULL;
}

const char* getNameContentNode(ContentNode* node) {
    return node ? node->name : NULL;
}

void setNameContentNode(ContentNode* node, const char* name) {
    if (!node) {
        return;
    }
    hdfree(node->name);
    node->name = name ? strdup(name) : NULL;
}

const char* getTypeContentNode(ContentNode* node) {
    return node ? node->type : NULL;
}

void setTypeContentNode(ContentNode* node, const char* type) {
    if (!node) {
        return;
    }
    hdfree(node->type);
    node->type = type ? strdup(type) : NULL;
}

const char* getBindType(ContentNode* node) {
    return node ? node->bindType : NULL;
}

void setBindType(ContentNode* node, const char* bindType) {
    if (!node) {
        return;
    }
    hdfree(node->bindType);
    node->bindType = bindType ? strdup(bindType) : NULL;
}

void toJsonContentNode(ContentNode* node, cJSON* json) {
    if (node->uuid) {
        cJSON_AddStringToObject(json, "uuid", node->uuid);
    }
    if (node->name) {
        cJSON_AddStringToObject(json, "name", node->name);
    }
    if (node->type) {
        cJSON_AddStringToObject(json, "type", node->type);
    }
    if (node->bindType) {
        cJSON_AddStringToObject(json, "bindType", node->bindType);
    }
    return;
}

ContentNode* fromJsonContentNode(const cJSON* json) {
    if (!json) {
        return NULL;
    }

    const cJSON* uuid = cJSON_GetObjectItemCaseSensitive(json, "uuid");
    const cJSON* name = cJSON_GetObjectItemCaseSensitive(json, "name");

    if (!cJSON_IsString(uuid) || !cJSON_IsString(name)) {
        return NULL;
    }

    ContentNode* node = createWithIdAndNameContentNode(uuid->valuestring, name->valuestring);
    if (!node) {
        return NULL;
    }

    const cJSON* type = cJSON_GetObjectItemCaseSensitive(json, "type");
    if (type && cJSON_IsString(type)) {
        node->type = strdup(type->valuestring);
    }

    const cJSON* bindType = cJSON_GetObjectItemCaseSensitive(json, "bindType");
    if (bindType && cJSON_IsString(bindType)) {
        node->bindType = strdup(bindType->valuestring);
    }

    return node;
}

