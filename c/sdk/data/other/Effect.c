#include "Effect.h"

const char* toStringEffectType(EffectType type) {
    switch (type) {
        case IMMEDIATE_SHOW:       return "IMMEDIATE_SHOW";
        case LEFT_PARALLEL_MOVE:    return "LEFT_PARALLEL_MOVE";
        case RIGHT_PARALLEL_MOVE:   return "RIGHT_PARALLEL_MOVE";
        case UP_PARALLEL_MOVE:      return "UP_PARALLEL_MOVE";
        case DOWN_PARALLEL_MOVE:    return "DOWN_PARALLEL_MOVE";
        case LEFT_COVER:            return "LEFT_COVER";
        case RIGHT_COVER:           return "RIGHT_COVER";
        case UP_COVER:              return "UP_COVER";
        case DOWN_COVER:            return "DOWN_COVER";
        case LEFT_TOP_COVER:        return "LEFT_TOP_COVER";
        case LEFT_BOTTOM_COVER:     return "LEFT_BOTTOM_COVER";
        case RIGHT_TOP_COVER:       return "RIGHT_TOP_COVER";
        case RIGHT_BOTTOM_COVER:    return "RIGHT_BOTTOM_COVER";
        case HORIZONTAL_DIVIDE:     return "HORIZONTAL_DIVIDE";
        case VERTICAL_DIVIDE:       return "VERTICAL_DIVIDE";
        case HORIZONTAL_CLOSE:      return "HORIZONTAL_CLOSE";
        case VERTICAL_CLOSE:        return "VERTICAL_CLOSE";
        case FADE:                  return "FADE";
        case HORIZONTAL_SHUTTER:    return "HORIZONTAL_SHUTTER";
        case VERTICAL_SHUTTER:      return "VERTICAL_SHUTTER";
        case NOT_CLEAR_AREA:        return "NOT_CLEAR_AREA";
        case LEFT_SERIES_MOVE:      return "LEFT_SERIES_MOVE";
        case RIGHT_SERIES_MOVE:     return "RIGHT_SERIES_MOVE";
        case UP_SERIES_MOVE:        return "UP_SERIES_MOVE";
        case DOWN_SERIES_MOVE:      return "DOWN_SERIES_MOVE";
        case RANDOM:                return "RANDOM";
        case HT_LEFT_SERIES_MOVE:   return "HT_LEFT_SERIES_MOVE";
        case HT_RIGHT_SERIES_MOVE:  return "HT_RIGHT_SERIES_MOVE";
        case HT_UP_SERIES_MOVE:     return "HT_UP_SERIES_MOVE";
        case HT_DOWN_SERIES_MOVE:   return "HT_DOWN_SERIES_MOVE";
        case FLICKEREFFECT:         return "FLICKEREFFECT";
        default: return "UNKNOWN";
    }
}

Effect* createEffect() {
    Effect* effect = (Effect*)hdmalloc(sizeof(Effect));
    effect->effectType = IMMEDIATE_SHOW;
    effect->speed = 5;
    effect->hold = 5000;
    return effect;
}

Effect* createWithTypeEffect(EffectType type) {
    Effect* effect = createEffect();
    effect->effectType = type;
    return effect;
}

Effect* createWithTypeAndSpeedEffect(EffectType type, int speed) {
    Effect* effect = createWithTypeEffect(type);
    effect->speed = speed;
    return effect;
}

Effect* createFullEffect(EffectType type, int speed, int hold) {
    Effect* effect = createWithTypeAndSpeedEffect(type, speed);
    effect->hold = hold;
    return effect;
}

Effect* copyEffect(const Effect* other) {
    return createFullEffect(other->effectType, other->speed, other->hold);
}

void destroyEffect(Effect* effect) {
    hdfree(effect);
}

EffectType getTypeEffect(const Effect* effect) {
    return effect ? effect->effectType : IMMEDIATE_SHOW;
}

void setTypeEffect(Effect* effect, EffectType type) {
    if (effect) {
        effect->effectType = type;
    }
}

int getTypeValueEffect(const Effect* effect) {
    return effect ? (int)effect->effectType : 0;
}

void setTypeValueEffect(Effect* effect, int type) {
    if (effect) {
        effect->effectType = (EffectType)type;
    }
}

int getSpeedEffect(const Effect* effect) {
    return effect ? effect->speed : 5;
}

void setSpeedEffect(Effect* effect, int speed) {
    if (effect) {
        effect->speed = speed;
    }
}

int getHoldEffect(const Effect* effect) {
    return effect ? effect->hold : 5000;
}

void setHoldEffect(Effect* effect, int hold) {
    if (effect) {
        effect->hold = hold;
    }
}

cJSON* toJsonEffect(const Effect* effect) {
    if (!effect) {
        return NULL;
    }
    cJSON* json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", (int)effect->effectType);
    cJSON_AddNumberToObject(json, "speed", effect->speed);
    cJSON_AddNumberToObject(json, "hold", effect->hold);
    return json;
}

Effect* fromJsonEffect(const cJSON* json) {
    if (!json) {
        return NULL;
    }
    cJSON* typeJson = cJSON_GetObjectItemCaseSensitive(json, "type");
    cJSON* speedJson = cJSON_GetObjectItemCaseSensitive(json, "speed");
    cJSON* holdJson = cJSON_GetObjectItemCaseSensitive(json, "hold");

    Effect* effect = createEffect();
    if (typeJson) {
        effect->effectType = (EffectType)typeJson->valueint;
    }
    if (speedJson) {
        effect->speed = speedJson->valueint;
    }
    if (holdJson) {
        effect->hold = holdJson->valueint;
    }

    return effect;
}

