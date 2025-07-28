#include "BaseClient.h"

// Concatenate string array
char* joinStrings(const char** array, int count, const char* delimiter) {
    if (!array || count <= 0 || !delimiter) {
		return NULL;
	}
    size_t total_len = 1; // Terminate the null character.
    size_t delim_len = strlen(delimiter);

    // Calculate the total length
    for (int i = 0; i < count; i++) {
        if (!array[i]) return NULL;
        total_len += strlen(array[i]);
        if (i < count - 1) {
			total_len += delim_len;
		}
    }

    char* result = (char*)hdmalloc(total_len);
    if (!result) {
		return NULL;
	}
    char* current = result;
    for (int i = 0; i < count; i++) {
        size_t len = strlen(array[i]);
        memcpy(current, array[i], len);
        current += len;

        if (i < count - 1) {
            memcpy(current, delimiter, delim_len);
            current += delim_len;
        }
    }
    *current = '\0';

    return result;
}

// Determine whether it is a URL (simplified implementation)
bool is_url(const char* str) {
    if (!str) {
        return false;
    }
    // Check for common URL prefixes
    if (strstr(str, "http://") == str || strstr(str, "https://") == str) {
        return true;
    }

    // Use regular expressions for stricter detection
    //regex_t regex;
    //int ret;
    //const char* pattern = "^((https|http)?://)"
    //    "?(([0-9a-z_!~*'().&=+$%-]+: )?[0-9a-z_!~*'().&=+$%-]+@)?"
    //    "(([0-9]{1,3}\\.){3}[0-9]{1,3}"
    //    "|"
    //    "([0-9a-z_!~*'()-]+\\.)*"
    //    "([0-9a-z][0-9a-z-]{0,61})?[0-9a-z]\\."
    //    "[a-z]{2,6})"
    //    "(:[0-9]{1,5})?"
    //    "((/?)|"
    //    "(/[0-9a-z_!~*'().;?:@&=+$,%#-]+)+/?)$";

    //ret = regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE | REG_NOSUB);
    //if (ret) {
    //    return false;
    //}

    //ret = regexec(&regex, str, 0, NULL, 0);
    //regfree(&regex);

    //return ret == 0;
    return false;
}

char* toJsonObject(const char* data) {
    cJSON* json = cJSON_Parse(data);
    if (json) {
        char* result = cJSON_PrintUnformatted(json);
        cJSON_Delete(json);
        return result;
    }

    cJSON* errorJson = cJSON_CreateObject();
    cJSON_AddStringToObject(errorJson, "message", "failed");
    cJSON_AddStringToObject(errorJson, "data", "Invalid JSON response");
    char* result = cJSON_PrintUnformatted(errorJson);
    cJSON_Delete(errorJson);
    return result;
}

BaseClient* createBaseClient() {
    BaseClient* client = (BaseClient*)hdmalloc(sizeof(BaseClient));
    if (!client) {
		return NULL;
	}
    client->httpClient = createHttpApi();
    if (!client->httpClient) {
        hdfree(client);
        return NULL;
    }

    return client;
}

BaseClient* createWithHostBaseClient(const char* hostUrl) {
    BaseClient* client = (BaseClient*)hdmalloc(sizeof(BaseClient));
    if (!client) {
        return NULL;
    }
    client->httpClient = createHttpApiWithHost(hostUrl);
    if (!client->httpClient) {
        hdfree(client);
        return NULL;
    }
    return client;
}

void destroyBaseClient(BaseClient* client) {
    if (!client) {
        return;
    }
    if (client->httpClient) {
        destroyHttpApi(client->httpClient);
    }
    hdfree(client);
}

char* getDeviceBaseClient(BaseClient* client) {
    if (!client || !client->httpClient) {
        return toJsonObject("{\"message\":\"failed\",\"data\":\"Invalid client\"}");
    }

    char* response = deviceList(client->httpClient);
    return response;
}

