package cn.huidu.device.api.sdk.data.program.other;

public class ClockParam {
    
    public class FormatColor {
        public String display;
        public String format;
        public String color;
        public int size;
    }
    
    public class StringColor {
        public String display;
        public String string;
        public int size;
        public String color;
    }
    
    public class Style {
        public String hourHandColor;
        public String minuteHandColor;
        public String secondHandColor;
        public String hourScaleColor;
        public String minuteScaleColor;
        public String fontName;
        public int fontSize;
    }

    public class FmtStyle {
        public String swap;
		public String space;
	}
}
