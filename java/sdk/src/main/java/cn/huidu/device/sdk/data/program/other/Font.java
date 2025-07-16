package cn.huidu.device.sdk.data.program.other;

public class Font {
    private String name;
    private int size;
    private boolean underline;
    private boolean bold;
    private boolean italic;
    private String color;

    public Font() {
        name = "";
        size = 14;
        underline = false;
        bold = false;
        italic = false;
        color = "#ff0000";
    }

    public Font(int size) {
        this();
        this.size = size;
    }

    public Font(int size, String color) {
        this(size);
        this.color = color;
    }

    public Font(int size, String color, boolean bold) {
        this(size, color);
        this.bold = bold;
    }

    public Font(int size, String color, boolean bold, boolean italic, boolean underline, String name) {
        this(size, color, bold);
        this.italic = italic;
        this.underline = underline;
        this.name = name;
    }

    public Font(Font other) {
        this(other.size, other.color, other.bold, other.italic, other.underline, other.name);
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getSize() {
        return size;
    }

    public void setSize(int size) {
        this.size = size;
    }

    public boolean isUnderline() {
        return underline;
    }

    public void setUnderline(boolean underline) {
        this.underline = underline;
    }

    public boolean isBold() {
        return bold;
    }

    public void setBold(boolean bold) {
        this.bold = bold;
    }

    public boolean isItalic() {
        return italic;
    }

    public void setItalic(boolean italic) {
        this.italic = italic;
    }

    public String getColor() {
        return color;
    }

    public void setColor(String color) {
        this.color = color;
    }
}
