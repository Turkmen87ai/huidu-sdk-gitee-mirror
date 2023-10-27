package cn.huidu.device.api.sdk;

import cn.huidu.device.api.sdk.common.BaseClient;

public class File extends BaseClient {

     public String uploadFile(String filePath) {
        return file(filePath);
    }
}
