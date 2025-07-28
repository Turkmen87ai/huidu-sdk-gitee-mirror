#include "posixPortHttp.h"
#include "curl/curl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t        realsize = size * nmemb;
    ResponseData *mem = (ResponseData *)userp;

    char *ptr = hdrealloc(mem->data, mem->size + realsize + 1);
    if (!ptr)
        return 0;

    mem->data = ptr;
    memcpy(&(mem->data[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->data[mem->size] = 0;

    return realsize;
}

/* returns last node in linked list */
static httpHeaderlist *hdhttpHeaderGetLast(httpHeaderlist *list) {
    httpHeaderlist *item;

    /* if caller passed us a NULL, return now */
    if (!list)
        return NULL;

    /* loop through to find the last item */
    item = list;
    while (item->next) {
        item = item->next;
    }
    return item;
}

/*
 * Curl_slist_append_nodup() appends a string to the linked list. Rather than
 * copying the string in dynamic storage, it takes its ownership. The string
 * should have been malloc()ated. Curl_slist_append_nodup always returns
 * the address of the first record, so that you can use this function as an
 * initialization function as well as an append function.
 * If an error occurs, NULL is returned and the string argument is NOT
 * released.
 */
httpHeaderlist *hdhttpHeaderAppendNodup(httpHeaderlist *list, char *data) {
    httpHeaderlist *last;
    httpHeaderlist *new_item;

    new_item = hdmalloc(sizeof(httpHeaderlist));
    if (!new_item)
        return NULL;

    new_item->next = NULL;
    new_item->data = data;

    /* if this is the first item, then new_item *is* the list */
    if (!list)
        return new_item;

    last = hdhttpHeaderGetLast(list);
    last->next = new_item;
    return list;
}

/*
 * curl_slist_append() appends a string to the linked list. It always returns
 * the address of the first record, so that you can use this function as an
 * initialization function as well as an append function. If you find this
 * bothersome, then simply create a separate _init function and call it
 * appropriately from within the program.
 */
httpHeaderlist *hdhttpHeaderAppend(httpHeaderlist *list, const char *data) {
    char *dupdata = strdup(data);

    if (!dupdata)
        return NULL;

    list = hdhttpHeaderAppendNodup(list, dupdata);
    if (!list)
        hdfree(dupdata);

    return list;
}

/*
 * Curl_slist_duplicate() duplicates a linked list. It always returns the
 * address of the first record of the cloned list or NULL in case of an
 * error (or if the input list was NULL).
 */
httpHeaderlist *hdhttpHeaderDuplicate(httpHeaderlist *inlist) {
    httpHeaderlist *outlist = NULL;
    httpHeaderlist *tmp;

    while (inlist) {
        tmp = hdhttpHeaderAppend(outlist, inlist->data);

        if (!tmp) {
            hdhttpHeaderFree(outlist);
            return NULL;
        }

        outlist = tmp;
        inlist = inlist->next;
    }
    return outlist;
}

/* be nice and clean up resources */
void hdhttpHeaderFree(httpHeaderlist *list) {
    httpHeaderlist *next;
    httpHeaderlist *item;

    if (!list)
        return;

    item = list;
    do {
        next = item->next;
        hdfree(item->data);
        hdfree(item);
        item = next;
    } while (next);
}

char *hdhttpRequest(const char *method, const char *url, const httpHeaderlist *header, const char *body, uint32_t bodySize, const char *filePath, int timeoutMs) {
    ResponseData          response_data = {0};
    struct curl_httppost *post = NULL;
    struct curl_httppost *last = NULL;
    struct curl_slist    *headers = NULL;
    char                 *result = NULL;
    char                  error_buf[CURL_ERROR_SIZE] = {0};

    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();
    if (!curl) {
        return strdup("{\"message\":\"failed\",\"data\":\"CURL init error\"}");
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);                      // 设置URL
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, error_buf);        // 设置错误缓冲区
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback); // 设置响应回调
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response_data);

    // 设置请求方法
    if (strcmp(method, "POST") == 0) {
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
    } else {
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    }

    // 处理不同类型的请求
    // 文件上传处理
    if (filePath) {
        curl_formadd(&post, &last, CURLFORM_COPYNAME, "file", CURLFORM_FILE, filePath, CURLFORM_END);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
    }
    // 普通POST请求
    else if (body && strcmp(method, "POST") == 0) {
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, bodySize);
    }

    // 设置超时
    if (timeoutMs > 0) {
        curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, (long)timeoutMs);
    }

    // 添加头部信息
    const httpHeaderlist *pHeader = header;
    while (NULL != pHeader) {
        headers = curl_slist_append(headers, pHeader->data);
        pHeader = pHeader->next;
    }

    // 设置请求头
    if (headers) {
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    }

    // 执行请求
    CURLcode res = curl_easy_perform(curl);

    // 检查错误
    if ((res == CURLE_OK) && (response_data.data)) {
        result = strdup(response_data.data);
    }

    // 清理
    if (response_data.data)
        hdfree(response_data.data);
    if (post)
        curl_formfree(post);
    if (headers)
        curl_slist_free_all(headers);
    if (curl)
        curl_easy_cleanup(curl);
    curl_global_cleanup();

    return result;
}
