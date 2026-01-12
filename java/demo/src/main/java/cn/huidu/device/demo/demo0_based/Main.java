package cn.huidu.device.demo.demo0_based;

import cn.huidu.device.sdk.Device;

public class Main {
    public static void main(String[] args) {
        // Replace with your own parameters
        // String host = "${YourHost}";
        // String sdkKey = "${YourSdkKey}";
        // String sdkSecret = "${YourSdkSecret}";
        // Config.InitSdk(host, sdkKey, sdkSecret);

        // 1. Instantiate device interface object
        Device device = new Device();
        // 2. Call interface to get online devices
        String jsonResult = device.getOnlineDevices();
        // 3. Print result
        System.out.println(jsonResult);
    }
}
