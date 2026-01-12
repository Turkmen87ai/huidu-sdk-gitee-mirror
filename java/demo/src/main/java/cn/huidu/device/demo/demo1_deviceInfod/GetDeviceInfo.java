package cn.huidu.device.demo.demo1_deviceInfod;

import cn.huidu.device.sdk.Device;

public class GetDeviceInfo {
    public static void main(String[] args) {
        // Replace with your own parameters
        // String host = "${YourHost}";
        // String sdkKey = "${YourSdkKey}";
        // String sdkSecret = "${YourSdkSecret}";
        // Config.InitSdk(host, sdkKey, sdkSecret);

        // 1. Instantiate device interface object
        Device device = new Device();
        // 2. Call interface to get information (device properties) for specified device ("C16-D21-015BD", need to replace with your own device id)
        String jsonResult = device.getDeviceProperty("");
        // 3. Print result
        System.out.println(jsonResult);
    }

}
