package cn.huidu.device.api.sdk.data.program;

import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;

import cn.huidu.device.api.sdk.data.program.area.AreaNode;
import cn.huidu.device.api.sdk.data.program.area.content.ContentNode;
import cn.huidu.device.api.sdk.data.program.other.Border;
import cn.huidu.device.api.sdk.data.program.other.PlayControl;

public class ProgramNode extends ContentNode {
    private AreaNode[] area;
    private Border border;
    private PlayControl playControl;
    
    public AreaNode[] getArea() {
        return area;
    }

    public void setArea(AreaNode[] area) {
        this.area = area;
    }

    public PlayControl getPlayControl() {
        return playControl;
    }

    public void setPlayControl(PlayControl playControl) {
        this.playControl = playControl;
    }

    public Border getBorder() {
        return border;
    }

    public void setBorder(Border border) {
        this.border = border;
    }

    public ProgramNode() {
        super();
    }

    public ProgramNode(AreaNode ares) {
        this.area = new AreaNode[] { ares };
    }
    
    public ProgramNode(AreaNode[] areas) {
        this.area = areas;
    }

    public ProgramNode(ContentNode contents) {
        area = new AreaNode[] { new AreaNode(contents) };
    }

    public ProgramNode(ContentNode[] contents) {
        area = new AreaNode[] { new AreaNode(contents) };
    }
    
    public ProgramNode(String jsonText) {
        this(JSONObject.parseObject(jsonText));
    }

    public ProgramNode(JSONObject jsonObj) {
        this(jsonObj.toJavaObject(ProgramNode.class));
        // 初始化区域
        JSONArray jsons = jsonObj.getJSONArray("area");
        if (jsons.size() == area.length) {
            for (int i = 0; i < area.length; i++) {
                area[i] = new AreaNode(jsons.getJSONObject(i));
            }
        }
    }

    protected ProgramNode(ProgramNode other) {
        super(other);
        this.area = other.area;
        this.border = other.border;
        this.playControl = other.playControl;
    }

}
