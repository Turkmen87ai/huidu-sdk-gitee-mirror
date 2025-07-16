package cn.huidu.device.api.sdk.data.program.other;

import java.time.LocalDate;
import java.time.LocalTime;
import java.util.ArrayList;
import java.util.List;
import com.alibaba.fastjson.annotation.JSONField;

public class PlayControl {

    public Date[] date;
    public Time[] time;
    public Week week;

    public PlayControl() {
        this.date = new Date[0];
        this.time = new Time[0];
        this.week = new Week();
    }
    
    public PlayControl(PlayControl other) {
        this.date = other.date;
        this.time = other.time;
        this.week = other.week;
    }

    public class Date {
        @JSONField(format = "yyyy-MM-dd")
        public LocalDate start;

        @JSONField(format = "yyyy-MM-dd")
        public LocalDate end;
    }
    
    public class Time {
        @JSONField(format = "HH:mm:ss")
        public LocalTime start;

        @JSONField(format = "HH:mm:ss")
        public LocalTime end;
    }
    
    public class Week {
        private Weekday[] enable;

        public Week() {
        }
        
        public Week(Week other) {
            enable = other.enable;
        }

        @JSONField(serialize = false)
        public Weekday[] getWeekday() {
            return enable;
        }

        @JSONField(deserialize = false)
        public void setWeekday(Weekday[] weekday) {
            this.enable = weekday;
        }

        public String getEnable() {
            List<String> list = new ArrayList<String>();
            for (Weekday value : enable) {
                list.add(value.toString());
            }
            return String.join(",", list);
        }

        public void setEnable(String value) {
            String[] values = value.split(",");
            List<Weekday> list = new ArrayList<Weekday>();
            for (String itemValue : values) {
                try {
                    Weekday weekDay = Weekday.valueOf(itemValue);
                    list.add(weekDay);
                } catch (Exception e) {
                } finally {
                }
                
            }
            enable = list.toArray(new Weekday[list.size()]);
        }
    }
     
    public enum Weekday {
        Mon, Tue, Wed, Thur, Fri, Sat, Sun
    }   
}
