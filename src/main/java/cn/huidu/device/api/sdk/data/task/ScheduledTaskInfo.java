package cn.huidu.device.api.sdk.data.task;

public class ScheduledTaskInfo {

    private String timeRange;   ///< hh:mm:ss~hh:mm:ss
    private String dateRange;   ///< yyyy-MM-DD~yyyy-MM-DD
    private String weekFilter;  ///< Mon,Tue,Wed,Thu,Fri,Sat,Sun
    private String montFilter;  ///< Jan,Feb,Mar,Apr,May,Jun,Jul,Aug,Sep,Oct,Nov,Dec
    private String data;        ///< 字段为字符串，具体的协议对应不同的定义，音量、亮度为0-100，开关类为[true/false]

    public ScheduledTaskInfo() {
    }

    public ScheduledTaskInfo(String data, String timeRange, String dateRange, String weekFilter, String montFilter) {
        this.data = data;
        this.timeRange = timeRange;
        this.dateRange = dateRange;
        this.weekFilter = weekFilter;
        this.montFilter = montFilter;
    }

    protected ScheduledTaskInfo(ScheduledTaskInfo other) {
        this(other.data, other.timeRange, other.dateRange, other.weekFilter, other.montFilter);
    }
}

