package cn.huidu.device.sdk.data.program.other;

public class Border {
    private int type;
    private Speed speed;
    private Effect effect;

    public Border() {
        type = 0;
        speed = Speed.Middle;
        effect = Effect.Static;
    }

    public Border(int type) {
        this();
        this.type = type;
    }

    public Border(int type, Speed speed) {
        this(type);
        this.speed = speed;
    }

    public Border(int type, Speed speed, Effect effect) {
        this(type, speed);
        this.effect = effect;
    }

    public Border(Border other) {
        this(other.type, other.speed, other.effect);
    }

    public enum Speed {
        Slow("slow"), /// < 慢
        Middle("middle"), /// < 适中
        Fast("fast"); /// < 快

        private final String value;

        public String getValue() {
            return value;
        }

        Speed(String value) {
            this.value = value;
        }
    }

    public enum Effect {
        Rotate("rotate"), /// < 旋转
        Blink("blink"), /// < 闪烁
        Static("null"); /// < 静止

        private final String value;

        public String getValue() {
            return value;
        }

        Effect(String value) {
            this.value = value;
        }
    }

    public int getType() {
        return type;
    }

    public void setType(int type) {
        this.type = type;
    }

    public Speed getSpeed() {
        return speed;
    }

    public void setSpeed(Speed speed) {
        this.speed = speed;
    }

    public Effect getEffect() {
        return effect;
    }

    public void setEffect(Effect effect) {
        this.effect = effect;
    }
}
