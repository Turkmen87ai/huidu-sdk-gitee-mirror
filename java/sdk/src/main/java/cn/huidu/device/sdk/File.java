package cn.huidu.device.sdk;

import cn.huidu.device.sdk.common.BaseClient;

public class File extends BaseClient {

    public String uploadFile(String filePath) {
        return file(filePath);
    }
}
