#include "PlayControl.h"

const char* weekdayToString(Weekday day) {
    switch (day) {
    case Mon:  return "Mon";
    case Tue:  return "Tue";
    case Wed:  return "Wed";
    case Thur: return "Thur";
    case Fri:  return "Fri";
    case Sat:  return "Sat";
    case Sun:  return "Sun";
    default: return "";
    }
}

Weekday stringToWeekday(const char* str) {
    if (strcmp(str, "Mon") == 0)  return Mon;
    if (strcmp(str, "Tue") == 0)  return Tue;
    if (strcmp(str, "Wed") == 0)  return Wed;
    if (strcmp(str, "Thur") == 0) return Thur;
    if (strcmp(str, "Fri") == 0)  return Fri;
    if (strcmp(str, "Sat") == 0)  return Sat;
    if (strcmp(str, "Sun") == 0)  return Sun;
    return Mon; // Default
}

Date* createDate() {
    Date* date = (Date*)hdmalloc(sizeof(Date));
    if (date) {
        date->start = NULL;
        date->end = NULL;
    }
    return date;
}

PlayControl* copyPlayControl(const PlayControl* other) {
    if (!other) {
        return NULL;
    }
    PlayControl* pc = createPlayControl();
    if (!pc) {
        return NULL;
    }

    if (other->date_count > 0) {
        Date** dates = (Date**)hdmalloc(other->date_count * sizeof(Date*));
        for (int i = 0; i < other->date_count; i++) {
            dates[i] = createDate();
            dates[i]->start = other->dates[i]->start ? strdup(other->dates[i]->start) : NULL;
            dates[i]->end = other->dates[i]->end ? strdup(other->dates[i]->end) : NULL;
        }
        setDatesPlayControl(pc, dates, other->date_count);
        hdfree(dates);
    }

    if (other->time_count > 0) {
        Time** times = (Time**)hdmalloc(other->time_count * sizeof(Time*));
        for (int i = 0; i < other->time_count; i++) {
            times[i] = createTime();
            times[i]->start = other->times[i]->start ? strdup(other->times[i]->start) : NULL;
            times[i]->end = other->times[i]->end ? strdup(other->times[i]->end) : NULL;
        }
        setTimesPlayControl(pc, times, other->time_count);
        hdfree(times);
    }

    if (other->week) {
        Week* week = createWeek();
        if (other->week->count > 0) {
            Weekday* weekdays = (Weekday*)hdmalloc(other->week->count * sizeof(Weekday));
            memcpy(weekdays, other->week->weekdays, other->week->count * sizeof(Weekday));
            setWeekdaysWeek(week, weekdays, other->week->count);
            hdfree(weekdays);
        }
        destroyWeek(pc->week);
        pc->week = week;
    }

    return pc;
}

void destroyDate(Date* date) {
    if (date) {
        hdfree(date->start);
        hdfree(date->end);
        hdfree(date);
    }
}

cJSON* toJsonDate(const Date* date) {
    if (!date) {
        return NULL;
    }
    cJSON* json = cJSON_CreateObject();
    if (date->start) cJSON_AddStringToObject(json, "start", date->start);
    if (date->end) cJSON_AddStringToObject(json, "end", date->end);
    return json;
}

Date* fromJsonDate(const cJSON* json) {
    if (!json) {
        return NULL;
    }
    Date* date = createDate();
    if (!date) {
        return NULL;
    }
    cJSON* start = cJSON_GetObjectItemCaseSensitive(json, "start");
    cJSON* end = cJSON_GetObjectItemCaseSensitive(json, "end");

    if (start && start->valuestring) {
        date->start = strdup(start->valuestring);
    }
    if (end && end->valuestring) {
        date->end = strdup(end->valuestring);
    }
    return date;
}

Time* createTime() {
    Time* time = (Time*)hdmalloc(sizeof(Time));
    if (time) {
        time->start = NULL;
        time->end = NULL;
    }
    return time;
}

void destroyTime(Time* time) {
    if (time) {
        hdfree(time->start);
        hdfree(time->end);
        hdfree(time);
    }
}

