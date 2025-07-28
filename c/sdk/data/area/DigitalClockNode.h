#ifndef DIGITALCLOCKNODE_H
#define DIGITALCLOCKNODE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ContentNode.h"
#include "Font.h"
#include "ClockParam.h"
#include "ClockParam.h"
#include "posixPortMemory.h"
typedef struct {
    ContentNode* base;  // Base class

    char* timezone;                // time zone
    char* timeOffset;              // Time offset
    Font* font;                    // font
    StringColorClockParam* title;  // title
    FormatColorClockParam* date;   // date format
    FormatColorClockParam* week;   // week format
    FormatColorClockParam* time;   // time format
    FormatColorClockParam* ampm;   // ampm format
    int spacing;                   // space
    bool multiLine;                // multiLine
    bool enabled12H;               // Whether to enable the 12-hour clock
    bool swapWeekAndDay;           // Whether to swap days and dates
} DigitalClockNode;

// Create a default digital clock node
DigitalClockNode* createDigitalClockNode();

// Copy the constructor
DigitalClockNode* copyDigitalClockNode(const DigitalClockNode* other);

// Free up resources
void destroyDigitalClockNode(DigitalClockNode* node);

// Getter/Setter method
const char* getTimezoneDigitalClockNode(const DigitalClockNode* node);

void setTimezoneDigitalClockNode(DigitalClockNode* node, const char* timezone);

const char* getTimeOffsetDigitalClockNode(const DigitalClockNode* node);

void setTimeOffsetDigitalClockNode(DigitalClockNode* node, const char* timeOffset);

Font* getFontDigitalClockNode(const DigitalClockNode* node);

void setFontDigitalClockNode(DigitalClockNode* node, Font* font);

StringColorClockParam* getTitleDigitalClockNode(const DigitalClockNode* node);

void setTitleDigitalClockNode(DigitalClockNode* node, StringColorClockParam* title);

FormatColorClockParam* getDateDigitalClockNode(const DigitalClockNode* node);

void setDateDigitalClockNode(DigitalClockNode* node, FormatColorClockParam* date);

FormatColorClockParam* getWeekDigitalClockNode(const DigitalClockNode* node);

void setWeekDigitalClockNode(DigitalClockNode* node, FormatColorClockParam* week);

FormatColorClockParam* getTimeDigitalClockNode(const DigitalClockNode* node);

void setTimeDigitalClockNode(DigitalClockNode* node, FormatColorClockParam* time);

FormatColorClockParam* getAmpmDigitalClockNode(const DigitalClockNode* node);

void setAmpmDigitalClockNode(DigitalClockNode* node, FormatColorClockParam* ampm);

// Get the clock format style
FmtStyleClockParam* getClockFmtStyleDigitalClockNode(DigitalClockNode* node);

int getSpacingDigitalClockNode(DigitalClockNode* node);

void setSpacingDigitalClockNode(DigitalClockNode* node, int spacing);

bool getMultiLineDigitalClockNode(const DigitalClockNode* node);

void setMultiLineDigitalClockNode(DigitalClockNode* node, bool multiLine);

bool getEnabled12HDigitalClockNode(const DigitalClockNode* node);

void setEnabled12HDigitalClockNode(DigitalClockNode* node, bool enabled12H);

int getSwapWeekAndDayDigitalClockNode(DigitalClockNode* node);

void setSwapWeekAndDayDigitalClockNode(DigitalClockNode* node, int swap);

// Serialized to JSON
cJSON* toJsonDigitalClockNode(const DigitalClockNode* node);

// deserialize from JSON
DigitalClockNode* fromJsonDigitalClockNode(const cJSON* json);

#endif