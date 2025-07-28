#ifndef HTTPAPI_H
#define HTTPAPI_H
#include "Config.h"
#include "curl/curl.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "posixPortHmacmd5.h"
#include "posixPortHttp.h"
#include "posixPortMemory.h"
#include <stddef.h>
typedef struct {
    char* sdkKey;
    char* sdkSecret;
    char* devApiUrl;
    char* fileApiUrl;
    char* programApiUrl;
} HttpApi;


// Generate the current time string
char* getCurrentDate();

// Initialize the HttpApi
HttpApi* createHttpApi();

HttpApi* createHttpApiWithHost(const char* hostUrl);

// Clean up the HttpApi
void destroyHttpApi(HttpApi* api);

// Signature request header
httpHeaderlist* signHeader(const char* body, const char* sdkKey, const char* sdkSecret);

// Universal HTTP request function
char* httpRequest(const char* method, const char* url, const char* body,
    const char* file_path, int timeout_ms);

// Equipment list
char* deviceList(HttpApi* api);

// Equipment operation
char* device(HttpApi* api, const char* body);

// Program operation
char* program(HttpApi* api, const char* body);

// File upload
char* uploadFile(HttpApi* api, const char* filePath);
#endif
