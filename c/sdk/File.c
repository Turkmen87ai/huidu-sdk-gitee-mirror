#include "File.h"

FileClient* createFileClient(const char* hostUrl) {
    FileClient* file = (FileClient*)hdmalloc(sizeof(FileClient));
    if (!file) {
        return NULL;
    }
    file->baseClient = createBaseClient(hostUrl);
    if (!file->baseClient) {
        hdfree(file);
        return NULL;
    }

    return file;
}

void freeFileClient(FileClient* file) {
    if (file) {
        destroyBaseClient(file->baseClient);
        hdfree(file);
    }
}

void setHostUrlFileClient(FileClient* file, const char* hostUrl) {
    if (file && file->baseClient) {
        file->baseClient = createWithHostBaseClient(hostUrl);
    }
}

char* uploadFileFileClient(FileClient* file, const char* filePath) {
    if (!file || !file->baseClient || !filePath) {
        return NULL;
    }
    return fileBaseClient(file->baseClient, filePath);
}

