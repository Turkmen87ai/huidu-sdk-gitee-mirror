package cn.huidu.device.sdk.deviceTask;

import java.util.HashMap;
import java.util.Map;
import cn.huidu.device.sdk.common.BaseClient;

public class PushStatusTask extends BaseClient {

    public String PushStatus(String id, String keyType, String value) {
        return PushStatus(new String[] { id }, new HashMap<String, String>() {
            {
                put(keyType, value);
            }
        });
    }

    public String PushStatus(String id, Map<String, String> KeyValues) {
        return PushStatus(new String[] { id }, KeyValues);
    }

    public String PushStatus(String[] id, String keyType, String value) {
        return PushStatus(id, new HashMap<String, String>() {
            {
                put(keyType, value);
            }
        });
    }

    public String PushStatus(String[] id, Map<String, String> KeyValues) {
        return device(id, "pushStatus", KeyValues);
    }
}
