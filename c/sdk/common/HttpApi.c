#include "HttpApi.h"
#include <stdio.h>
#include <string.h>

#if defined(_WIN32)
#include <rpcdce.h>
#elif defined(__linux__) || defined(__APPLE__) || defined(__unix__)
#include <fcntl.h>
#include <unistd.h>
#endif

#if defined(_WIN32)
#define HDSPRINTF(dest, size, format, ...) sprintf_s(dest, size, format, __VA_ARGS__)
#else
#define HDSPRINTF(dest, size, format, ...) snprintf(dest, size, format, __VA_ARGS__)
#endif

char* getCurrentDate() {
    time_t now = time(NULL);
    struct tm* tm = localtime(&now);
    char* buffer = (char*)hdmalloc(64);
    if (!buffer) return NULL;

    strftime(buffer, 64, "%a, %d %b %Y %H:%M:%S %Z", tm);
    return buffer;
}

char* generateUuid() {
    unsigned char bytes[16]; // Stores 128 bits of random data

    // Assign and format the UUID string
    char* str = (char*)malloc(37);
    if (!str) return NULL;

    // Secure random number generation across platforms
#if defined(_WIN32)
    UUID uuid;
    uuid.Data1 = rand();
    HDSPRINTF(str, 37, "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
        uuid.Data1, uuid.Data2, uuid.Data3,
        uuid.Data4[0], uuid.Data4[1], uuid.Data4[2], uuid.Data4[3],
        uuid.Data4[4], uuid.Data4[5], uuid.Data4[6], uuid.Data4[7]);
    return str;
#else
    // Unix/Linux/macOS use /dev/urandom
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) return NULL;
    if (read(fd, bytes, sizeof(bytes)) != sizeof(bytes)) {
        close(fd);
        return NULL;
    }
    close(fd);
#endif
    // Set UUID versions (4) and variants (RFC 4122)
    bytes[6] = (bytes[6] & 0x0F) | 0x40; // 7 bytes high 4 bits set to 0100
    bytes[8] = (bytes[8] & 0x3F) | 0x80; // 9 bits high 2 bits set to 10

    HDSPRINTF(str, 37, "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
        bytes[0], bytes[1], bytes[2], bytes[3],
        bytes[4], bytes[5],
        bytes[6], bytes[7],
        bytes[8], bytes[9],
        bytes[10], bytes[11], bytes[12], bytes[13], bytes[14], bytes[15]);

    return str;
}

HttpApi* createHttpApi() {
    HttpApi* api = (HttpApi*)hdmalloc(sizeof(HttpApi));
    if (!api) return NULL;

    api->sdkKey = strdup(GetSdkKey());
    api->sdkSecret = strdup(GetSdkSecret());

    // Build an API URL
    size_t baseLen = strlen(GetHost());
    size_t devUrlLen = baseLen + strlen("/api/device/") + 1;
    size_t fileUrlLen = baseLen + strlen("/api/file/") + 1;
    size_t programUrlLen = baseLen + strlen("/api/program/") + 1;
    api->devApiUrl = (char*)hdmalloc(devUrlLen);
    HDSPRINTF(api->devApiUrl, devUrlLen, "%s/api/device/", GetHost());

    api->fileApiUrl = (char*)hdmalloc(fileUrlLen);
    HDSPRINTF(api->fileApiUrl, fileUrlLen, "%s/api/file/", GetHost());

    api->programApiUrl = (char*)hdmalloc(programUrlLen);
    HDSPRINTF(api->programApiUrl, programUrlLen, "%s/api/program/", GetHost());

    return api;
}

HttpApi* createHttpApiWithHost(const char* hostUrl) {
    HttpApi* api = malloc(sizeof(HttpApi));
    if (!api) return NULL;

    api->sdkKey = strdup(GetSdkKey());
    api->sdkSecret = strdup(GetSdkSecret());

    // Build an API URL
    size_t baseLen = strlen(hostUrl);
    size_t devUrlLen = baseLen + strlen("/api/device/") + 1;
    size_t fileUrlLen = baseLen + strlen("/api/file/") + 1;
    size_t programUrlLen = baseLen + strlen("/api/program/") + 1;
    api->devApiUrl = (char*)hdmalloc(devUrlLen);
    HDSPRINTF(api->devApiUrl, devUrlLen, "%s/api/device/", hostUrl);

    api->fileApiUrl = (char*)hdmalloc(fileUrlLen);
    HDSPRINTF(api->fileApiUrl, fileUrlLen, "%s/api/file/", hostUrl);

    api->programApiUrl = (char*)hdmalloc(programUrlLen);
    HDSPRINTF(api->programApiUrl, programUrlLen, "%s/api/program/", hostUrl);

    return api;
}

void destroyHttpApi(HttpApi* api) {
    if (!api) return;

    hdfree(api->sdkKey);
    hdfree(api->sdkSecret);
    hdfree(api->devApiUrl);
    hdfree(api->fileApiUrl);
    hdfree(api->programApiUrl);
    hdfree(api);
}

