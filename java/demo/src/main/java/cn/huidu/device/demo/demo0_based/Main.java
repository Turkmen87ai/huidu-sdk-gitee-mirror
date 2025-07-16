package cn.huidu.device.demo.demo0_based;

import cn.huidu.device.sdk.Device;

public class Main {
    public static void main(String[] args) {
        // 替换成你自己的参数
        // String host = "${YourHost}";
        // String sdkKey = "${YourSdkKey}";
        // String sdkSecret = "${YourSdkSecret}";
        // Config.InitSdk(host, sdkKey, sdkSecret);

        // 1. 实例化设备接口对象
        Device device = new Device();
        // 2. 调用接口获取在线设备
        String jsonResult = device.getOnlineDevices();
        // 3. 打印结果
        System.out.println(jsonResult);
    }
}
