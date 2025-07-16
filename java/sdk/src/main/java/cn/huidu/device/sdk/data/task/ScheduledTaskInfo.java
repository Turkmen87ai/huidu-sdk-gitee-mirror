package cn.huidu.device.sdk.data.task;

public class ScheduledTaskInfo {

    private String timeRange; /// < hh:mm:ss~hh:mm:ss
    private String dateRange; /// < yyyy-MM-DD~yyyy-MM-DD
    private String weekFilter; /// < Mon,Tue,Wed,Thu,Fri,Sat,Sun
    private String montFilter; /// < Jan,Feb,Mar,Apr,May,Jun,Jul,Aug,Sep,Oct,Nov,Dec
    private String data; /// < 字段为字符串，具体的协议对应不同的定义，音量、亮度为0-100，开关类为[true/false]

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

    public String getTimeRange() {
        return timeRange;
    }

    public void setTimeRange(String timeRange) {
        this.timeRange = timeRange;
    }

    public String getDateRange() {
        return dateRange;
    }

    public void setDateRange(String dateRange) {
        this.dateRange = dateRange;
    }

    public String getWeekFilter() {
        return weekFilter;
    }

    public void setWeekFilter(String weekFilter) {
        this.weekFilter = weekFilter;
    }

    public String getMontFilter() {
        return montFilter;
    }

    public void setMontFilter(String montFilter) {
        this.montFilter = montFilter;
    }

    public String getData() {
        return data;
    }

    public void setData(String data) {
        this.data = data;
    }

}
