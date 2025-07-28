#include "TextNode.h"

const char* alignmentToString(TextAlignment alignment) {
    switch (alignment) {
    case LEFT: return "left";
    case RIGHT: return "right";
    default: return "center";
    }
}

TextAlignment alignmentFromString(const char* str) {
    if (str == NULL) return CENTER;

    if (strcmp(str, "left") == 0) return LEFT;
    if (strcmp(str, "right") == 0) return RIGHT;
    return CENTER;
}

TextVAlignment valignmentFromString(const char* str) {
    if (str == NULL) return MIDDLE;

    if (strcmp(str, "top") == 0) return TOP;
    if (strcmp(str, "bottom") == 0) return BOTTOM;
    return MIDDLE;
}

const char* valignmentToString(TextVAlignment valignment) {
    switch (valignment) {
    case TOP: return "top";
    case BOTTOM: return "bottom";
    default: return "middle";
    }
}

TextNode* createTextNode() {
    TextNode* node = (TextNode*)hdmalloc(sizeof(TextNode));
    if (!node) {
        return NULL;
    }
    node->base = createContentNode();
    setTypeContentNode(node->base, "text");

    node->string = NULL;
    node->multiLine = true;  // The default is multi-row
    node->alignment = CENTER;
    node->valignment = MIDDLE;
    node->effect = NULL;
    node->font = NULL;

    return node;
}

TextNode* createWithTextTextNode(const char* text) {
    TextNode* node = createTextNode();
    if (node && text) {
        node->string = strdup(text);
    }
    return node;
}

TextNode* copyTextNode(const TextNode* other) {
    if (!other) {
        return NULL;
    }
    TextNode* node = createTextNode();
    if (!node) {
        return NULL;
    }

    node->base = copyContentNode(other->base);

    if (other->string) {
        node->string = strdup(other->string);
    }

    if (other->effect) {
        node->effect = copyEffect(other->effect);
    }
    if (other->font) {
        node->font = copyFont(other->font);
    }

    node->multiLine = other->multiLine;
    node->alignment = other->alignment;
    node->valignment = other->valignment;

    return node;
}

void destroyTextNode(TextNode* node) {
    if (!node) {
        return;
    }

    hdfree(node->string);

    if (node->effect) {
        destroyEffect(node->effect);
    }
    if (node->font) {
        destroyFont(node->font);
    }

    destroyContentNode(node->base);

    hdfree(node);
}

const char* getStringTextNode(const TextNode* node) {
    return node ? node->string : NULL;
}

void setStringTextNode(TextNode* node, const char* string) {
    if (!node) {
        return;
    }
    hdfree(node->string);
    node->string = string ? strdup(string) : NULL;
}

bool getMultiLineTextNode(const TextNode* node) {
    return node ? node->multiLine : true;
}

void setMultiLineTextNode(TextNode* node, bool multiLine) {
    if (node) {
        node->multiLine = multiLine;
    }
}

TextAlignment getAlignmentTextNode(const TextNode* node) {
    return node ? node->alignment : CENTER;
}

void setAlignmentTextNode(TextNode* node, TextAlignment alignment) {
    if (node) {
        node->alignment = alignment;
    }
}

TextVAlignment getVAlignmentTextNode(const TextNode* node) {
    return node ? node->valignment : MIDDLE;
}

void setVAlignmentTextNode(TextNode* node, TextVAlignment valignment) {
    if (node) {
        node->valignment = valignment;
    }
}

Effect* getEffectTextNode(const TextNode* node) {
    return node ? node->effect : NULL;
}

void setEffectTextNode(TextNode* node, Effect* effect) {
    if (!node) {
        return;
    }
    if (node->effect) {
        destroyEffect(node->effect);
    }
    node->effect = effect;
}

Font* getFontTextNode(const TextNode* node) {
    return node ? node->font : NULL;
}

void setFontTextNode(TextNode* node, Font* font) {
    if (!node) {
        return;
    }
    if (node->font) {
        destroyFont(node->font);
    }
    node->font = font;
}

cJSON* toJsonTextNode(const TextNode* node) {
    if (!node) {
        return NULL;
    }
    cJSON* json = cJSON_CreateObject();
    if (!json) {
        return NULL;
    }

    toJsonContentNode(node->base, json);

    if (node->string) {
        cJSON_AddStringToObject(json, "string", node->string);
    }
    cJSON_AddBoolToObject(json, "multiLine", node->multiLine);

    const char* alignStr = alignmentToString(node->alignment);
    cJSON_AddStringToObject(json, "alignment", alignStr);

    const char* valignStr = valignmentToString(node->valignment);
    cJSON_AddStringToObject(json, "valignment", valignStr);

    if (node->effect) {
        cJSON* effectJson = toJsonEffect(node->effect);
        if (effectJson) {
            cJSON_AddItemToObject(json, "effect", effectJson);
        }
    }

    if (node->font) {
        cJSON* fontJson = toJsonFont(node->font);
        if (fontJson) {
            cJSON_AddItemToObject(json, "font", fontJson);
        }
    }

    return json;
}

TextNode* fromJsonTextNode(const cJSON* json) {
    if (!json) {
        return NULL;
    }

    TextNode* node = createTextNode();
    if (!node) {
        return NULL;
    }

    const cJSON* baseJson = cJSON_GetObjectItem(json, "base");
    if (baseJson) {
        node->base = fromJsonContentNode(baseJson);
    }

    const cJSON* string = cJSON_GetObjectItem(json, "string");
    if (string && cJSON_IsString(string)) {
        setStringTextNode(node, string->valuestring);
    }

    const cJSON* multiLine = cJSON_GetObjectItem(json, "multiLine");
    if (multiLine && cJSON_IsBool(multiLine)) {
        setMultiLineTextNode(node, cJSON_IsTrue(multiLine));
    }

    const cJSON* alignment = cJSON_GetObjectItem(json, "alignment");
    if (alignment && cJSON_IsString(alignment)) {
        node->alignment = alignmentFromString(alignment->valuestring);
    }

    const cJSON* valignment = cJSON_GetObjectItem(json, "valignment");
    if (valignment && cJSON_IsString(valignment)) {
        node->valignment = valignmentFromString(valignment->valuestring);
    }

    const cJSON* effectJson = cJSON_GetObjectItem(json, "effect");
    if (effectJson) {
        Effect* effect = fromJsonEffect(effectJson);
        if (effect) {
            setEffectTextNode(node, effect);
        }
    }

    const cJSON* fontJson = cJSON_GetObjectItem(json, "font");
    if (fontJson) {
        Font* font = fromJsonFont(fontJson);
        if (font) {
            setFontTextNode(node, font);
        }
    }

    return node;
}

