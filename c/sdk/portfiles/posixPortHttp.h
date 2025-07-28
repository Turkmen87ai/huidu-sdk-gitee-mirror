/**
 * @file   posixPortHttp.h
 * @brief  Huidu SDK的http模块
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

// 回调函数用于接收响应数据
typedef struct {
    char  *data;
    size_t size;
} ResponseData;

httpHeaderlist *hdhttpHeaderAppendNodup(httpHeaderlist *list, char *data);

httpHeaderlist *hdhttpHeaderAppend(httpHeaderlist *list, const char *data);

httpHeaderlist *hdhttpHeaderDuplicate(httpHeaderlist *inlist);

void hdhttpHeaderFree(httpHeaderlist *list);

/**
 * 发起HTTP请求
 *
 * @param method 请求方法，如"GET"、"POST"等
 * @param url 请求的URL地址
 * @param header 请求的头信息列表，用于传递额外的请求参数
 * @param body 请求体内容，通常用于POST请求传递数据
 * @param bodySize 请求体的大小，单位为字节
 * @param filePath 若需将响应内容保存到文件，则指定文件路径；否则传入NULL
 * @param timeout_ms 请求的超时时间，单位为毫秒
 *
 * @return 返回指向动态分配的内存区域的指针，该内存区域包含响应内容；
 *         如果请求失败或解析响应出错，则返回NULL。
 *         调用者负责释放返回的内存区域。
 *
 * 此函数根据提供的参数构建HTTP请求，并接收响应。
 * 如果filePath参数被提供，响应内容将被保存到指定的文件中。
 * 否则，响应内容将被读取到内存中，并在函数返回后需要由调用者释放。
 */
char *hdhttpRequest(const char *method, const char *url, const httpHeaderlist *header, const char *body, uint32_t bodySize, const char *filePath, int timeoutMs);

#endif // __POSIX_PORT_HTTP_H__