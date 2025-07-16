package cn.huidu.device.api.demo.demo5_dynamicContent;

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
        // 恢复到最初状态
        Map<String, String> keyValues = new HashMap<String, String>() {
            {
                put("temperature", "0");
                put("parkingSpace", "0");
            }
        };
        String jsonResult = pushStatusTask.PushStatus("", keyValues);
        System.out.println(jsonResult);

        try {
            Thread.sleep(3000);
        } catch (Exception e) {
        }

        keyValues = new HashMap<String, String>() {
                {
                    put("temperature", "25");
                    put("parkingSpace", "666");
                }
        };
        jsonResult = pushStatusTask.PushStatus("", keyValues);
        System.out.println(jsonResult);


        // 设置当前值
        for (int count = 6666; count >= 0; count--) {
            jsonResult = pushStatusTask.PushStatus("", "parkingSpace", String.valueOf(count));
            System.out.println(jsonResult);

            try {
                Thread.sleep(100);
            } catch (Exception e) {
            }

            if (count % 100 == 0) {
                // 更新温度
                jsonResult = pushStatusTask.PushStatus("", "temperature", String.valueOf(25 + (6 - count / 100)));
                System.out.println(jsonResult);
            }
            
        }
    }

}
