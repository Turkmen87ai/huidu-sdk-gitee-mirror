package cn.huidu.device.api.sdk.data.program.area.content;

import cn.huidu.device.api.sdk.data.program.other.Effect;
import cn.huidu.device.api.sdk.data.program.other.Font;

public class DynamicNode extends ContentNode {
    private String string;
    private String keys;
    private Boolean multiLine;
    private Alignment alignment;
    private VAlignment valignment;
    private Effect effect;
    private Font font;

    public DynamicNode() {
        super();
        // this.effect = new Effect(EffectType.IMMEDIATE_SHOW);
        // this.effect.setHold(360000);
        // setType("dynamic"); // 动态内容
        multiLine = false;
    }

    public DynamicNode(String text, String keys) {
        this();
        this.string = text;
        this.keys = keys;
    }

    public DynamicNode(DynamicNode other) {
        super(other);
        this.string = other.string;
        this.multiLine = other.multiLine;
        this.alignment = other.alignment;
        this.valignment = other.valignment;
        this.effect = other.effect;
        this.font = other.font;
    }
    
    public enum Alignment {
        center("center"),   ///< 居中对齐
        left("left"),       ///< 左对齐
        right("right");     ///< 右对齐

        private final String value;

        public String getValue() {
            return value;
        }

        Alignment(String value) {
            this.value = value;
        }
    }
    
    public enum VAlignment {
        middle("middle"),   ///< 垂直居中
        top("top"),         ///< 上对齐
        bottom("bottom");   ///< 下对齐

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

    public String getKeys() {
        return keys;
    }

    public void setKeys(String keys) {
        this.keys = keys;
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
