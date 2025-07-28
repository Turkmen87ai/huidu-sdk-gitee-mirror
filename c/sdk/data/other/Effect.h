#ifndef EFFECT_H
#define EFFECT_H
#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include "posixPortMemory.h"
typedef enum {
    IMMEDIATE_SHOW      = 0,   ///< 直接显示.
    LEFT_PARALLEL_MOVE  = 1,   ///< 向左平移.
    RIGHT_PARALLEL_MOVE = 2,   ///< 向右平移.
    UP_PARALLEL_MOVE    = 3,   ///< 向上平移.
    DOWN_PARALLEL_MOVE  = 4,   ///< 向下平移.
    LEFT_COVER          = 5,   ///< 向左覆盖.
    RIGHT_COVER         = 6,   ///< 向右覆盖.
    UP_COVER            = 7,   ///< 向上覆盖.
    DOWN_COVER          = 8,   ///< 向下覆盖.
    LEFT_TOP_COVER      = 9,   ///< 左上覆盖.
    LEFT_BOTTOM_COVER   = 10,  ///< 左下覆盖.
    RIGHT_TOP_COVER     = 11,  ///< 右上覆盖.
    RIGHT_BOTTOM_COVER  = 12,  ///< 右下覆盖.
    HORIZONTAL_DIVIDE   = 13,  ///< 水平对开.
    VERTICAL_DIVIDE     = 14,  ///< 垂直对开.
    HORIZONTAL_CLOSE    = 15,  ///< 水平闭合.
    VERTICAL_CLOSE      = 16,  ///< 垂直闭合.
    FADE                = 17,  ///< 淡入淡出.
    HORIZONTAL_SHUTTER  = 18,  ///< 水平百叶窗.
    VERTICAL_SHUTTER    = 19,  ///< 垂直百叶窗.
    NOT_CLEAR_AREA      = 20,  ///< 不清屏.
    LEFT_SERIES_MOVE    = 21,  ///< 连续左移.
    RIGHT_SERIES_MOVE   = 22,  ///< 连续右移.
    UP_SERIES_MOVE      = 23,  ///< 连续上移.
    DOWN_SERIES_MOVE    = 24,  ///< 连续下移.    
    RANDOM              = 25,  ///< 随机特效.
    HT_LEFT_SERIES_MOVE = 26,  ///< 首尾相接连续左移.
    HT_RIGHT_SERIES_MOVE= 27,  ///< 首尾相接连续右移.
    HT_UP_SERIES_MOVE   = 28,  ///< 首尾相接连续上移.
    HT_DOWN_SERIES_MOVE = 29,  ///< 首尾相接连续下移.
    FLICKEREFFECT       = 30   ///< 闪烁.
} EffectType;

typedef struct {
    EffectType effectType;
    int speed;
    int hold;
} Effect;

// Effect to string
const char* toStringEffectType(EffectType type);

// Create a default effect
Effect* createEffect();

// Create an Effect with parameters
Effect* createWithTypeEffect(EffectType type);

Effect* createWithTypeAndSpeedEffect(EffectType type, int speed);

Effect* createFullEffect(EffectType type, int speed, int hold);

// Copy Effect
Effect* copyEffect(const Effect* other);

// Release Effect
void destroyEffect(Effect* effect);

EffectType getTypeEffect(const Effect* effect);

void setTypeEffect(Effect* effect, EffectType type);

int getTypeValueEffect(const Effect* effect);

void setTypeValueEffect(Effect* effect, int type);

int getSpeedEffect(const Effect* effect);

void setSpeedEffect(Effect* effect, int speed);

int getHoldEffect(const Effect* effect);

void setHoldEffect(Effect* effect, int hold);

cJSON* toJsonEffect(const Effect* effect);

Effect* fromJsonEffect(const cJSON* json);

#endif