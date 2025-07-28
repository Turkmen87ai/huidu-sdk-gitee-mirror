#ifndef PLAYCONTROL_H
#define PLAYCONTROL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cJSON.h"
#include "posixPortMemory.h"
#include <stddef.h>
typedef enum {
    Mon, Tue, Wed, Thur, Fri, Sat, Sun
} Weekday;

const char* weekdayToString(Weekday day);

Weekday stringToWeekday(const char* str);

typedef struct {
    char* start; // "yyyy-MM-dd" format
    char* end;   // "yyyy-MM-dd" format
} Date;

Date* createDate();

void destroyDate(Date* date);

cJSON* toJsonDate(const Date* date);

Date* fromJsonDate(const cJSON* json);

typedef struct {
    char* start; // "HH:mm:ss" format
    char* end;   // "HH:mm:ss" format
} Time;

Time* createTime();

void destroyTime(Time* time);

cJSON* toJsonTime(const Time* time);

Time* fromJsonTime(const cJSON* json);

typedef struct {
    Weekday* weekdays; // Enabled week array
    int count;         // Weekly quantity
} Week;

Week* createWeek();

void destroyWeek(Week* week);

// Set the week of activation
void setWeekdaysWeek(Week* week, Weekday* weekdays, int count);

// Get the enabled week string (comma separated)
char* getEnableWeek(const Week* week);

// Set the enabled week from the string
void setEnableWeek(Week* week, const char* value);

cJSON* toJsonWeek(const Week* week);

Week* fromJsonWeek(const cJSON* json);

typedef struct {
    Date** dates;     // Date array
    int date_count;   // Number of dates

    Time** times;     // Time array
    int time_count;   // Number of hours

    Week* week;       // Weekly settings
} PlayControl;

PlayControl* createPlayControl();

PlayControl* copyPlayControl(const PlayControl* other);

void destroyPlayControl(PlayControl* pc);

// Set the date array
void setDatesPlayControl(PlayControl* pc, Date** dates, int count);

// Set the time array
void setTimesPlayControl(PlayControl* pc, Time** times, int count);

cJSON* toJsonPlayControl(const PlayControl* pc);

PlayControl* fromJsonPlayControl(const cJSON* json);
#endif
