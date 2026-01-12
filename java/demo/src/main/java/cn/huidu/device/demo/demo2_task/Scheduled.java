package cn.huidu.device.demo.demo2_task;

import java.util.HashMap;
import java.util.Map;

import cn.huidu.device.sdk.data.task.ScheduledTaskInfo;
import cn.huidu.device.sdk.deviceTask.ScheduledTask;

public class Scheduled {
    public static void main(String[] args) {
        // Replace with your own parameters
        // String host = "${YourHost}";
        // String sdkKey = "${YourSdkKey}";
        // String sdkSecret = "${YourSdkSecret}";
        // Config.InitSdk(host, sdkKey, sdkSecret);

        // 1. Instantiate task interface object
        ScheduledTask scheduledTask = new ScheduledTask();

        Map<String, ScheduledTaskInfo[]> taskInfos = new HashMap<>();

        ScheduledTaskInfo taskInfo = new ScheduledTaskInfo();
        taskInfo.setTimeRange("06:00:00~19:00:00");
        taskInfos.put("screen", new ScheduledTaskInfo[] { taskInfo });
        // 2. Call interface

        // Switch south area to 1
        String jsonResult = scheduledTask.setScheduledTask("", taskInfos);
        System.out.println(jsonResult);
    }

}
