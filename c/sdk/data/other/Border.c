#include "Border.h"

const char* BorderSpeedToString(BorderSpeed speed) {
    switch (speed) {
    case BORDER_SPEED_SLOW:   return "slow";
    case BORDER_SPEED_MIDDLE: return "middle";
    case BORDER_SPEED_FAST:   return "fast";
    default: return "unknown";
    }
}

BorderSpeed BorderSpeedFromString(const char* str) {
    if (strcmp(str, "slow") == 0)    return BORDER_SPEED_SLOW;
    if (strcmp(str, "middle") == 0)  return BORDER_SPEED_MIDDLE;
    if (strcmp(str, "fast") == 0)    return BORDER_SPEED_FAST;
    return BORDER_SPEED_MIDDLE; // Default
}

const char* BorderEffectToString(BorderEffect effect) {
    switch (effect) {
    case BORDER_EFFECT_ROTATE: return "rotate";
    case BORDER_EFFECT_BLINK:  return "blink";
    case BORDER_EFFECT_STATIC: return "null";
    default: return "unknown";
    }
}

BorderEffect BorderEffectFromString(const char* str) {
    if (strcmp(str, "rotate") == 0) return BORDER_EFFECT_ROTATE;
    if (strcmp(str, "blink") == 0)  return BORDER_EFFECT_BLINK;
    if (strcmp(str, "null") == 0)   return BORDER_EFFECT_STATIC;
    return BORDER_EFFECT_STATIC; // Default
}

Border* createBorder() {
    Border* border = (Border*)hdmalloc(sizeof(Border));
    border->type = 0;
    border->speed = BORDER_SPEED_MIDDLE;
    border->effect = BORDER_EFFECT_STATIC;
    return border;
}

Border* createWithTypeBorder(int type) {
    Border* border = createBorder();
    border->type = type;
    return border;
}

Border* createWithTypeAndSpeedBorder(int type, BorderSpeed speed) {
    Border* border = createWithTypeBorder(type);
    border->speed = speed;
    return border;
}

Border* createFullBorder(int type, BorderSpeed speed, BorderEffect effect) {
    Border* border = createWithTypeAndSpeedBorder(type, speed);
    border->effect = effect;
    return border;
}

Border* copyBorder(const Border* other) {
    if (!other) {
        return NULL;
    }
    return createFullBorder(other->type, other->speed, other->effect);
}

void destroyBorder(Border* border) {
    hdfree(border);
}

int getTypeBorder(const Border* border) {
    return border ? border->type : 0;
}

void setTypeBorder(Border* border, int type) {
    if (border) {
        border->type = type;
    }
}

BorderSpeed getSpeedBorder(const Border* border) {
    return border ? border->speed : BORDER_SPEED_MIDDLE;
}

void setSpeedBorder(Border* border, BorderSpeed speed) {
    if (border) {
        border->speed = speed;
    }
}

BorderEffect getEffectBorder(const Border* border) {
    return border ? border->effect : BORDER_EFFECT_STATIC;
}

void setEffectBorder(Border* border, BorderEffect effect) {
    if (border) {
        border->effect = effect;
    }
}

cJSON* toJsonBorder(const Border* border) {
    if (!border) {
        return NULL;
    }
    cJSON* json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", border->type);
    cJSON_AddStringToObject(json, "speed", BorderSpeedToString(border->speed));
    cJSON_AddStringToObject(json, "effect", BorderEffectToString(border->effect));
    return json;
}

Border* fromJsonBorder(const cJSON* json) {
    if (!json) {
        return NULL;
    }
    cJSON* typeJson = cJSON_GetObjectItemCaseSensitive(json, "type");
    cJSON* speedJson = cJSON_GetObjectItemCaseSensitive(json, "speed");
    cJSON* effectJson = cJSON_GetObjectItemCaseSensitive(json, "effect");

    Border* border = createBorder();
    if (typeJson) {
        border->type = typeJson->valueint;
    }
    if (speedJson && speedJson->valuestring) {
        border->speed = BorderSpeedFromString(speedJson->valuestring);
    }
    if (effectJson && effectJson->valuestring) {
        border->effect = BorderEffectFromString(effectJson->valuestring);
    }
    return border;
}

