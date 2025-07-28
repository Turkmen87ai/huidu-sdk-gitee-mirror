#include "Config.h"

// Configure instances globally
static Config globalConfig = { NULL, NULL, NULL };

// Initialize the configuration from the JSON file
static void InitFromFile() {
    const char* filename = "./config/application.json";
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Error: Cannot open config file %s\n", filename);
        return;
    }

    // Read the contents of the file
    fseek(fp, 0, SEEK_END);
    long len = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char* data = (char*)hdmalloc(len + 1);
    if (!data) {
        fclose(fp);
        return;
    }

    fread(data, 1, len, fp);
    data[len] = '\0';
    fclose(fp);

    // Parse JSON
    cJSON* root = cJSON_Parse(data);
    if (!root) {
        fprintf(stderr, "Error: Invalid JSON in config file\n");
        free(data);
        return;
    }

    // Extract configuration items
    cJSON* item;
    if ((item = cJSON_GetObjectItem(root, "host")) && cJSON_IsString(item)) {
        InitSdk(item->valuestring, NULL, NULL);
    }
    if ((item = cJSON_GetObjectItem(root, "sdkKey")) && cJSON_IsString(item)) {
        free(globalConfig.sdkKey);
        globalConfig.sdkKey = strdup(item->valuestring);
    }
    if ((item = cJSON_GetObjectItem(root, "sdkSecret")) && cJSON_IsString(item)) {
        free(globalConfig.sdkSecret);
        globalConfig.sdkSecret = strdup(item->valuestring);
    }

    // Clean up resources
    cJSON_Delete(root);
    hdfree(data);
}

void InitSdk(const char* host, const char* sdkKey, const char* sdkSecret) {
    // Free up old memory
    hdfree(globalConfig.host);
    hdfree(globalConfig.sdkKey);
    hdfree(globalConfig.sdkSecret);

    // If not specified, the configuration file is read
    if (!host || !sdkKey || !sdkSecret) {
        InitFromFile();
    }

    // Allocate new memory and copy the values
    globalConfig.host = host ? strdup(host) : NULL;
    globalConfig.sdkKey = sdkKey ? strdup(sdkKey) : NULL;
    globalConfig.sdkSecret = sdkSecret ? strdup(sdkSecret) : NULL;
}

const char* GetHost() { return globalConfig.host ? globalConfig.host : ""; }
const char* GetSdkKey() { return globalConfig.sdkKey ? globalConfig.sdkKey : ""; }
const char* GetSdkSecret() { return globalConfig.sdkSecret ? globalConfig.sdkSecret : ""; }

void destroyConfig() {
    hdfree(globalConfig.host);
    hdfree(globalConfig.sdkKey);
    hdfree(globalConfig.sdkSecret);
    globalConfig.host = NULL;
    globalConfig.sdkKey = NULL;
    globalConfig.sdkSecret = NULL;
}
