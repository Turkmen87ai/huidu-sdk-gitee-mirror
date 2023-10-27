package cn.huidu.device.api.sdk.deviceTask;

import cn.huidu.device.api.sdk.common.BaseClient;
import cn.huidu.device.api.sdk.data.task.PeriodicTaskInfo;

public class PeriodicTask extends BaseClient {

    public String getPeriodicTask(String id) {
        return getPeriodicTask(new String[] { id });
    }

    public String getPeriodicTask(String[] id) {
        return device(id, "getPeriodicTask");
    }

    public String setPeriodicTask(String id, PeriodicTaskInfo[] periodicTaskInfos) {
        return setPeriodicTask(new String[] { id }, periodicTaskInfos);
    }

    public String setPeriodicTask(String[] id, PeriodicTaskInfo[] periodicTaskInfos) {
        return device(id, "setPeriodicTask", periodicTaskInfos);
    }
}