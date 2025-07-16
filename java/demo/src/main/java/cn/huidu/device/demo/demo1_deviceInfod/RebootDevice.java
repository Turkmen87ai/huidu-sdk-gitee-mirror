package cn.huidu.device.demo.demo1_deviceInfod;

import cn.huidu.device.sdk.Device;

public class RebootDevice {
    public static void main(String[] args) {
        // 替换成你自己的参数
        // String host = "${YourHost}";
        // String sdkKey = "${YourSdkKey}";
        // String sdkSecret = "${YourSdkSecret}";
        // Config.InitSdk(host, sdkKey, sdkSecret);

        // 1. 实例化设备接口对象
        Device device = new Device();
        // 2. 调用接口，重启设备
        String jsonResult = device.device(new String[] { "C16-D21-015BD" }, "rebootDevice");
        // 3. 打印结果
        System.out.println(jsonResult);

    }

}
