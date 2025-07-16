package cn.huidu.device.api.demo.demo1_deviceInfod;

import cn.huidu.device.api.sdk.Device;

public class ModifyDevice {
    public static void main(String[] args) {
        // 替换成你自己的参数
        // String host = "${YourHost}";
        // String sdkKey = "${YourSdkKey}";
        // String sdkSecret = "${YourSdkSecret}";
        // Config.InitSdk(host, sdkKey, sdkSecret);

        // 1. 实例化设备接口对象
        Device device = new Device();
        // 2. 调用接口设置指定设备（"C16-D21-015BD",需要替换成自己的设备id）的名称
        String jsonResult = device.setDeviceName("C16-D21-015BD", "coffee");
        // 3. 打印结果
        System.out.println(jsonResult);

        // 4. 调用接口获取指定设备（"C16-D21-015BD",需要替换成自己的设备id）的名称
        jsonResult = device.getDeviceProperty("C16-D21-015BD", "name");
        // 5. 打印结果
        System.out.println(jsonResult);
    }

}
