package cn.huidu.device.api.sdk.data.task;

public class PeriodicTaskInfo {
    private String url;
    private String rege;
    private int interval;

    public PeriodicTaskInfo() {
    }

    public PeriodicTaskInfo(String url, String rege, int interval) {
        this.url = url;
        this.rege = rege;
        this.interval = interval;
    }

    protected PeriodicTaskInfo(PeriodicTaskInfo other) {
        this(other.url, other.rege, other.interval);
    }

    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
    }

    public String getRege() {
        return rege;
    }

    public void setRege(String rege) {
        this.rege = rege;
    }

    public int getInterval() {
        return interval;
    }

    public void setInterval(int interval) {
        this.interval = interval;
    }
}
