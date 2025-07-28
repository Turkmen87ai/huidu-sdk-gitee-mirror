#include <stdio.h>
#include "Config.h"
#include "BaseClient.h"
#include "Device.h"

int main() {
    // Replace it with your own parameters.
    char* host = "${YourHost}";
    char* sdkKey = "${YourSdkKey}";
    char* sdkSecret = "${YourSdkSecret}";
    InitSdk(host, sdkKey, sdkSecret);

    // 1. Instantiate the device interface object.
    Device* device = createDevice();

    // 2. Obtain device attributes.
    char* jsonResult = getDevicePropertySingle(device, "C16L-D00-A000F", NULL);
    // 2. Set the device name.
    //char* jsonResult = setDeviceName(device, "C16L-D00-A000F", "coffee");
    // 2. Obtain specified attribute name.
    //char* jsonResult = getDevicePropertySingle(device, "C16L-D00-A000F", "name");
    // 2. Obtain device status.
    //char* jsonResult = getDeviceStatusSingle(device, "C16L-D00-A000F");
    // 2. Restart the device.
    //const char* devIds[] = { "C16L-D00-A000F"};
    //char* jsonResult = deviceBaseClient(device->baseClient, devIds, 1, "rebootDevice", NULL);

    // 3. Release resources
    destroyDevice(device);
	destroyConfig();
     
    // 4. Print result
    printf("%s\n", jsonResult);
    system("pause");
}