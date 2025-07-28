#include "ClockParam.h"

// FormatColor
FormatColorClockParam* createFormatColorClockParam() {
    FormatColorClockParam* fc = (FormatColorClockParam*)hdmalloc(sizeof(FormatColorClockParam));
    if (fc) {
        fc->display = NULL;
        fc->format = NULL;
        fc->color = NULL;
        fc->size = 0;
    }
    return fc;
}

FormatColorClockParam* copyFormatColorClockParam(const FormatColorClockParam* src) {
    if (!src) {
        return NULL;
    }
    FormatColorClockParam* dst = createFormatColorClockParam();
    if (dst) {
        dst->display = strdup(src->display);
        dst->format = strdup(src->format);
        dst->color = strdup(src->color);
        dst->size = src->size;
    }
    return dst;
}

void destroyFormatColorClockParam(FormatColorClockParam* fc) {
    if (!fc) {
        return;
    }
    hdfree(fc->display);
    hdfree(fc->format);
    hdfree(fc->color);
    hdfree(fc);
}

// StringColor
StringColorClockParam* createStringColorClockParam() {
    StringColorClockParam* sc = (StringColorClockParam*)hdmalloc(sizeof(StringColorClockParam));
    if (sc) {
        sc->display = NULL;
        sc->string = NULL;
        sc->color = NULL;
        sc->size = 0;
    }
    return sc;
}

StringColorClockParam* copyStringColorClockParam(const StringColorClockParam* src) {
    if (!src) {
		return NULL;
	}
    StringColorClockParam* dst = createStringColorClockParam();
    if (dst) {
        dst->display = strdup(src->display);
        dst->string = strdup(src->string);
        dst->color = strdup(src->color);
        dst->size = src->size;
    }
    return dst;
}

void destroyStringColorClockParam(StringColorClockParam* sc) {
    if (!sc) {
        return;
    }
    hdfree(sc->display);
    hdfree(sc->string);
    hdfree(sc->color);
    hdfree(sc);
}

void setDisplayStringColorClockParam(StringColorClockParam* sc, const char* display) {
    if (!sc) return;
    hdfree(sc->display);
    sc->display = strdup(display);
}

// Style
StyleClockParam* createStyleClockParam() {
    StyleClockParam* style = (StyleClockParam*)hdmalloc(sizeof(StyleClockParam));
    if (style) {
        style->hourHandColor = NULL;
        style->minuteHandColor = NULL;
        style->secondHandColor = NULL;
        style->hourScaleColor = NULL;
        style->minuteScaleColor = NULL;
        style->fontName = NULL;
        style->fontSize = 0;
    }
    return style;
}

StyleClockParam* copyStyleClockParam(const StyleClockParam* src) {
    if (!src) {
		return NULL;
	}
    StyleClockParam* dst = createStyleClockParam();
    if (dst) {
        dst->hourHandColor = strdup(src->hourHandColor);
        dst->minuteHandColor = strdup(src->minuteHandColor);
        dst->secondHandColor = strdup(src->secondHandColor);
        dst->hourScaleColor = strdup(src->hourScaleColor);
        dst->minuteScaleColor = strdup(src->minuteScaleColor);
        dst->fontName = strdup(src->fontName);
        dst->fontSize = src->fontSize;
    }
    return dst;
}

void destroyStyleClockParam(StyleClockParam* style) {
    if (!style) {
		return;
	}
    hdfree(style->hourHandColor);
    hdfree(style->minuteHandColor);
    hdfree(style->secondHandColor);
    hdfree(style->hourScaleColor);
    hdfree(style->minuteScaleColor);
    hdfree(style->fontName);
    hdfree(style);
}

// FmtStyle
FmtStyleClockParam* createFmtStyleClockParam() {
    FmtStyleClockParam* fs = (FmtStyleClockParam*)hdmalloc(sizeof(FmtStyleClockParam));
    if (fs) {
        fs->swap = NULL;
        fs->space = NULL;
    }
    return fs;
}

