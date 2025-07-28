#include "Device.h"

Device* createDevice() {
    Device* dev = (Device*)hdmalloc(sizeof(Device));
    if (!dev) {
		return NULL;
	}
    dev->baseClient = createBaseClient();
    if (!dev->baseClient) {
        hdfree(dev);
        return NULL;
    }

    return dev;
}

Device* createDeviceWithHost(const char* hostUrl) {
    Device* dev = (Device*)hdmalloc(sizeof(Device));
    if (dev) {
        dev->baseClient = createWithHostBaseClient(hostUrl);
    }
    return dev;
}

void destroyDevice(Device* dev) {
    if (!dev) {
        return;
    }
    if (dev->baseClient) {
        destroyBaseClient(dev->baseClient);
    }
    hdfree(dev);
}

char* getOnlineDevices(Device* dev) {
    if (!dev || !dev->baseClient) {
        return NULL;
    }
    return getDeviceBaseClient(dev->baseClient);
}

char* setDeviceName(Device* dev, const char* id, const char* name) {
    if (!dev || !dev->baseClient || !id || !name) {
        return NULL;
    }

    cJSON* properties = cJSON_CreateObject();
    cJSON_AddStringToObject(properties, "name", name);

    char* propsStr = cJSON_PrintUnformatted(properties);
    cJSON_Delete(properties);

    const char* ids[] = { id };
    char* result = deviceBaseClient(dev->baseClient, ids, 1, "setDeviceProperty", propsStr);

    hdfree(propsStr);
    return result;
}

char* setScreenSize(Device* dev, const char* id, int width, int height) {
    if (!dev || !dev->baseClient || !id) {
        return NULL;
    }

    cJSON* properties = cJSON_CreateObject();
    cJSON_AddNumberToObject(properties, "screen.width", width);
    cJSON_AddNumberToObject(properties, "screen.height", height);

    char* propsStr = cJSON_PrintUnformatted(properties);
    cJSON_Delete(properties);

    const char* ids[] = { id };
    char* result = deviceBaseClient(dev->baseClient, ids, 1, "setDeviceProperty", propsStr);

    hdfree(propsStr);
    return result;
}

char* getDeviceProperty(Device* dev, const char** ids, int idCount,
    const char** properties, int propCount) {
    if (!dev || !dev->baseClient || !ids || idCount <= 0) {
        return NULL;
    }

    cJSON* propArray = NULL;
    if (properties && propCount > 0) {
        propArray = cJSON_CreateArray();
        for (int i = 0; i < propCount; i++) {
            cJSON_AddItemToArray(propArray, cJSON_CreateString(properties[i]));
        }
    }

    char* propsStr = propArray ? cJSON_PrintUnformatted(propArray) : NULL;
    if (propArray) {
        cJSON_Delete(propArray);
    }
    char* result = deviceBaseClient(dev->baseClient, ids, idCount, "getDeviceProperty", propsStr);

    if (propsStr) {
        hdfree(propsStr);
    }
    return result;
}

char* getDevicePropertySingle(Device* dev, const char* id, const char* property) {
    if (!id) return NULL;

    const char* ids[] = { id };
    const char* properties[] = { property };
    return getDeviceProperty(dev, ids, 1, properties, 1);
}

char* setDeviceProperty(Device* dev, const char** ids, int idCount,
    const char* key, const char* value) {
    if (!dev || !dev->baseClient || !ids || idCount <= 0 || !key || !value) {
		return NULL;
	}

    cJSON* properties = cJSON_CreateObject();
    cJSON_AddStringToObject(properties, key, value);

    char* propsStr = cJSON_PrintUnformatted(properties);
    cJSON_Delete(properties);

    char* result = deviceBaseClient(dev->baseClient, ids, idCount, "setDeviceProperty", propsStr);

    hdfree(propsStr);
    return result;
}

char* setDeviceProperties(Device* dev, const char** ids, int idCount,
    cJSON* properties) {
    if (!dev || !dev->baseClient || !ids || idCount <= 0 || !properties) {
        return NULL;
    }
    char* propsStr = cJSON_PrintUnformatted(properties);
    char* result = deviceBaseClient(dev->baseClient, ids, idCount, "setDeviceProperty", propsStr);

    hdfree(propsStr);
    return result;
}

char* getDeviceStatus(Device* dev, const char** ids, int idCount,
    const char** keys, int keyCount) {
    if (!dev || !dev->baseClient || !ids || idCount <= 0) {
        return NULL;
    }

    cJSON* keyArray = NULL;
    if (keys && keyCount > 0) {
        keyArray = cJSON_CreateArray();
        for (int i = 0; i < keyCount; i++) {
            cJSON_AddItemToArray(keyArray, cJSON_CreateString(keys[i]));
        }
    }

    char* keysStr = keyArray ? cJSON_PrintUnformatted(keyArray) : NULL;
    if (keyArray) {
        cJSON_Delete(keyArray);
    }
    char* result = deviceBaseClient(dev->baseClient, ids, idCount, "getDeviceStatus", keysStr);

    if (keysStr) {
        hdfree(keysStr);
    }
    return result;
}

char* getDeviceStatusSingle(Device* dev, const char* id) {
    if (!id) {
        return NULL;
    }
    const char* ids[] = { id };
    return getDeviceStatus(dev, ids, 1, NULL, 0);
}

