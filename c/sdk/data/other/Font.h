#ifndef FONT_H
#define FONT_H
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON.h"
#include "posixPortMemory.h"
typedef struct {
    char* name;        // Font name
    int size;          // Font size
    bool underline;    // Whether there is an underscore
    bool bold;         // bold or not
    bool italic;       // Italic or not
    char* color;       // Font color (hex string)
} Font;

// Create a default font
Font* createFont();

// Constructors with font size
Font* createWithSizeFont(int size);

// Constructors with size and color
Font* createWithSizeAndColorFont(int size, const char* color);

// Constructors with size, color, bold
Font* createWithSizeColorAndBoldFont(int size, const char* color, bool bold);

// A complete constructor with multiple parameters
Font* createFullFont(int size, const char* color, bool bold, bool italic, bool underline, const char* name);

// Copy fonts
Font* copyFont(const Font* other);

// Free up font resources
void destroyFont(Font* font);

const char* getNameFont(const Font* font);

void setNameFont(Font* font, const char* name);

int getSizeFont(const Font* font);

void setSizeFont(Font* font, int size);

bool isUnderlineFont(const Font* font);

void setUnderlineFont(Font* font, bool underline);

bool isBoldFont(const Font* font);

void setBoldFont(Font* font, bool bold);

bool isItalicFont(const Font* font);

void setItalicFont(Font* font, bool italic);

const char* getColorFont(const Font* font);

void setColorFont(Font* font, const char* color);

cJSON* toJsonFont(const Font* font);

Font* fromJsonFont(const cJSON* json);

#endif
