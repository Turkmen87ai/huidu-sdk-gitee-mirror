#include <stdio.h>
#include "Config.h"
#include "Device.h"

int main() {
    // Replace it with your own parameters.
    char* host = "${YourHost}";
    char* sdkKey = "${YourSdkKey}";
    char* sdkSecret = "${YourSdkSecret}";
    InitSdk(host, sdkKey, sdkSecret);

    // 1. Instantiate the device interface object.
    Device* device = createDevice();

    // 2. Call the interface to obtain the online devices.
    char* jsonResult = getOnlineDevices(device);

    // 3. Release resources
    destroyDevice(device);
	destroyConfig();

    // 4. Print result
    printf("%s\n", jsonResult);

    system("pause");
}