httpHeaderlist* signHeader(const char* body, const char* sdkKey, const char* sdkSecret) {
    httpHeaderlist* headers = NULL;
    char            header[256] = { 0 };

    // Generate UUID
    char* cuid = generateUuid();
    if (cuid == NULL) {
        return NULL;
    }
    HDSPRINTF(header, sizeof(header), "requestId: %s", cuid);
    headers = hdhttpHeaderAppend(headers, header);
    if (cuid) {
        hdfree(cuid);
        cuid = NULL;
    }

    // Add the sdkKey header
    HDSPRINTF(header, sizeof(header), "sdkKey: %s", sdkKey);
    headers = hdhttpHeaderAppend(headers, header);

    // Add time headers
    char* date_str = getCurrentDate();
    if (date_str == NULL) {
        hdhttpHeaderFree(headers);
        return NULL;
    }
    HDSPRINTF(header, sizeof(header), "date: %s", date_str);
    headers = hdhttpHeaderAppend(headers, header);

    // Compute signatures
    size_t sign_len = body ? strlen(body) + strlen(sdkKey) + strlen(date_str) + 1 : strlen(sdkKey) + strlen(date_str) + 1;
    char* sign_data = (char*)hdmalloc(sign_len);
    if (sign_data == NULL) {
        if (date_str) {
            hdfree(date_str);
            date_str = NULL;
        }
        hdhttpHeaderFree(headers);
        return NULL;
    }
    if (body) {
        HDSPRINTF(sign_data, sign_len, "%s%s%s", body, sdkKey, date_str);
    }
    else {
        HDSPRINTF(sign_data, sign_len, "%s%s", sdkKey, date_str);
    }

    printf("sign_data:%s\n", sign_data);
    uint8_t sign[33] = { 0 };
    hdhmacmd5Hex(sign_data, strlen(sign_data), sdkSecret, strlen(sdkSecret), sign);
    printf("sign:%s\n", sign);

    // Resource cleanup
     if (date_str) {
        hdfree(date_str);
        date_str = NULL;
    }
    if (sign_data) {
        hdfree(sign_data);
        sign_data = NULL;
    }

    // Add a signature header
    HDSPRINTF(header, sizeof(header), "sign: %s", sign);
    headers = hdhttpHeaderAppend(headers, header);
    return headers;
}

char* httpRequest(const char* method, const char* url, const char* body,
    const char* file_path, int timeout_ms) {
    httpHeaderlist* headers = NULL;
    char* result = NULL;

    // Handle different types of requests
    uint32_t bodySize = 0;
    // File upload processing
    if (file_path) {
        headers = signHeader(NULL, GetSdkKey(), GetSdkSecret());
    }
    else if (body && strcmp(method, "POST") == 0) { // Normal POST requests
        bodySize = strlen(body);
        headers = signHeader(body, GetSdkKey(), GetSdkSecret());
        // Set Content-Type
        if (headers) {
            headers = hdhttpHeaderAppend(headers, "content-type: application/json");
        }
    }
    else { // GET request
        headers = signHeader(NULL, GetSdkKey(), GetSdkSecret());
    }

    // Execute the request
    result = hdhttpRequest(method, url, headers, body, bodySize, file_path, timeout_ms);

    // clean
    if (NULL != headers) {
        hdhttpHeaderFree(headers);
    }

    if (!result) {
        result = strdup("{\"message\":\"failed\",\"data\":\"Unknown error\"}");
    }

    return result;
}

char* deviceList(HttpApi* api) {
    if (!api || !api->devApiUrl) {
        return strdup("{\"message\":\"failed\",\"data\":\"Invalid API object\"}");
    }

    size_t url_len = strlen(api->devApiUrl) + 6; // "/list/" + null terminator
    char* url = (char*)hdmalloc(url_len);
    if (!url) {
        return strdup("{\"message\":\"failed\",\"data\":\"Memory allocation error\"}");
    }

    HDSPRINTF(url, url_len, "%slist/", api->devApiUrl);
    char* result = httpRequest("GET", url, NULL, NULL, 0);
    hdfree(url);
    return result;
}

char* device(HttpApi* api, const char* body) {
    if (!api || !api->devApiUrl) {
        return strdup("{\"message\":\"failed\",\"data\":\"Invalid API object\"}");
    }
    return httpRequest("POST", api->devApiUrl, body, NULL, 0);
}

char* program(HttpApi* api, const char* body) {
    if (!api || !api->devApiUrl) {
        return strdup("{\"message\":\"failed\",\"data\":\"Invalid API object\"}");
    }
    return httpRequest("POST", api->programApiUrl, body, NULL, 60000); // 60 seconds timeout
}

char* uploadFile(HttpApi* api, const char* filePath) {
    if (!api || !api->devApiUrl) {
        return strdup("{\"message\":\"failed\",\"data\":\"Invalid API object\"}");
    }

    // Check if the file exists
    FILE* file = fopen(filePath, "rb");
    if (!file) {
        cJSON* error = cJSON_CreateObject();
        cJSON_AddStringToObject(error, "message", "failed");
        cJSON_AddStringToObject(error, "data", "File not found");
        char* result = cJSON_PrintUnformatted(error);
        cJSON_Delete(error);
        return result;
    }
    fclose(file);
    return httpRequest("POST", api->fileApiUrl, NULL, filePath, 0);
}

