#ifndef CLOCKPARAM_H
#define CLOCKPARAM_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "posixPortMemory.h"
typedef struct FormatColor {
    char* display;
    char* format;
    char* color;
    int size;
} FormatColorClockParam;

typedef struct StringColor {
    char* display;
    char* string;
    int size;
    char* color;
} StringColorClockParam;

typedef struct Style {
    char* hourHandColor;
    char* minuteHandColor;
    char* secondHandColor;
    char* hourScaleColor;
    char* minuteScaleColor;
    char* fontName;
    int fontSize;
} StyleClockParam;

typedef struct FmtStyle {
    char* swap;
    char* space;
} FmtStyleClockParam;

// create FormatColor
FormatColorClockParam* createFormatColorClockParam();

// copy FormatColor
FormatColorClockParam* copyFormatColorClockParam(const FormatColorClockParam* src);

// release FormatColor
void destroyFormatColorClockParam(FormatColorClockParam* fc);

// create StringColor
StringColorClockParam* createStringColorClockParam();

// copy StringColor
StringColorClockParam* copyStringColorClockParam(const StringColorClockParam* src);

// release StringColor
void destroyStringColorClockParam(StringColorClockParam* sc);

// Assign a single attribute to a single attribute
void setDisplayStringColorClockParam(StringColorClockParam* sc, const char* display);

// create Style
StyleClockParam* createStyleClockParam();

// copy Style
StyleClockParam* copyStyleClockParam(const StyleClockParam* src);

// release Style
void destroyStyleClockParam(StyleClockParam* style);

// create FmtStyle
FmtStyleClockParam* createFmtStyleClockParam();

// copy FmtStyle
FmtStyleClockParam* copyFmtStyleClockParam(const FmtStyleClockParam* src);

// release FmtStyle
void destroyFmtStyleClockParam(FmtStyleClockParam* fs);

// Assign a single attribute to a single attribute
void setSwapFmtStyleClockParam(FmtStyleClockParam* fs, const char* swap);

void setSpaceFmtStyleClockParam(FmtStyleClockParam* fs, const char* space);

cJSON* toJsonFormatColorClockParam(const FormatColorClockParam* fc);

cJSON* toJsonStringColorClockParam(const StringColorClockParam* sc);

cJSON* toJsonStyleClockParam(const StyleClockParam* style);

cJSON* toJsonFmtStyleClockParam(const FmtStyleClockParam* fs);

FormatColorClockParam* fromJsonFormatColorClockParam(const cJSON* json);

StringColorClockParam* fromJsonStringColorClockParam(const cJSON* json);

StyleClockParam* fromJsonStyleClockParam(const cJSON* json);

FmtStyleClockParam* fromJsonFmtStyleClockParam(const cJSON* json);

#endif