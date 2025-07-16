package cn.huidu.device.api.sdk.data.program.area.content;

import cn.huidu.device.api.sdk.data.program.other.ClockParam.FmtStyle;
import cn.huidu.device.api.sdk.data.program.other.ClockParam.FormatColor;
import cn.huidu.device.api.sdk.data.program.other.ClockParam.StringColor;
import cn.huidu.device.api.sdk.data.program.other.ClockParam;
import cn.huidu.device.api.sdk.data.program.other.Font;

public class DigitalClockNode extends ContentNode {
    private String timezone;
    private String timeOffset;
    private Font font;
    private StringColor title;
    private FormatColor date;
    private FormatColor week;
    private FormatColor time;
    private FormatColor ampm;
    private int spacing;
    private boolean multiLine;
    private boolean enabled12H;
    private boolean swapWeekAndDay;
       
    public DigitalClockNode() {
        this.setType("digitalClock");
        multiLine = true;
        title = new ClockParam().new StringColor();
        title.display = "0";
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
        this.ampm = other.ampm;
        this.spacing = other.spacing;
        this.multiLine = other.multiLine;
        this.enabled12H = other.enabled12H;
        this.swapWeekAndDay = other.swapWeekAndDay;
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

    public FormatColor getAmpm() {
        return ampm;
    }

    public void setAmpm(FormatColor ampm) {
        this.ampm = ampm;
    }

    public Boolean getEnabled12H() {
        return enabled12H;
    }

    public void setEnabled12H(Boolean enabled12h) {
        enabled12H = enabled12h;
    }

    public Boolean getMultiLine() {
        return multiLine;
    }

    public void setMultiLine(Boolean multiLine) {
        this.multiLine = multiLine;
    }

    public FmtStyle getClockFmtStyle() {
        FmtStyle style = new ClockParam().new FmtStyle();
        if (swapWeekAndDay) {
            style.swap = "1";
        }
        if (spacing > 0) {
            style.space = Integer.toString(spacing);
        }

        return style;
    }

    public void setSwapWeekAndDay(Boolean swapWeekAndDay) {
        this.swapWeekAndDay = swapWeekAndDay;
    }

    public void setSpacing(int spacing) {
        this.spacing = spacing;
    }
}
