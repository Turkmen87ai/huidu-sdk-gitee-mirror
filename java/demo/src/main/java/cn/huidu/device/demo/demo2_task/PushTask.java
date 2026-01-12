package cn.huidu.device.demo.demo2_task;

import java.util.HashMap;
import java.util.Map;

import cn.huidu.device.sdk.deviceTask.PushStatusTask;

public class PushTask {
    public static void main(String[] args) {
        // Replace with your own parameters
        // String host = "${YourHost}";
        // String sdkKey = "${YourSdkKey}";
        // String sdkSecret = "${YourSdkSecret}";
        // Config.InitSdk(host, sdkKey, sdkSecret);

        // 1. Instantiate task interface object
        PushStatusTask pushStatusTask = new PushStatusTask();

        // 2. Call interface
        // Switch four areas to 0
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

        // Switch east area to 2
        jsonResult = pushStatusTask.PushStatus("", "东", "2");
        System.out.println(jsonResult);

        try {
            Thread.sleep(3000);
        } catch (Exception e) {

        }

        // Switch south area to 1
        jsonResult = pushStatusTask.PushStatus("", "南", "1");
        System.out.println(jsonResult);
    }

}
