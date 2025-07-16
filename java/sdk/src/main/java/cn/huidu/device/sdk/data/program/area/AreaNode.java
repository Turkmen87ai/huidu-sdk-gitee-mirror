package cn.huidu.device.sdk.data.program.area;

import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;

import cn.huidu.device.sdk.data.program.area.content.ContentNode;
import cn.huidu.device.sdk.data.program.area.content.DialClockNode;
import cn.huidu.device.sdk.data.program.area.content.DigitalClockNode;
import cn.huidu.device.sdk.data.program.area.content.DynamicNode;
import cn.huidu.device.sdk.data.program.area.content.ImageNode;
import cn.huidu.device.sdk.data.program.area.content.TextNode;
import cn.huidu.device.sdk.data.program.area.content.VideoNode;
import cn.huidu.device.sdk.data.program.other.Border;

public class AreaNode extends ContentNode {
    private int x;
    private int y;
    private int width;
    private int height;
    private ContentNode[] item;
    private Border border;

    public AreaNode() {
        super();
    }

    public AreaNode(JSONObject jsonObj) {
        this(jsonObj.toJavaObject(AreaNode.class));
        // 重新初始化内容插件
        JSONArray jsons = jsonObj.getJSONArray("item");
        if (jsons.size() == item.length) {
            for (int i = 0; i < item.length; i++) {
                if (item[i].getType() == null) {
                    continue;
                }

                switch (item[i].getType()) {
                    case "text": {
                        item[i] = jsons.getJSONObject(i).toJavaObject(TextNode.class);
                    }
                        break;
                    case "dynamic": {
                        item[i] = jsons.getJSONObject(i).toJavaObject(DynamicNode.class);
                    }
                        break;
                    case "image": {
                        item[i] = jsons.getJSONObject(i).toJavaObject(ImageNode.class);
                    }
                        break;
                    case "video": {
                        item[i] = jsons.getJSONObject(i).toJavaObject(VideoNode.class);
                    }
                        break;
                    case "digitalClock": {
                        item[i] = jsons.getJSONObject(i).toJavaObject(DigitalClockNode.class);
                    }
                        break;
                    case "dialClock": {
                        item[i] = jsons.getJSONObject(i).toJavaObject(DialClockNode.class);
                    }
                        break;
                    default:
                        break;
                }
            }
        }
    }

    public AreaNode(ContentNode contents) {
        this.item = new ContentNode[] { contents };
    }

    public AreaNode(ContentNode[] contents) {
        this.item = contents;
    }

    protected AreaNode(AreaNode other) {
        super(other);
        this.x = other.x;
        this.y = other.y;
        this.width = other.width;
        this.height = other.height;
        this.item = other.item;
        this.border = other.border;
    }

    public int getX() {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }

    public int getWidth() {
        return width;
    }

    public void setWidth(int width) {
        this.width = width;
    }

    public int getHeight() {
        return height;
    }

    public void setHeight(int height) {
        this.height = height;
    }

    public ContentNode[] getItem() {
        return item;
    }

    public void setItem(ContentNode[] item) {
        this.item = item;
    }

    public Border getBorder() {
        return border;
    }

    public void setBorder(Border border) {
        this.border = border;
    }
}