char* deviceBaseClient(BaseClient* client, const char** devIds, int devIdCount,
    const char* method, const char* data) {
    if (!client || !client->httpClient) {
        return toJsonObject("{\"message\":\"failed\",\"data\":\"Invalid client\"}");
    }

    cJSON* request = cJSON_CreateObject();
    cJSON_AddStringToObject(request, "method", method);

    if (data) {
        cJSON* dataJson = cJSON_Parse(data);
        if (dataJson) {
            cJSON_AddItemToObject(request, "data", dataJson);
        }
        else {
            cJSON_AddStringToObject(request, "data", data);
        }
    }

    if (devIdCount > 0) {
        char* devId = joinStrings((const char**)devIds, devIdCount, ",");
        if (devId) {
            cJSON_AddStringToObject(request, "id", devId);
            hdfree(devId);
        }
    }

    char* requestStr = cJSON_PrintUnformatted(request);
    cJSON_Delete(request);

    char* response = device(client->httpClient, requestStr);
    hdfree(requestStr);

    char* result = toJsonObject(response);
    hdfree(response);
    return result;
}

char* fileBaseClient(BaseClient* client, const char* filePath) {
    if (!client || !client->httpClient || !filePath) {
        return toJsonObject("{\"message\":\"failed\",\"data\":\"Invalid client\"}");
    }

    // 检查文件是否存在
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

    char* response = uploadFile(client->httpClient, filePath);
    char* result = toJsonObject(response);
    hdfree(response);
    return result;
}

cJSON* uploadAndUpdateFiles(BaseClient* bc, ProgramNode** programNodes, int nodeCount) {
    cJSON* retObj = cJSON_CreateObject();
    cJSON_AddStringToObject(retObj, "message", "ok");
    // Collect all documents (deduplicate)
    FileInfo** allFiles = NULL;
    int fileCount = 0;
    int capacity = 0;

    for (int i = 0; i < nodeCount; i++) {
        ProgramNode* pn = programNodes[i];
        if (!pn) {
            continue;
        }

        // Handles files at the AreaNode level
        for (size_t k = 0; k < pn->areaCount; k++) {
            AreaNode* an = pn->areas[k];

            for (size_t n = 0; n < an->itemCount; n++) {
                const char* type = getTypeContentNode(an->items[n].text->base);
                FileInfo* files = NULL;
                int count = 0;
                if (type) {
                    if (strcmp(type, "image") == 0) {
                        files = getFilesInfoImageNode(an->items[n].image, &count);
                    }
                    else if (strcmp(type, "video") == 0) {
                        files = getFilesInfoVideoNode(an->items[n].video, &count);
                    }
                }

                for (int j = 0; j < count; j++) {
                    bool exists = false;
                    for (int k = 0; k < fileCount; k++) {
                        if (strcmp(allFiles[k]->localFile, files[j].localFile) == 0) {
                            exists = true;
                            break;
                        }
                    }
                    if (!exists) {
                        if (fileCount >= capacity) {
                            capacity = capacity ? capacity * 2 : 16;
                            FileInfo** newFiles = (FileInfo**)hdrealloc(allFiles, capacity * sizeof(FileInfo*));
                            if (!newFiles) {
                                // Memory allocation failed handling
                                for (int m = 0; m < fileCount; m++) hdfree(allFiles[m]);
                                hdfree(allFiles);
                                cJSON_AddStringToObject(retObj, "message", "failed");
                                cJSON_AddStringToObject(retObj, "data", "Memory allocation error");
                                return retObj;
                            }
                            allFiles = newFiles;
                        }
                        allFiles[fileCount] = copyFileInfo(&files[j]);
                        fileCount++;
                    }
                }
            }
        }
    }

    // Process file uploads
    bool success = true;
    for (int i = 0; i < fileCount; i++) {
        FileInfo* info = allFiles[i];

        if (is_url(info->localFile) && info->md5 && info->size > 0) {
            info->url = strdup(info->localFile);
            continue;
        }

        char* fileRes = fileBaseClient(bc, info->localFile);
        printf("%s\n", fileRes);
        cJSON* fileJson = cJSON_Parse(fileRes);
        hdfree(fileRes);

        if (!cJSON_HasObjectItem(fileJson, "message") ||
            strcmp(cJSON_GetObjectItem(fileJson, "message")->valuestring, "ok") != 0) {
            cJSON_ReplaceItemInObject(retObj, "data", cJSON_Duplicate(fileJson, 1));
            cJSON_ReplaceItemInObject(retObj, "message", cJSON_CreateString("failed"));
            success = false;
            cJSON_Delete(fileJson);
            break;
        }

        cJSON* dataArr = cJSON_GetObjectItem(fileJson, "data");
        if (!cJSON_IsArray(dataArr) || cJSON_GetArraySize(dataArr) == 0) {
            // Error handling
            success = false;
            cJSON_Delete(fileJson);
            break;
        }

        cJSON* dataObj = cJSON_GetArrayItem(dataArr, 0);
        if (!cJSON_HasObjectItem(dataObj, "message") ||
            strcmp(cJSON_GetObjectItem(dataObj, "message")->valuestring, "ok") != 0) {
            // Error handling
            success = false;
            cJSON_Delete(fileJson);
            break;
        }

        hdfree(info->md5);
        info->md5 = strdup(cJSON_GetObjectItem(dataObj, "md5")->valuestring);
        info->size = atoi(cJSON_GetObjectItem(dataObj, "size")->valuestring);
        hdfree(info->url);
        info->url = strdup(cJSON_GetObjectItem(dataObj, "data")->valuestring);

        cJSON_Delete(fileJson);
    }

    // Update file information
    if (success && fileCount > 0) {
        for (int i = 0; i < nodeCount; i++) {
            ProgramNode* pn = programNodes[i];
            for (size_t j = 0; j < pn->areaCount; j++) {
                AreaNode* area = getAreaProgramNode(pn, j);
                for (size_t n = 0; n < area->itemCount; n++) {
                    const char* type = getTypeContentNode(area->items[n].text->base);
                    if (type) {
                        if (strcmp(type, "image") == 0) {
                            updateFilesInfoImageNode(area->items[n].image, allFiles, fileCount);
                        }
                        else if (strcmp(type, "video") == 0) {
                            updateFilesInfoVideoNode(area->items[n].video, allFiles, fileCount);
                        }
                    }
                }
            }
        }
    }

    // clean
    for (int i = 0; i < fileCount; i++) {
        destroyFileInfo(allFiles[i]);
    }
    hdfree(allFiles);
    return retObj;
}

