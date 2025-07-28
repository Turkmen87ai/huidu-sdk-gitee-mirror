#include "DialClockNode.h"

DialClockNode* createDialClockNode() {
    DialClockNode* node = (DialClockNode*)hdmalloc(sizeof(DialClockNode));
    if (!node) {
        return NULL;
    }

    node->base = createContentNode();
    setTypeContentNode(node->base, "dialClock");

    node->timezone = NULL;
    node->timeOffset = NULL;
    node->font = NULL;
    node->title = createStringColorClockParam();
    if (node->title) {
        setDisplayStringColorClockParam(node->title, "0");
    }

    node->date = NULL;
    node->week = NULL;
    node->time = NULL;
    node->ampm = NULL;
    node->style = NULL;
    node->spacing = 0;
    node->enabled12H = false;
    node->swapWeekAndDay = false;

    return node;
}

DialClockNode* copyDialClockNode(const DialClockNode* other) {
    if (!other) {
        return NULL;
    }
    DialClockNode* node = createDialClockNode();
    if (!node) {
        return NULL;
    }
    node->base = copyContentNode(other->base);

    if (other->timezone) {
        node->timezone = strdup(other->timezone);
    }
    if (other->timeOffset) {
        node->timeOffset = strdup(other->timeOffset);
    }

    if (other->font) node->font = copyFont(other->font);
    if (other->title) {
        StringColorClockParam* newTitle = copyStringColorClockParam(other->title);
        if (node->title) {
            destroyStringColorClockParam(node->title);
        }
        node->title = newTitle;
    }
    if (other->date) {
        FormatColorClockParam* newDate = copyFormatColorClockParam(other->date);
        if (node->date) {
            destroyFormatColorClockParam(node->date);
        }
        node->date = newDate;
    }
    if (other->week) {
        FormatColorClockParam* newWeek = copyFormatColorClockParam(other->week);
        if (node->week) {
            destroyFormatColorClockParam(node->week);
        }
        node->week = newWeek;
    }
    if (other->time) {
        FormatColorClockParam* newTime = copyFormatColorClockParam(other->time);
        if (node->time) {
            destroyFormatColorClockParam(node->time);
        }
        node->time = newTime;
    }
    if (other->ampm) {
        FormatColorClockParam* newAmpm = copyFormatColorClockParam(other->ampm);
        if (node->ampm) {
            destroyFormatColorClockParam(node->ampm);
        }
        node->ampm = newAmpm;
    }

    if (other->style) {
        StyleClockParam* newStyle = copyStyleClockParam(other->style);
        if (node->style) {
            destroyStyleClockParam(node->style);
        }
        node->style = newStyle;
    }

    node->spacing = other->spacing;
    node->enabled12H = other->enabled12H;
    node->swapWeekAndDay = other->swapWeekAndDay;
    return node;
}

void destroyDialClockNode(DialClockNode* node) {
    if (!node) {
        return;
    }

    hdfree(node->timezone);
    hdfree(node->timeOffset);

    if (node->font) {
        destroyFont(node->font);
    }
    if (node->title) {
        destroyStringColorClockParam(node->title);
    }
    if (node->date) {
        destroyFormatColorClockParam(node->date);
    }
    if (node->week) {
        destroyFormatColorClockParam(node->week);
    }
    if (node->time) {
        destroyFormatColorClockParam(node->time);
    }
    if (node->ampm) {
        destroyFormatColorClockParam(node->ampm);
    }
    if (node->style) {
        destroyStyleClockParam(node->style);
    }

    destroyContentNode(node->base);

    hdfree(node);
}

const char* getTimezoneDialClockNode(const DialClockNode* node) {
    return node ? node->timezone : NULL;
}

void setTimezoneDialClockNode(DialClockNode* node, const char* timezone) {
    if (!node) {
        return;
    }
    hdfree(node->timezone);
    node->timezone = timezone ? strdup(timezone) : NULL;
}

const char* getTimeOffsetDialClockNode(const DialClockNode* node) {
    return node ? node->timeOffset : NULL;
}

void setTimeOffsetDialClockNode(DialClockNode* node, const char* timeOffset) {
    if (!node) {
        return;
    }
    hdfree(node->timeOffset);
    node->timeOffset = timeOffset ? strdup(timeOffset) : NULL;
}

Font* getFontDialClockNode(const DialClockNode* node) {
    return node ? node->font : NULL;
}

