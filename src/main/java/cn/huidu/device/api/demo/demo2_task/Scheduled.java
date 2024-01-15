package cn.huidu.device.api.demo.demo2_task;

import java.util.HashMap;
import java.util.Map;

import cn.huidu.device.api.sdk.data.task.ScheduledTaskInfo;
import cn.huidu.device.api.sdk.deviceTask.ScheduledTask;

public class Scheduled {
    public static void main(String[] args) {
        // 替换成你自己的参数
        // String host = "${YourHost}";
        // String sdkKey = "${YourSdkKey}";
        // String sdkSecret = "${YourSdkSecret}";
        // Config.InitSdk(host, sdkKey, sdkSecret);

        // 1. 实例化任务接口对象 
        ScheduledTask scheduledTask = new ScheduledTask();

        Map<String, ScheduledTaskInfo[]> taskInfos = new HashMap<>();

        ScheduledTaskInfo taskInfo = new ScheduledTaskInfo();
        taskInfo.setTimeRange("06:00:00~19:00:00");
        taskInfos.put("screen", new ScheduledTaskInfo[] {taskInfo});
        // 2. 调用接口
        
        // 切换南区域为1
        String jsonResult = scheduledTask.setScheduledTask("", taskInfos);
        System.out.println(jsonResult);
    }

}