cJSON* toJsonTime(const Time* time) {
    if (!time) {
        return NULL;
    }
    cJSON* json = cJSON_CreateObject();
    if (time->start) {
        cJSON_AddStringToObject(json, "start", time->start);
    }
    if (time->end) {
        cJSON_AddStringToObject(json, "end", time->end);
    }
    return json;
}

Time* fromJsonTime(const cJSON* json) {
    if (!json) {
        return NULL;
    }
    Time* time = createTime();
    if (!time) {
        return NULL;
    }
    cJSON* start = cJSON_GetObjectItemCaseSensitive(json, "start");
    cJSON* end = cJSON_GetObjectItemCaseSensitive(json, "end");

    if (start && start->valuestring) {
        time->start = strdup(start->valuestring);
    }
    if (end && end->valuestring) {
        time->end = strdup(end->valuestring);
    }
    return time;
}

Week* createWeek() {
    Week* week = (Week*)hdmalloc(sizeof(Week));
    if (week) {
        week->weekdays = NULL;
        week->count = 0;
    }
    return week;
}

void destroyWeek(Week* week) {
    if (week) {
        hdfree(week->weekdays);
        hdfree(week);
    }
}

void setWeekdaysWeek(Week* week, Weekday* weekdays, int count) {
    if (!week) {
        return;
    }
    hdfree(week->weekdays);
    if (count > 0 && weekdays) {
        week->weekdays = (Weekday*)hdmalloc(count * sizeof(Weekday));
        memcpy(week->weekdays, weekdays, count * sizeof(Weekday));
        week->count = count;
    }
    else {
        week->weekdays = NULL;
        week->count = 0;
    }
}

char* getEnableWeek(const Week* week) {
    if (!week || week->count == 0) {
        return strdup("");
    }
    // Calculate the required memory
    size_t totalLen = 0;
    for (int i = 0; i < week->count; i++) {
        totalLen += strlen(weekdayToString(week->weekdays[i])) + 1; // +1 for comma or null
    }

    char* result = (char*)hdmalloc(totalLen);
    result[0] = '\0';

    for (int i = 0; i < week->count; i++) {
        if (i > 0) {
            strcat(result, ",");
        }
        strcat(result, weekdayToString(week->weekdays[i]));
    }

    return result;
}

void setEnableWeek(Week* week, const char* value) {
    if (!week || !value) {
        return;
    }

    hdfree(week->weekdays);
    week->weekdays = NULL;
    week->count = 0;


    char* copy = strdup(value);
    char* token = strtok(copy, ",");


    Weekday* temp = NULL;
    int capacity = 0;
    int count = 0;

    while (token) {
        if (count >= capacity) {
            capacity = capacity ? capacity * 2 : 8;
            temp = hdrealloc(temp, capacity * sizeof(Weekday));
        }

        Weekday day = stringToWeekday(token);
        temp[count++] = day;

        token = strtok(NULL, ",");
    }

    if (count > 0) {
        week->weekdays = temp;
        week->count = count;
    }
    else {
        hdfree(temp);
    }

    hdfree(copy);
}

cJSON* toJsonWeek(const Week* week) {
    if (!week) {
        return NULL;
    }
    cJSON* json = cJSON_CreateObject();
    if (week->count > 0) {
        char* enableStr = getEnableWeek(week);
        cJSON_AddStringToObject(json, "enable", enableStr);
        hdfree(enableStr);
    }
    else {
        cJSON_AddStringToObject(json, "enable", "");
    }
    return json;
}

Week* fromJsonWeek(const cJSON* json) {
    if (!json) {
        return NULL;
    }
    Week* week = createWeek();
    if (!week) {
        return NULL;
    }
    cJSON* enable = cJSON_GetObjectItemCaseSensitive(json, "enable");
    if (enable && enable->valuestring) {
        setEnableWeek(week, enable->valuestring);
    }

    return week;
}

PlayControl* createPlayControl() {
    PlayControl* pc = (PlayControl*)hdmalloc(sizeof(PlayControl));
    if (pc) {
        pc->dates = NULL;
        pc->date_count = 0;
        pc->times = NULL;
        pc->time_count = 0;
        pc->week = createWeek();
    }
    return pc;
}