void setFontDialClockNode(DialClockNode* node, Font* font) {
    if (!node) {
        return;
    }
    if (node->font) {
        destroyFont(node->font);
    }
    node->font = font;
}

StringColorClockParam* getTitleDialClockNode(const DialClockNode* node) {
    return node ? node->title : NULL;
}

void setTitleDialClockNode(DialClockNode* node, StringColorClockParam* title) {
    if (!node) {
        return;
    }
    if (node->title) {
        destroyStringColorClockParam(node->title);
    }
    node->title = title;
}

FormatColorClockParam* getDateDialClockNode(const DialClockNode* node) {
    return node ? node->date : NULL;
}

void setDateDialClockNode(DialClockNode* node, FormatColorClockParam* date) {
    if (!node) {
        return;
    }
    if (node->date) {
        destroyFormatColorClockParam(node->date);
    }
    node->date = date;
}

FormatColorClockParam* getWeekDialClockNode(DialClockNode* node) {
    return node ? node->week : NULL;
}

void setWeekDialClockNode(DialClockNode* node, FormatColorClockParam* week) {
    if (!node) {
        return;
    }
    if (node->week) {
        destroyFormatColorClockParam(node->week);
    }
    node->week = week;
}

FormatColorClockParam* getTimeDialClockNode(DialClockNode* node) {
    return node ? node->time : NULL;
}

void setTimeDialClockNode(DialClockNode* node, FormatColorClockParam* time) {
    if (!node) {
        return;
    }
    if (node->time) {
        destroyFormatColorClockParam(node->time);
    }
    node->time = time;
}

StyleClockParam* getStyleDialClockNode(DialClockNode* node) {
    return node ? node->style : NULL;
}

void setStyleDialClockNode(DialClockNode* node, StyleClockParam* style) {
    if (!node) {
        return;
    }
    if (node->style) {
        destroyStyleClockParam(node->style);
    }
    node->style = style;
}

FormatColorClockParam* getAmpmDialClockNode(DialClockNode* node) {
    return node ? node->ampm : NULL;
}

void setAmpmDialClockNode(DialClockNode* node, FormatColorClockParam* ampm) {
    if (!node) {
        return;
    }
    if (node->ampm) {
        destroyFormatColorClockParam(node->ampm);
    }
    node->ampm = ampm;
}

FmtStyleClockParam* getClockFmtStyleDialClockNode(DialClockNode* node) {
    FmtStyleClockParam* style = createFmtStyleClockParam();
    if (node) {
        if (node->swapWeekAndDay) {
            setSwapFmtStyleClockParam(style, "1");
        }
        if (node->spacing > 0) {
            char spaceStr[12];
            snprintf(spaceStr, sizeof(spaceStr), "%d", node->spacing);
            setSpaceFmtStyleClockParam(style, spaceStr);
        }
    }
    return style;
}

int getSpacingDialClockNode(DialClockNode* node) {
    return node ? node->spacing : 0;
}

void setSpacingDialClockNode(DialClockNode* node, int spacing) {
    if (node) {
        node->spacing = spacing;
    }
}

int getEnabled12HDialClockNode(DialClockNode* node) {
    return node ? node->enabled12H : false;
}

void setEnabled12HDialClockNode(DialClockNode* node, int enabled) {
    if (node) {
        node->enabled12H = enabled;
    }
}

int getSwapWeekAndDayDialClockNode(DialClockNode* node) {
    return node ? node->swapWeekAndDay : false;
}

void setSwapWeekAndDayDialClockNode(DialClockNode* node, int swap) {
    if (node) {
        node->swapWeekAndDay = swap;
    }
}

