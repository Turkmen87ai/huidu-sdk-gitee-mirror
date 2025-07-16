package cn.huidu.device.sdk.common;

import java.io.FileInputStream;
import java.util.Properties;

public class Config {
    public static String host = null;
    public static String sdkKey = null;
    public static String sdkSecret = null;

    // 环境初始化
    public static void InitSdk(String host, String sdkKey, String sdkSecret) {
        Config.host = host;
        Config.sdkKey = sdkKey;
        Config.sdkSecret = sdkSecret;
    }

    // 环境初始化
    protected static void InitSdk() {
        Properties prop = new Properties();
        try {
            // 读取application.properties文件
            FileInputStream fileInputStream = new FileInputStream(
                    "huidusdk\\src\\main\\resources\\application.properties");
            prop.load(fileInputStream);

            Config.host = prop.getProperty("host");
            Config.sdkKey = prop.getProperty("sdkKey");
            Config.sdkSecret = prop.getProperty("sdkSecret");

            fileInputStream.close();
        } catch (Exception e) {

        }
    }

    static {
        Config.InitSdk();
    }
}
