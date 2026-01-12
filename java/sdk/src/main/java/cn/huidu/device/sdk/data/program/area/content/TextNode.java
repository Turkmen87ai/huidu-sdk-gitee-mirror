package cn.huidu.device.sdk.data.program.area.content;

import cn.huidu.device.sdk.data.program.other.Effect;
import cn.huidu.device.sdk.data.program.other.Font;

public class TextNode extends ContentNode {
    protected String string;
    protected Boolean multiLine;
    protected Alignment alignment;
    protected VAlignment valignment;
    protected Effect effect;
    protected Font font;

    public TextNode() {
        super();
        setType("text"); // Text content
        multiLine = true;
    }

    public TextNode(String text) {
        this();
        this.string = text;
    }

    public TextNode(TextNode other) {
        super(other);
        this.string = other.string;
        this.multiLine = other.multiLine;
        this.alignment = other.alignment;
        this.valignment = other.valignment;
        this.effect = other.effect;
        this.font = other.font;
    }

    public enum Alignment {
        center("center"), /// < Center alignment
        left("left"), /// < Left alignment
        right("right"); /// < Right alignment

        private final String value;

        public String getValue() {
            return value;
        }

        Alignment(String value) {
            this.value = value;
        }
    }

    public enum VAlignment {
        middle("middle"), /// < Vertical center
        top("top"), /// < Top alignment
        bottom("bottom"); /// < Bottom alignment

        private final String value;

        public String getValue() {
            return value;
        }

        VAlignment(String value) {
            this.value = value;
        }
    }

    public String getString() {
        return string;
    }

    public void setString(String string) {
        this.string = string;
    }

    public Boolean getMultiLine() {
        return multiLine;
    }

    public void setMultiLine(Boolean multiLine) {
        this.multiLine = multiLine;
    }

    public Alignment getAlignment() {
        return alignment;
    }

    public void setAlignment(Alignment alignment) {
        this.alignment = alignment;
    }

    public VAlignment getValignment() {
        return valignment;
    }

    public void setValignment(VAlignment valignment) {
        this.valignment = valignment;
    }

    public Effect getEffect() {
        return effect;
    }

    public void setEffect(Effect effect) {
        this.effect = effect;
    }

    public Font getFont() {
        return font;
    }

    public void setFont(Font font) {
        this.font = font;
    }
}