cJSON* toJsonDialClockNode(const DialClockNode* node) {
    if (!node) return NULL;

    cJSON* json = cJSON_CreateObject();
    if (!json) {
		return NULL;
	}
	
    toJsonContentNode(node->base, json);

    if (node->timezone) {
		cJSON_AddStringToObject(json, "timezone", node->timezone);
	}
	
    if (node->timeOffset) {
		cJSON_AddStringToObject(json, "timeOffset", node->timeOffset);
	}
	
    if (node->font) {
        cJSON* fontJson = toJsonFont(node->font);
        if (fontJson) cJSON_AddItemToObject(json, "font", fontJson);
    }

    if (node->title) {
        cJSON* titleJson = toJsonStringColorClockParam(node->title);
        if (titleJson) cJSON_AddItemToObject(json, "title", titleJson);
    }

    if (node->date) {
        cJSON* dateJson = toJsonFormatColorClockParam(node->date);
        if (dateJson) cJSON_AddItemToObject(json, "date", dateJson);
    }

    if (node->week) {
        cJSON* weekJson = toJsonFormatColorClockParam(node->week);
        if (weekJson) cJSON_AddItemToObject(json, "week", weekJson);
    }

    if (node->time) {
        cJSON* timeJson = toJsonFormatColorClockParam(node->time);
        if (timeJson) cJSON_AddItemToObject(json, "time", timeJson);
    }

    if (node->ampm) {
        cJSON* ampmJson = toJsonFormatColorClockParam(node->ampm);
        if (ampmJson) cJSON_AddItemToObject(json, "ampm", ampmJson);
    }

    if (node->style) {
        cJSON* styleJson = toJsonStyleClockParam(node->style);
        if (styleJson) cJSON_AddItemToObject(json, "style", styleJson);
    }

    cJSON_AddNumberToObject(json, "spacing", node->spacing);
    cJSON_AddBoolToObject(json, "enabled12H", node->enabled12H);
    cJSON_AddBoolToObject(json, "swapWeekAndDay", node->swapWeekAndDay);

    return json;
}

DialClockNode* fromJsonDialClockNode(const cJSON* json) {
    if (!json) {
		return NULL;
	}

    DialClockNode* node = createDialClockNode();
    if (!node) {
		return NULL;
	}

    const cJSON* baseJson = cJSON_GetObjectItem(json, "base");
    if (baseJson) {
        node->base = fromJsonContentNode(baseJson);
    }

    const cJSON* timezone = cJSON_GetObjectItem(json, "timezone");
    if (timezone && cJSON_IsString(timezone)) {
        setTimezoneDialClockNode(node, timezone->valuestring);
    }

    const cJSON* timeOffset = cJSON_GetObjectItem(json, "timeOffset");
    if (timeOffset && cJSON_IsString(timeOffset)) {
        setTimeOffsetDialClockNode(node, timeOffset->valuestring);
    }

    const cJSON* fontJson = cJSON_GetObjectItem(json, "font");
    if (fontJson) {
        Font* font = fromJsonFont(fontJson);
        if (font) {
            setFontDialClockNode(node, font);
        }
    }

    const cJSON* titleJson = cJSON_GetObjectItem(json, "title");
    if (titleJson) {
        StringColorClockParam* title = fromJsonStringColorClockParam(titleJson);
        if (title) {
            setTitleDialClockNode(node, title);
        }
    }

    const cJSON* dateJson = cJSON_GetObjectItem(json, "date");
    if (dateJson) {
        FormatColorClockParam* date = fromJsonFormatColorClockParam(dateJson);
        if (date) {
            setDateDialClockNode(node, date);
        }
    }

    const cJSON* weekJson = cJSON_GetObjectItem(json, "week");
    if (weekJson) {
        FormatColorClockParam* week = fromJsonFormatColorClockParam(weekJson);
        if (week) {
            setWeekDialClockNode(node, week);
        }
    }

    const cJSON* timeJson = cJSON_GetObjectItem(json, "time");
    if (timeJson) {
        FormatColorClockParam* time = fromJsonFormatColorClockParam(timeJson);
        if (time) {
            setTimeDialClockNode(node, time);
        }
    }

    const cJSON* ampmJson = cJSON_GetObjectItem(json, "ampm");
    if (ampmJson) {
        FormatColorClockParam* ampm = fromJsonFormatColorClockParam(ampmJson);
        if (ampm) {
            setAmpmDialClockNode(node, ampm);
        }
    }

    const cJSON* spacing = cJSON_GetObjectItem(json, "spacing");
    if (spacing && cJSON_IsNumber(spacing)) {
        setSpacingDialClockNode(node, spacing->valueint);
    }

    const cJSON* enabled12H = cJSON_GetObjectItem(json, "enabled12H");
    if (enabled12H && cJSON_IsBool(enabled12H)) {
        setEnabled12HDialClockNode(node, cJSON_IsTrue(enabled12H));
    }

    const cJSON* swapWeekAndDay = cJSON_GetObjectItem(json, "swapWeekAndDay");
    if (swapWeekAndDay && cJSON_IsBool(swapWeekAndDay)) {
        setSwapWeekAndDayDialClockNode(node, cJSON_IsTrue(swapWeekAndDay));
    }

    return node;
}

