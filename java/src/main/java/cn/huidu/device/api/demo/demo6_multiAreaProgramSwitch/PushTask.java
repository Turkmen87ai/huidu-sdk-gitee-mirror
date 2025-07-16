package cn.huidu.device.api.demo.demo6_multiAreaProgramSwitch;

import java.util.HashMap;
import java.util.Map;

import cn.huidu.device.api.sdk.deviceTask.PushStatusTask;

public class PushTask {
    public static void main(String[] args) {
        // 替换成你自己的参数
        // String host = "${YourHost}";
        // String sdkKey = "${YourSdkKey}";
        // String sdkSecret = "${YourSdkSecret}";
        // Config.InitSdk(host, sdkKey, sdkSecret);

        // 1. 实例化任务接口对象
        PushStatusTask pushStatusTask = new PushStatusTask();

        // 2. 调用接口
        // 切换四个区域为0
        Map<String, String> keyValues = new HashMap<String, String>() {
            {
                put("东", "0");
                put("西", "0");
                put("南", "0");
                put("北", "0");
            }
        };
        String jsonResult = pushStatusTask.PushStatus("", keyValues);
        System.out.println(jsonResult);

        try {
            Thread.sleep(3000);
        } catch (Exception e) {

        }

        // 切换东区域为2
        jsonResult = pushStatusTask.PushStatus("", "东", "2");
        System.out.println(jsonResult);

        try {
            Thread.sleep(3000);
        } catch (Exception e) {

        }

        // 切换南区域为1
        jsonResult = pushStatusTask.PushStatus("", "南", "1");
        System.out.println(jsonResult);

        try {
            Thread.sleep(3000);
        } catch (Exception e) {

        }

        // 切换四个区域为3
        keyValues = new HashMap<String, String>() {
            {
                put("东", "3");
                put("西", "3");
                put("南", "3");
                put("北", "3");
            }
        };

        jsonResult = pushStatusTask.PushStatus("", keyValues);
        // 3. 打印结果
        System.out.println(jsonResult);
    }

}
