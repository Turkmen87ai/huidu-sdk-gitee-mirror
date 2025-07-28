#include "Font.h"

Font* createFont() {
    Font* font = (Font*)hdmalloc(sizeof(Font));
    if (font) {
        font->name = strdup("");    // Default empty strings
        font->size = 14;            // Default number 14
        font->underline = false;
        font->bold = false;
        font->italic = false;
        font->color = strdup("#ff0000");// Red by default
    }
    return font;
}

Font* createWithSizeFont(int size) {
    Font* font = createFont();
    if (font) {
        font->size = size;
    }
    return font;
}

Font* createWithSizeAndColorFont(int size, const char* color) {
    Font* font = createWithSizeFont(size);
    if (font && color) {
        hdfree(font->color);
        font->color = strdup(color);
    }
    return font;
}

Font* createWithSizeColorAndBoldFont(int size, const char* color, bool bold) {
    Font* font = createWithSizeAndColorFont(size, color);
    if (font) {
        font->bold = bold;
    }
    return font;
}

Font* createFullFont(int size, const char* color, bool bold, bool italic, bool underline, const char* name) {
    Font* font = createWithSizeColorAndBoldFont(size, color, bold);
    if (font) {
        font->italic = italic;
        font->underline = underline;
        if (name) {
            hdfree(font->name);
            font->name = strdup(name);
        }
    }
    return font;
}

Font* copyFont(const Font* other) {
    if (!other) {
        return NULL;
    }
    return createFullFont(
        other->size,
        other->color,
        other->bold,
        other->italic,
        other->underline,
        other->name
    );
}

void destroyFont(Font* font) {
    if (!font) {
        return;
    }
    hdfree(font->name);
    hdfree(font->color);
    hdfree(font);
}

const char* getNameFont(const Font* font) {
    return font ? font->name : "";
}

void setNameFont(Font* font, const char* name) {
    if (font) {
        hdfree(font->name);
        font->name = name ? strdup(name) : strdup("");
    }
}

int getSizeFont(const Font* font) {
    return font ? font->size : 14;
}

void setSizeFont(Font* font, int size) {
    if (font) {
        font->size = size;
    }
}

bool isUnderlineFont(const Font* font) {
    return font ? font->underline : false;
}

void setUnderlineFont(Font* font, bool underline) {
    if (font) {
        font->underline = underline;
    }
}

bool isBoldFont(const Font* font) {
    return font ? font->bold : false;
}

void setBoldFont(Font* font, bool bold) {
    if (font) {
        font->bold = bold;
    }
}

bool isItalicFont(const Font* font) {
    return font ? font->italic : false;
}

void setItalicFont(Font* font, bool italic) {
    if (font) {
        font->italic = italic;
    }
}

const char* getColorFont(const Font* font) {
    return font ? font->color : "#ff0000";
}

void setColorFont(Font* font, const char* color) {
    if (font && color) {
        hdfree(font->color);
        font->color = strdup(color);
    }
}

cJSON* toJsonFont(const Font* font) {
    if (!font) {
        return NULL;
    }
    cJSON* json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "name", font->name);
    cJSON_AddNumberToObject(json, "size", font->size);
    cJSON_AddBoolToObject(json, "underline", font->underline);
    cJSON_AddBoolToObject(json, "bold", font->bold);
    cJSON_AddBoolToObject(json, "italic", font->italic);
    cJSON_AddStringToObject(json, "color", font->color);
    return json;
}

Font* fromJsonFont(const cJSON* json) {
    if (!json) {
        return NULL;
    }
    Font* font = createFont();
    if (!font) {
        return NULL;
    }

    cJSON* name = cJSON_GetObjectItemCaseSensitive(json, "name");
    cJSON* size = cJSON_GetObjectItemCaseSensitive(json, "size");
    cJSON* underline = cJSON_GetObjectItemCaseSensitive(json, "underline");
    cJSON* bold = cJSON_GetObjectItemCaseSensitive(json, "bold");
    cJSON* italic = cJSON_GetObjectItemCaseSensitive(json, "italic");
    cJSON* color = cJSON_GetObjectItemCaseSensitive(json, "color");

    if (name && name->valuestring) {
        hdfree(font->name);
        font->name = strdup(name->valuestring);
    }

    if (size) {
        font->size = size->valueint;
    }
    if (underline) {
        font->underline = cJSON_IsTrue(underline);
    }
    if (bold) {
        font->bold = cJSON_IsTrue(bold);
    }
    if (italic) {
        font->italic = cJSON_IsTrue(italic);
    }
    if (color && color->valuestring) {
        hdfree(font->color);
        font->color = strdup(color->valuestring);
    }

    return font;
}

