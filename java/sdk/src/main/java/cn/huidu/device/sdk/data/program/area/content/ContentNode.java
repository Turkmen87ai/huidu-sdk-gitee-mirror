package cn.huidu.device.sdk.data.program.area.content;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.annotation.JSONField;

import cn.huidu.device.sdk.data.program.other.FileInfo;

public class ContentNode {
    private String uuid;
    private String name;
    private String type;
    private String bindType;

    public ContentNode() {
    }

    public ContentNode(String id, String name) {
        this.uuid = id;
        this.name = name;
    }

    protected ContentNode(ContentNode other) {
        this(other.uuid, other.name);
        this.type = other.type;
        this.bindType = other.bindType;
    }

    @JSONField(name = "uuid")
    public String getId() {
        return uuid;
    }

    @JSONField(name = "uuid")
    public void setId(String uuid) {
        this.uuid = uuid;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getBindType() {
        return bindType;
    }

    public void setBindType(String bindType) {
        this.bindType = bindType;
    }

    public FileInfo[] getFilesInfo() {
        return null;
    }

    public void updateFilesInfo(FileInfo[] filesinfo) {

    }

    public String toString() {
        return JSON.toJSONString(this);
    }

}
