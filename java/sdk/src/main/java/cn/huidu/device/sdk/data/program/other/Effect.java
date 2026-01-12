package cn.huidu.device.sdk.data.program.other;

import com.alibaba.fastjson.annotation.JSONField;

public class Effect {

    private EffectType type;
    private int speed;
    private int hold;

    @JSONField(serialize = false)
    public EffectType getType() {
        return type;
    }

    @JSONField(deserialize = false)
    public void setType(EffectType type) {
        this.type = type;
    }

    @JSONField(name = "type")
    public int getTypeValue() {
        return type.getValue();
    }

    @JSONField(name = "type")
    public void setTypeValue(int type) {
        this.type = EffectType.valueOf(type);
    }

    public int getSpeed() {
        return speed;
    }

    public void setSpeed(int speed) {
        this.speed = speed;
    }

    public int getHold() {
        return hold;
    }

    public void setHold(int hold) {
        this.hold = hold;
    }

    public Effect() {
        type = EffectType.IMMEDIATE_SHOW;
        speed = 5;
        hold = 5000;
    }

    public Effect(EffectType type) {
        this();
        this.type = type;
    }

    public Effect(EffectType type, int speed) {
        this(type);
        this.speed = speed;
    }

    public Effect(EffectType type, int speed, int hold) {
        this(type, speed);
        this.hold = hold;
    }

    public Effect(Effect other) {
        this(other.type, other.speed, other.hold);
    }

    public enum EffectType {
        IMMEDIATE_SHOW(0), /// < Immediate display.
        LEFT_PARALLEL_MOVE(1), /// < Move left.
        RIGHT_PARALLEL_MOVE(2), /// < Move right.
        UP_PARALLEL_MOVE(3), /// < Move up.
        DOWN_PARALLEL_MOVE(4), /// < Move down.
        LEFT_COVER(5), /// < Cover from left.
        RIGHT_COVER(6), /// < Cover from right.
        UP_COVER(7), /// < Cover from top.
        DOWN_COVER(8), /// < Cover from bottom.
        LEFT_TOP_COVER(9), /// < Cover from top-left.
        LEFT_BOTTOM_COVER(10), /// < Cover from bottom-left.
        RIGHT_TOP_COVER(11), /// < Cover from top-right.
        RIGHT_BOTTOM_COVER(12), /// < Cover from bottom-right.
        HORIZONTAL_DIVIDE(13), /// < Horizontal split.
        VERTICAL_DIVIDE(14), /// < Vertical split.
        HORIZONTAL_CLOSE(15), /// < Horizontal close.
        VERTICAL_CLOSE(16), /// < Vertical close.
        FADE(17), /// < Fade in/out.
        HORIZONTAL_SHUTTER(18), /// < Horizontal blinds.
        VERTICAL_SHUTTER(19), /// < Vertical blinds.
        NOT_CLEAR_AREA(20), /// < Do not clear area.
        LEFT_SERIES_MOVE(21), /// < Continuous left move.
        RIGHT_SERIES_MOVE(22), /// < Continuous right move.
        UP_SERIES_MOVE(23), /// < Continuous up move.
        DOWN_SERIES_MOVE(24), /// < Continuous down move.
        RANDOM(25), /// < Random effect.
        HT_LEFT_SERIES_MOVE(26), /// < Head-to-tail continuous left move.
        HT_RIGHT_SERIES_MOVE(27), /// < Head-to-tail continuous right move.
        HT_UP_SERIES_MOVE(28), /// < Head-to-tail continuous up move.
        HT_DOWN_SERIES_MOVE(29), /// < Head-to-tail continuous down move.
        FLICKEREFFECT(30); /// < Flicker effect.

        private final int value;

        EffectType(int value) {
            this.value = value;
        }

        public int getValue() {
            return value;
        }

        // Convert int value to corresponding enum constant
        public static EffectType valueOf(int value) {
            for (EffectType enumValue : EffectType.values()) {
                if (enumValue.getValue() == value) {
                    return enumValue;
                }
            }
            return IMMEDIATE_SHOW;
        }
    };
}
