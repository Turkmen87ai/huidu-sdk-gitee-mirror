package cn.huidu.device.api.sdk.data.program.area.content;

import cn.huidu.device.api.sdk.data.program.other.ClockParam.FormatColor;
import cn.huidu.device.api.sdk.data.program.other.ClockParam.StringColor;
import cn.huidu.device.api.sdk.data.program.other.Font;

public class DigitalClockNode extends ContentNode {
    private String timezone;
    private String timeOffset;
    private Font font;
    private StringColor title;
    private FormatColor date;
    private FormatColor week;
    private FormatColor time;

    public DigitalClockNode() {
        this.setType("digitalClock");
    }

    public DigitalClockNode(DigitalClockNode other) {
        this();
        this.timezone = other.timezone;
        this.timeOffset = other.timezone;
        this.font = other.font;
        this.title = other.title;
        this.date = other.date;
        this.week = other.week;
        this.time = other.time;
    }

    public String getTimezone() {
        return timezone;
    }

    public void setTimezone(String timezone) {
        this.timezone = timezone;
    }

    public String getTimeOffset() {
        return timeOffset;
    }

    public void setTimeOffset(String timeOffset) {
        this.timeOffset = timeOffset;
    }

    public Font getFont() {
        return font;
    }

    public void setFont(Font font) {
        this.font = font;
    }

    public StringColor getTitle() {
        return title;
    }

    public void setTitle(StringColor title) {
        this.title = title;
    }

    public FormatColor getDate() {
        return date;
    }

    public void setDate(FormatColor date) {
        this.date = date;
    }

    public FormatColor getWeek() {
        return week;
    }

    public void setWeek(FormatColor week) {
        this.week = week;
    }

    public FormatColor getTime() {
        return time;
    }

    public void setTime(FormatColor time) {
        this.time = time;
    }
}
