#ifndef TEXTNODE_H
#define TEXTNODE_H
#include <stdbool.h>
#include <string.h>
#include "cJSON.h"
#include "ContentNode.h"
#include "Effect.h"
#include "Font.h"
#include "posixPortMemory.h"
// Horizontally aligned enumeration
typedef enum {
    CENTER,
    LEFT,
    RIGHT
} TextAlignment;

// Vertically align the enumeration
typedef enum {
    MIDDLE,
    TOP,
    BOTTOM
} TextVAlignment;


typedef struct TextNode {
    ContentNode* base;  // Base class

    char* string;          // Text content
    bool multiLine;        // Whether multiple lines are displayed
    TextAlignment alignment; // Horizontal alignment
    TextVAlignment valignment; // Vertical alignment
    Effect* effect;        // Text effects
    Font* font;            // font
} TextNode;

// Horizontally aligned to convert strings
const char* alignmentToString(TextAlignment alignment);

// String to horizontal alignment
TextAlignment alignmentFromString(const char* str);

// Strings are vertically aligned
TextVAlignment valignmentFromString(const char* str);

// Vertical alignment to turn strings
const char* valignmentToString(TextVAlignment valignment);

TextNode* createTextNode();

TextNode* createWithTextTextNode(const char* text);

TextNode* copyTextNode(const TextNode* other);

void destroyTextNode(TextNode* node);

const char* getStringTextNode(const TextNode* node);

void setStringTextNode(TextNode* node, const char* string);

bool getMultiLineTextNode(const TextNode* node);

void setMultiLineTextNode(TextNode* node, bool multiLine);

TextAlignment getAlignmentTextNode(const TextNode* node);

void setAlignmentTextNode(TextNode* node, TextAlignment alignment);

TextVAlignment getVAlignmentTextNode(const TextNode* node);

void setVAlignmentTextNode(TextNode* node, TextVAlignment valignment);

Effect* getEffectTextNode(const TextNode* node);

void setEffectTextNode(TextNode* node, Effect* effect);

Font* getFontTextNode(const TextNode* node);

void setFontTextNode(TextNode* node, Font* font);

cJSON* toJsonTextNode(const TextNode* node);

TextNode* fromJsonTextNode(const cJSON* json);
#endif
