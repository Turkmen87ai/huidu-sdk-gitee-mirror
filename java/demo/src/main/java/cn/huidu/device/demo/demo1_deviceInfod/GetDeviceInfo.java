package cn.huidu.device.demo.demo1_deviceInfod;

import cn.huidu.device.sdk.Device;

public class GetDeviceInfo {
    public static void main(String[] args) {
        // 替换成你自己的参数
        // String host = "${YourHost}";
        // String sdkKey = "${YourSdkKey}";
        // String sdkSecret = "${YourSdkSecret}";
        // Config.InitSdk(host, sdkKey, sdkSecret);

        // 1. 实例化设备接口对象
        Device device = new Device();
        // 2. 调用接口获取指定设备（"C16-D21-015BD",需要替换成自己的设备id）的信息（设备属性）
        String jsonResult = device.getDeviceProperty("");
        // 3. 打印结果
        System.out.println(jsonResult);
    }

}
