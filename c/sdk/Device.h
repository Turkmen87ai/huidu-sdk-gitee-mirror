#ifndef DEVICE_H
#define DEVICE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "BaseClient.h"
#include "posixPortMemory.h"
// Device structure
typedef struct {
    BaseClient* baseClient;
} Device;

// Create device instance.
Device* createDevice();

Device* createDeviceWithHost(const char* hostUrl);

// Release device instance
void destroyDevice(Device* dev);

// Obtain online devices.
char* getOnlineDevices(Device* dev);

// Set the device name.
char* setDeviceName(Device* dev, const char* id, const char* name);

// Set the screen size.
char* setScreenSize(Device* dev, const char* id, int width, int height);

// Obtain device attributes (multiple devices, multiple attributes).
char* getDeviceProperty(Device* dev, const char** ids, int idCount,
    const char** properties, int propCount);

// Obtain device attributes (single device, single attribute)
char* getDevicePropertySingle(Device* dev, const char* id, const char* property);

// Set device attributes (multiple devices, single attribute).
char* setDeviceProperty(Device* dev, const char** ids, int idCount,
    const char* key, const char* value);

// Set device attributes (multiple attributes)
char* setDeviceProperties(Device* dev, const char** ids, int idCount,
    cJSON* properties);

// Obtain device status (multiple devices, multiple keys).
char* getDeviceStatus(Device* dev, const char** ids, int idCount,
    const char** keys, int keyCount);

// Obtain the status of the device (individual device)
char* getDeviceStatusSingle(Device* dev, const char* id);

#endif

