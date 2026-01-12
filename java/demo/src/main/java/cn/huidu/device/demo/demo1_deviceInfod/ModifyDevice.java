package cn.huidu.device.demo.demo1_deviceInfod;

import cn.huidu.device.sdk.Device;

public class ModifyDevice {
    public static void main(String[] args) {
        // Replace with your own parameters
        // String host = "${YourHost}";
        // String sdkKey = "${YourSdkKey}";
        // String sdkSecret = "${YourSdkSecret}";
        // Config.InitSdk(host, sdkKey, sdkSecret);

        // 1. Instantiate device interface object
        Device device = new Device();
        // 2. Call interface to set name for specified device ("C16-D21-015BD", need to replace with your own device id)
        String jsonResult = device.setDeviceName("C16-D21-015BD", "coffee");
        // 3. Print result
        System.out.println(jsonResult);

        // 4. Call interface to get name for specified device ("C16-D21-015BD", need to replace with your own device id)
        jsonResult = device.getDeviceProperty("C16-D21-015BD", "name");
        // 5. Print result
        System.out.println(jsonResult);
    }

}
