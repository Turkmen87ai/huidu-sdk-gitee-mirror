package cn.huidu.device.api.sdk.data.task;

public class ScheduledTaskInfo {
    private Boolean enable;
    private String begin;
    private String end;
    private String value;

    public ScheduledTaskInfo() {
    }

    public ScheduledTaskInfo(Boolean enable, String begin, String end, String value) {
        this.enable = enable;
        this.begin = begin;
        this.end = end;
        this.value = value;
    }

    protected ScheduledTaskInfo(ScheduledTaskInfo other) {
        this(other.enable, other.begin, other.end, other.value);
    }
}