char* programBaseClient(BaseClient* client, const char** devIds, int devIdCount,
    const char* method, ProgramNode** programNodes, int nodeCount,
    const char* dataEx) {
    if (!client || !client->httpClient) {
        return toJsonObject("{\"message\":\"failed\",\"data\":\"Invalid client\"}");
    }

    // Upload and update files
    cJSON* uploadResult = uploadAndUpdateFiles(client, programNodes, nodeCount);
    const cJSON* message = cJSON_GetObjectItemCaseSensitive(uploadResult, "message");

    if (message && cJSON_IsString(message) && strcmp(message->valuestring, "ok") != 0) {
        char* resultStr = cJSON_PrintUnformatted(uploadResult);
        cJSON_Delete(uploadResult);
        return resultStr;
    }
    cJSON_Delete(uploadResult);

    // Create request JSON
    cJSON* request = cJSON_CreateObject();
    cJSON_AddStringToObject(request, "method", method);

    // Add a program node
    cJSON* programArray = cJSON_CreateArray();
    for (int i = 0; i < nodeCount; i++) {
        cJSON* programJson = toJsonProgramNode(programNodes[i]);
        if (programJson) {
            cJSON_AddItemToArray(programArray, programJson);
        }
    }
    cJSON_AddItemToObject(request, "data", programArray);

    // Add extra data
    if (dataEx) {
        cJSON* dataExJson = cJSON_Parse(dataEx);
        if (dataExJson) {
            cJSON_AddItemToObject(request, "dataEx", dataExJson);
        }
        else {
            cJSON_AddStringToObject(request, "dataEx", dataEx);
        }
    }

    // Add the device ID
    if (devIdCount > 0) {
        char* devId = joinStrings((const char**)devIds, devIdCount, ",");
        if (devId) {
            cJSON_AddStringToObject(request, "id", devId);
            hdfree(devId);
        }
    }

    char* requestStr = cJSON_PrintUnformatted(request);
    cJSON_Delete(request);

    // Send a request
    char* response = program(client->httpClient, requestStr);
    hdfree(requestStr);

    char* result = toJsonObject(response);
    hdfree(response);
    return result;
}

