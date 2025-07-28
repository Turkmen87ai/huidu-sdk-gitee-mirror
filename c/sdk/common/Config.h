#ifndef CONFIG_H
#define CONFIG_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cJSON.h"
#include "posixPortMemory.h"
// Configure the structure
typedef struct {
    char* host;
    char* sdkKey;
    char* sdkSecret;
} Config;

// Initialize Configuration (Manual Setup)
void InitSdk(const char* host, const char* sdkKey, const char* sdkSecret);

// Get the configuration value
const char* GetHost();
const char* GetSdkKey();
const char* GetSdkSecret();

// Destroy resources
void destroyConfig();


#endif