FmtStyleClockParam* copyFmtStyleClockParam(const FmtStyleClockParam* src) {
    if (!src) {
        return NULL;
    }
    FmtStyleClockParam* dst = createFmtStyleClockParam();
    if (dst) {
        dst->swap = strdup(src->swap);
        dst->space = strdup(src->space);
    }
    return dst;
}

void destroyFmtStyleClockParam(FmtStyleClockParam* fs) {
    if (!fs) {
        return;
    }
    hdfree(fs->swap);
    hdfree(fs->space);
    hdfree(fs);
}

void setSwapFmtStyleClockParam(FmtStyleClockParam* fs, const char* swap) {
    if (!fs) {
        return;
    }
    hdfree(fs->swap);
    fs->swap = strdup(swap);
}

void setSpaceFmtStyleClockParam(FmtStyleClockParam* fs, const char* space) {
    if (!fs) {
        return;
    }
    hdfree(fs->space);
    fs->space = strdup(space);
}

cJSON* toJsonFormatColorClockParam(const FormatColorClockParam* fc) {
    if (!fc) {
        return NULL;
    }
    cJSON* json = cJSON_CreateObject();
    if (fc->display) {
        cJSON_AddStringToObject(json, "display", fc->display);
    }
    if (fc->format) {
        cJSON_AddStringToObject(json, "format", fc->format);
    }
    if (fc->color) {
        cJSON_AddStringToObject(json, "color", fc->color);
    }
    cJSON_AddNumberToObject(json, "size", fc->size);
    return json;
}

cJSON* toJsonStringColorClockParam(const StringColorClockParam* sc) {
    if (!sc) {
        return NULL;
    }
    cJSON* json = cJSON_CreateObject();
    if (sc->display) {
        cJSON_AddStringToObject(json, "display", sc->display);
    }
    if (sc->string) {
        cJSON_AddStringToObject(json, "string", sc->string);
    }
    cJSON_AddNumberToObject(json, "size", sc->size);
    if (sc->color) {
        cJSON_AddStringToObject(json, "color", sc->color);
    }
    return json;
}

cJSON* toJsonStyleClockParam(const StyleClockParam* style) {
    if (!style) {
        return NULL;
    }
    cJSON* json = cJSON_CreateObject();
    if (style->hourHandColor) {
        cJSON_AddStringToObject(json, "hourHandColor", style->hourHandColor);
    }
    if (style->minuteHandColor) {
        cJSON_AddStringToObject(json, "minuteHandColor", style->minuteHandColor);
    }
    if (style->secondHandColor) {
        cJSON_AddStringToObject(json, "secondHandColor", style->secondHandColor);
    }
    if (style->hourScaleColor) {
        cJSON_AddStringToObject(json, "hourScaleColor", style->hourScaleColor);
    }
    if (style->minuteScaleColor) {
        cJSON_AddStringToObject(json, "minuteScaleColor", style->minuteScaleColor);
    }
    if (style->fontName) {
        cJSON_AddStringToObject(json, "fontName", style->fontName);
    }
    cJSON_AddNumberToObject(json, "fontSize", style->fontSize);
    return json;
}

cJSON* toJsonFmtStyleClockParam(const FmtStyleClockParam* fs) {
    if (!fs) {
        return NULL;
    }
    cJSON* json = cJSON_CreateObject();
    if (fs->swap) {
        cJSON_AddStringToObject(json, "swap", fs->swap);
    }
    if (fs->space) {
        cJSON_AddStringToObject(json, "space", fs->space);
    }
    return json;
}

