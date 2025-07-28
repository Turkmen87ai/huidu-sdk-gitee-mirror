#ifndef BORDER_H
#define BORDER_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON.h"
#include "posixPortMemory.h"
// Border speed enumeration
typedef enum {
    BORDER_SPEED_SLOW,
    BORDER_SPEED_MIDDLE,
    BORDER_SPEED_FAST
} BorderSpeed;

// Border effect enumeration
typedef enum {
    BORDER_EFFECT_ROTATE,
    BORDER_EFFECT_BLINK,
    BORDER_EFFECT_STATIC
} BorderEffect;

// Convert velocity enumeration to string
const char* BorderSpeedToString(BorderSpeed speed);

// Convert a string to a velocity enumeration
BorderSpeed BorderSpeedFromString(const char* str);

// Convert effect enumeration to strings
const char* BorderEffectToString(BorderEffect effect);

// Convert strings to effect enumerations
BorderEffect BorderEffectFromString(const char* str);

typedef struct {
    int type;
    BorderSpeed speed;
    BorderEffect effect;
} Border;

// Create a default border
Border* createBorder();

// Create borders with type parameters
Border* createWithTypeBorder(int type);

// Create borders with type and speed parameters
Border* createWithTypeAndSpeedBorder(int type, BorderSpeed speed);

// Create a border with full parameters
Border* createFullBorder(int type, BorderSpeed speed, BorderEffect effect);

// Copy the border
Border* copyBorder(const Border* other);

// Free up border memory
void destroyBorder(Border* border);

// Get the border type
int getTypeBorder(const Border* border);

// Set the border type
void setTypeBorder(Border* border, int type);

// Get the border speed
BorderSpeed getSpeedBorder(const Border* border);

// Set the border speed
void setSpeedBorder(Border* border, BorderSpeed speed);

// Get the border effect
BorderEffect getEffectBorder(const Border* border);

// Set the border effect
void setEffectBorder(Border* border, BorderEffect effect);

cJSON* toJsonBorder(const Border* border);

Border* fromJsonBorder(const cJSON* json);
#endif