void destroyPlayControl(PlayControl* pc) {
    if (!pc) {
        return;
    }

    for (int i = 0; i < pc->date_count; i++) {
        destroyDate(pc->dates[i]);
    }
    hdfree(pc->dates);

    for (int i = 0; i < pc->time_count; i++) {
        destroyTime(pc->times[i]);
    }
    hdfree(pc->times);

    destroyWeek(pc->week);

    hdfree(pc);
}

void setDatesPlayControl(PlayControl* pc, Date** dates, int count) {
    if (!pc) {
        return;
    }

    for (int i = 0; i < pc->date_count; i++) {
        destroyDate(pc->dates[i]);
    }
    hdfree(pc->dates);

    if (count > 0 && dates) {
        pc->dates = (Date**)hdmalloc(count * sizeof(Date*));
        for (int i = 0; i < count; i++) {
            pc->dates[i] = dates[i];
        }
        pc->date_count = count;
    }
    else {
        pc->dates = NULL;
        pc->date_count = 0;
    }
}

void setTimesPlayControl(PlayControl* pc, Time** times, int count) {
    if (!pc) {
        return;
    }

    for (int i = 0; i < pc->time_count; i++) {
        destroyTime(pc->times[i]);
    }
    hdfree(pc->times);

    if (count > 0 && times) {
        pc->times = (Time**)hdmalloc(count * sizeof(Time*));
        for (int i = 0; i < count; i++) {
            pc->times[i] = times[i];
        }
        pc->time_count = count;
    }
    else {
        pc->times = NULL;
        pc->time_count = 0;
    }
}

cJSON* toJsonPlayControl(const PlayControl* pc) {
    if (!pc) {
        return NULL;
    }
    cJSON* json = cJSON_CreateObject();

    cJSON* dateArray = cJSON_CreateArray();
    for (int i = 0; i < pc->date_count; i++) {
        cJSON* dateJson = toJsonDate(pc->dates[i]);
        if (dateJson) {
            cJSON_AddItemToArray(dateArray, dateJson);
        }
    }
    cJSON_AddItemToObject(json, "date", dateArray);

    cJSON* timeArray = cJSON_CreateArray();
    for (int i = 0; i < pc->time_count; i++) {
        cJSON* timeJson = toJsonTime(pc->times[i]);
        if (timeJson) {
            cJSON_AddItemToArray(timeArray, timeJson);
        }
    }
    cJSON_AddItemToObject(json, "time", timeArray);

    cJSON* weekJson = toJsonWeek(pc->week);
    if (weekJson) {
        cJSON_AddItemToObject(json, "week", weekJson);
    }
    return json;
}

PlayControl* fromJsonPlayControl(const cJSON* json) {
    if (!json) {
        return NULL;
    }
    PlayControl* pc = createPlayControl();
    if (!pc) {
        return NULL;
    }

    cJSON* dateArray = cJSON_GetObjectItemCaseSensitive(json, "date");
    if (dateArray && cJSON_IsArray(dateArray)) {
        int count = cJSON_GetArraySize(dateArray);
        Date** dates = (Date**)hdmalloc(count * sizeof(Date*));

        for (int i = 0; i < count; i++) {
            cJSON* item = cJSON_GetArrayItem(dateArray, i);
            dates[i] = fromJsonDate(item);
        }

        setDatesPlayControl(pc, dates, count);
        hdfree(dates);
    }

    cJSON* timeArray = cJSON_GetObjectItemCaseSensitive(json, "time");
    if (timeArray && cJSON_IsArray(timeArray)) {
        int count = cJSON_GetArraySize(timeArray);
        Time** times = (Time**)hdmalloc(count * sizeof(Time*));

        for (int i = 0; i < count; i++) {
            cJSON* item = cJSON_GetArrayItem(timeArray, i);
            times[i] = fromJsonTime(item);
        }

        setTimesPlayControl(pc, times, count);
        hdfree(times);
    }

    cJSON* weekJson = cJSON_GetObjectItemCaseSensitive(json, "week");
    if (weekJson) {
        destroyWeek(pc->week);
        pc->week = fromJsonWeek(weekJson);
    }

    return pc;
}

