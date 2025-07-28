#ifndef DIALCLOCKNODE_H
#define DIALCLOCKNODE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Font.h"
#include "ClockParam.h"
#include "ContentNode.h"
#include "posixPortMemory.h"
typedef struct {
    ContentNode* base;  // Base class

    char* timezone;                // time zone
    char* timeOffset;              // Time offset
    Font* font;                    // font
    StringColorClockParam* title;  // title
    FormatColorClockParam* date;   // Date format
    FormatColorClockParam* week;   // week format
    FormatColorClockParam* time;   // time format
    FormatColorClockParam* ampm;   // ampm format
    StyleClockParam* style;        // style
    int spacing;                   // space
    bool enabled12H;               // Whether to enable the 12-hour clock
    bool swapWeekAndDay;           // Whether to swap days and dates
} DialClockNode;

// Create a default watch face clock node
DialClockNode* createDialClockNode();

// Copy the constructor
DialClockNode* copyDialClockNode(const DialClockNode* other);

// Free up resources
void destroyDialClockNode(DialClockNode* node);

// Getter/Setter method
const char* getTimezoneDialClockNode(const DialClockNode* node);

void setTimezoneDialClockNode(DialClockNode* node, const char* timezone);

const char* getTimeOffsetDialClockNode(const DialClockNode* node);

void setTimeOffsetDialClockNode(DialClockNode* node, const char* timeOffset);

Font* getFontDialClockNode(const DialClockNode* node);

void setFontDialClockNode(DialClockNode* node, Font* font);

StringColorClockParam* getTitleDialClockNode(const DialClockNode* node);

void setTitleDialClockNode(DialClockNode* node, StringColorClockParam* title);

FormatColorClockParam* getDateDialClockNode(const DialClockNode* node);

void setDateDialClockNode(DialClockNode* node, FormatColorClockParam* date);

FormatColorClockParam* getWeekDialClockNode(DialClockNode* node);

void setWeekDialClockNode(DialClockNode* node, FormatColorClockParam* week);

FormatColorClockParam* getTimeDialClockNode(DialClockNode* node);

void setTimeDialClockNode(DialClockNode* node, FormatColorClockParam* time);

StyleClockParam* getStyleDialClockNode(DialClockNode* node);

void setStyleDialClockNode(DialClockNode* node, StyleClockParam* style);

FormatColorClockParam* getAmpmDialClockNode(DialClockNode* node);

void setAmpmDialClockNode(DialClockNode* node, FormatColorClockParam* ampm);

// Get the clock format style
FmtStyleClockParam* getClockFmtStyleDialClockNode(DialClockNode* node);

int getSpacingDialClockNode(DialClockNode* node);

void setSpacingDialClockNode(DialClockNode* node, int spacing);

int getEnabled12HDialClockNode(DialClockNode* node);

void setEnabled12HDialClockNode(DialClockNode* node, int enabled);

int getSwapWeekAndDayDialClockNode(DialClockNode* node);

void setSwapWeekAndDayDialClockNode(DialClockNode* node, int swap);

// Serialized to JSON
cJSON* toJsonDialClockNode(const DialClockNode* node);

// deserialize from JSON
DialClockNode* fromJsonDialClockNode(const cJSON* json);

#endif