package cn.huidu.device.sdk.data.program.area.content;

import cn.huidu.device.sdk.data.program.other.Effect;
import cn.huidu.device.sdk.data.program.other.Effect.EffectType;

public class DynamicNode extends TextNode {
    private String keys;

    public DynamicNode() {
        super();
        this.effect = new Effect(EffectType.IMMEDIATE_SHOW);
        this.effect.setHold(360000);
        setType("dynamic"); // Dynamic content
        // multiLine = false;
    }

    public DynamicNode(String text, String keys) {
        this();
        this.string = text;
        this.keys = keys;
    }

    public DynamicNode(DynamicNode other) {
        super(other);
        this.keys = other.keys;
    }

    public String getKeys() {
        return keys;
    }

    public void setKeys(String keys) {
        this.keys = keys;
    }

}
