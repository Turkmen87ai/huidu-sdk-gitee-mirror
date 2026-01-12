/**
 * @file   posixPortHttp.h
 * @brief  Huidu SDK HTTP module
 * @author taixi
 * @date   2025/07/22
 */

#ifndef __POSIX_PORT_HTTP_H__
#define __POSIX_PORT_HTTP_H__

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "posixPortMemory.h"

typedef struct _httpHeaderlist {
    char                   *data;
    struct _httpHeaderlist *next;
} httpHeaderlist;

// Callback function for receiving response data
typedef struct {
    char  *data;
    size_t size;
} ResponseData;

httpHeaderlist *hdhttpHeaderAppendNodup(httpHeaderlist *list, char *data);

httpHeaderlist *hdhttpHeaderAppend(httpHeaderlist *list, const char *data);

httpHeaderlist *hdhttpHeaderDuplicate(httpHeaderlist *inlist);

void hdhttpHeaderFree(httpHeaderlist *list);

/**
 * Initiate HTTP request
 *
 * @param method Request method, such as "GET", "POST", etc.
 * @param url Request URL address
 * @param header Request header list for passing additional request parameters
 * @param body Request body content, usually used for POST requests to pass data
 * @param bodySize Request body size in bytes
 * @param filePath If response content needs to be saved to a file, specify the file path; otherwise pass NULL
 * @param timeout_ms Request timeout in milliseconds
 *
 * @return Returns a pointer to a dynamically allocated memory region containing the response content;
 *         Returns NULL if the request fails or response parsing fails.
 *         The caller is responsible for freeing the returned memory region.
 *
 * This function constructs an HTTP request based on the provided parameters and receives the response.
 * If the filePath parameter is provided, the response content will be saved to the specified file.
 * Otherwise, the response content will be read into memory and needs to be freed by the caller after the function returns.
 */
char *hdhttpRequest(const char *method, const char *url, const httpHeaderlist *header, const char *body, uint32_t bodySize, const char *filePath, int timeoutMs);

#endif // __POSIX_PORT_HTTP_H__