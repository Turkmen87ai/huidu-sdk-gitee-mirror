package cn.huidu.device.sdk.deviceTask;

import java.util.Map;

import cn.huidu.device.sdk.common.BaseClient;
import cn.huidu.device.sdk.data.task.ScheduledTaskInfo;

public class ScheduledTask extends BaseClient {

    public String getScheduledTask(String id) {
        return getScheduledTask(new String[] { id }, null);
    }

    public String getScheduledTask(String[] id, String[] scheduledTask) {
        return device(id, "getScheduledTask", scheduledTask);
    }

    public String setScheduledTask(String id, Map<String, ScheduledTaskInfo[]> scheduledTaskInfos) {
        return setScheduledTask(new String[] { id }, scheduledTaskInfos);
    }

    public String setScheduledTask(String[] id, Map<String, ScheduledTaskInfo[]> scheduledTaskInfos) {
        return device(id, "setScheduledTask", scheduledTaskInfos);
    }
}