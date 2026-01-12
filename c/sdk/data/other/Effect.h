#ifndef EFFECT_H
#define EFFECT_H
#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include "posixPortMemory.h"
typedef enum {
    IMMEDIATE_SHOW      = 0,   ///< Immediate display.
    LEFT_PARALLEL_MOVE  = 1,   ///< Move left.
    RIGHT_PARALLEL_MOVE = 2,   ///< Move right.
    UP_PARALLEL_MOVE    = 3,   ///< Move up.
    DOWN_PARALLEL_MOVE  = 4,   ///< Move down.
    LEFT_COVER          = 5,   ///< Cover from left.
    RIGHT_COVER         = 6,   ///< Cover from right.
    UP_COVER            = 7,   ///< Cover from top.
    DOWN_COVER          = 8,   ///< Cover from bottom.
    LEFT_TOP_COVER      = 9,   ///< Cover from top-left.
    LEFT_BOTTOM_COVER   = 10,  ///< Cover from bottom-left.
    RIGHT_TOP_COVER     = 11,  ///< Cover from top-right.
    RIGHT_BOTTOM_COVER  = 12,  ///< Cover from bottom-right.
    HORIZONTAL_DIVIDE   = 13,  ///< Horizontal split.
    VERTICAL_DIVIDE     = 14,  ///< Vertical split.
    HORIZONTAL_CLOSE    = 15,  ///< Horizontal close.
    VERTICAL_CLOSE      = 16,  ///< Vertical close.
    FADE                = 17,  ///< Fade in/out.
    HORIZONTAL_SHUTTER  = 18,  ///< Horizontal blinds.
    VERTICAL_SHUTTER    = 19,  ///< Vertical blinds.
    NOT_CLEAR_AREA      = 20,  ///< Do not clear area.
    LEFT_SERIES_MOVE    = 21,  ///< Continuous left move.
    RIGHT_SERIES_MOVE   = 22,  ///< Continuous right move.
    UP_SERIES_MOVE      = 23,  ///< Continuous up move.
    DOWN_SERIES_MOVE    = 24,  ///< Continuous down move.    
    RANDOM              = 25,  ///< Random effect.
    HT_LEFT_SERIES_MOVE = 26,  ///< Head-to-tail continuous left move.
    HT_RIGHT_SERIES_MOVE= 27,  ///< Head-to-tail continuous right move.
    HT_UP_SERIES_MOVE   = 28,  ///< Head-to-tail continuous up move.
    HT_DOWN_SERIES_MOVE = 29,  ///< Head-to-tail continuous down move.
    FLICKEREFFECT       = 30   ///< Flicker effect.
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