FormatColorClockParam* fromJsonFormatColorClockParam(const cJSON* json) {
    if (!json) {
        return NULL;
    }
    FormatColorClockParam* fc = createFormatColorClockParam();

    cJSON* display = cJSON_GetObjectItemCaseSensitive(json, "display");
    cJSON* format = cJSON_GetObjectItemCaseSensitive(json, "format");
    cJSON* color = cJSON_GetObjectItemCaseSensitive(json, "color");
    cJSON* size = cJSON_GetObjectItemCaseSensitive(json, "size");

    if (display && display->valuestring) {
        fc->display = strdup(display->valuestring);
    }
    if (format && format->valuestring) {
        fc->format = strdup(format->valuestring);
    }
    if (color && color->valuestring) {
        fc->color = strdup(color->valuestring);
    }
    if (size) {
        fc->size = size->valueint;
    }
    return fc;
}

StringColorClockParam* fromJsonStringColorClockParam(const cJSON* json) {
    if (!json) {
        return NULL;
    }
    StringColorClockParam* sc = createStringColorClockParam();

    cJSON* display = cJSON_GetObjectItemCaseSensitive(json, "display");
    cJSON* string = cJSON_GetObjectItemCaseSensitive(json, "string");
    cJSON* size = cJSON_GetObjectItemCaseSensitive(json, "size");
    cJSON* color = cJSON_GetObjectItemCaseSensitive(json, "color");

    if (display && display->valuestring) {
        sc->display = strdup(display->valuestring);
    }
    if (string && string->valuestring) {
        sc->string = strdup(string->valuestring);
    }
    if (size) {
        sc->size = size->valueint;
    }
    if (color && color->valuestring) {
        sc->color = strdup(color->valuestring);
    }
    return sc;
}

StyleClockParam* fromJsonStyleClockParam(const cJSON* json) {
    if (!json) {
        return NULL;
    }
    StyleClockParam* style = createStyleClockParam();

    cJSON* hourHandColor = cJSON_GetObjectItemCaseSensitive(json, "hourHandColor");
    cJSON* minuteHandColor = cJSON_GetObjectItemCaseSensitive(json, "minuteHandColor");
    cJSON* secondHandColor = cJSON_GetObjectItemCaseSensitive(json, "secondHandColor");
    cJSON* hourScaleColor = cJSON_GetObjectItemCaseSensitive(json, "hourScaleColor");
    cJSON* minuteScaleColor = cJSON_GetObjectItemCaseSensitive(json, "minuteScaleColor");
    cJSON* fontName = cJSON_GetObjectItemCaseSensitive(json, "fontName");
    cJSON* fontSize = cJSON_GetObjectItemCaseSensitive(json, "fontSize");

    if (hourHandColor && hourHandColor->valuestring) {
        style->hourHandColor = strdup(hourHandColor->valuestring);
    }
    if (minuteHandColor && minuteHandColor->valuestring) {
        style->minuteHandColor = strdup(minuteHandColor->valuestring);
    }
    if (secondHandColor && secondHandColor->valuestring) {
        style->secondHandColor = strdup(secondHandColor->valuestring);
    }
    if (hourScaleColor && hourScaleColor->valuestring) {
        style->hourScaleColor = strdup(hourScaleColor->valuestring);
    }
    if (minuteScaleColor && minuteScaleColor->valuestring) {
        style->minuteScaleColor = strdup(minuteScaleColor->valuestring);
    }
    if (fontName && fontName->valuestring) {
        style->fontName = strdup(fontName->valuestring);
    }
    if (fontSize) {
        style->fontSize = fontSize->valueint;
    }
    return style;
}

FmtStyleClockParam* fromJsonFmtStyleClockParam(const cJSON* json) {
    if (!json) {
        return NULL;
    }
    FmtStyleClockParam* fs = createFmtStyleClockParam();

    cJSON* swap = cJSON_GetObjectItemCaseSensitive(json, "swap");
    cJSON* space = cJSON_GetObjectItemCaseSensitive(json, "space");

    if (swap && swap->valuestring) {
        fs->swap = strdup(swap->valuestring);
    }
    if (space && space->valuestring) {
        fs->space = strdup(space->valuestring);
    }
    return fs;
}

