package cn.huidu.device.api.sdk.data.program.other;

public class Border {
    private int type;
    private int speed;
    private Effect effect;

    public Border() {
        type = 0;
        speed = 5;
        effect = Effect.Static;
    }

    public Border(int type) {
        this();
        this.type = type;
    }

    public Border(int type, int speed) {
        this(type);
        this.speed = speed;
    }

    public Border(int type, int speed, Effect effect) {
        this(type, speed);
        this.effect = effect;
    }

    public Border(Border other) {
        this(other.type, other.speed, other.effect);
    }

    public enum Effect {
        Rotate("rotate"),/// < 旋转
        Blink("blink"),  /// < 闪烁
        Static("null");  /// < 静止

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

    public int getSpeed() {
        return speed;
    }

    public void setSpeed(int speed) {
        this.speed = speed;
    }

    public Effect getEffect() {
        return effect;
    }

    public void setEffect(Effect effect) {
        this.effect = effect;
    }
}
