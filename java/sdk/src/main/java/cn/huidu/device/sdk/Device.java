package cn.huidu.device.sdk;

import java.util.HashMap;
import java.util.Map;

import cn.huidu.device.sdk.common.BaseClient;

public class Device extends BaseClient {

    public String getOnlineDevices() {
        return getDevice();
    }

    public String setDeviceName(String id, String name) {
        return setDeviceProperty(id, "name", name);
    }

    public String setScreenSize(String id, int width, int height) {
        Map<String, String> map = new HashMap<>();
        map.put("screen.width", Integer.toString(width));
        map.put("screen.height", Integer.toString(height));
        return setDeviceProperty(id, map);
    }

    public String getDeviceProperty(String id) {
        return getDeviceProperty(new String[] { id }, new String[] {});
    }

    public String getDeviceProperty(String[] id) {
        return getDeviceProperty(id, new String[] {});
    }

    public String getDeviceProperty(String id, String property) {
        return getDeviceProperty(new String[] { id }, new String[] { property });
    }

    public String getDeviceProperty(String id, String[] propertys) {
        return getDeviceProperty(new String[] { id }, propertys);
    }

    public String getDeviceProperty(String[] id, String property) {
        return getDeviceProperty(id, new String[] { property });
    }

    public String getDeviceProperty(String[] id, String[] propertys) {
        return device(id, "getDeviceProperty", propertys);
    }

    public String setDeviceProperty(String id, String propKey, String propValues) {
        Map<String, String> map = new HashMap<>();
        map.put(propKey, propValues);
        return setDeviceProperty(new String[] { id }, map);
    }

    public String setDeviceProperty(String id, Map<String, String> propKeyValues) {
        return setDeviceProperty(new String[] { id }, propKeyValues);
    }

    public String setDeviceProperty(String[] id, String propKey, String propValues) {
        Map<String, String> map = new HashMap<>();
        map.put(propKey, propValues);
        return setDeviceProperty(id, map);
    }

    public String setDeviceProperty(String[] id, Map<String, String> propKeyValues) {
        return device(id, "setDeviceProperty", propKeyValues);
    }

    public String getDeviceStatus(String id) {
        return getDeviceStatus(new String[] { id }, null);
    }

    public String getDeviceStatus(String[] id) {
        return getDeviceStatus(id, null);
    }

    public String getDeviceStatus(String id, String[] keys) {
        return getDeviceStatus(new String[] { id }, keys);
    }

    public String getDeviceStatus(String[] id, String[] keys) {
        return device(id, "getDeviceStatus", keys);
    }

}
