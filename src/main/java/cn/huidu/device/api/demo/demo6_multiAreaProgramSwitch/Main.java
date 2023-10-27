package cn.huidu.device.api.demo.demo6_multiAreaProgramSwitch;

import java.util.ArrayList;
import cn.huidu.device.api.sdk.Program;
import cn.huidu.device.api.sdk.data.program.ProgramNode;
import cn.huidu.device.api.sdk.data.program.area.AreaNode;
import cn.huidu.device.api.sdk.data.program.area.content.ContentNode;
import cn.huidu.device.api.sdk.data.program.area.content.TextNode;
import cn.huidu.device.api.sdk.data.program.other.Font;

public class Main {
    public static void main(String[] args) {
        // 替换成你自己的参数
        // String host = "${YourHost}";
        // String sdkKey = "${YourSdkKey}";
        // String sdkSecret = "${YourSdkSecret}";
        // Config.InitSdk(host, sdkKey, sdkSecret);

        /**
         * 本示例展示了节目包括两4区域，每个区域有多个内容，默认播放第一个，其他需要通过状态变化来切换(配合任务推送使用，内容变化有任务推送接口更新)。
         */

        String[] areaNames = new String[]{
                "东","南","西","北"
        };

        String[] colors = new String[]{
                "#FFFFFF","#FF0000","#FFFF00","#00FF00"
        };

        ArrayList<AreaNode> areas = new ArrayList<AreaNode>();

        // 1. 创建多个区域和多个状态
        for (int index = 0; index < areaNames.length; index++) {

                String bindString = areaNames[index];

                // 每个区域创建内容资源
                ArrayList<ContentNode> nodes = new ArrayList<ContentNode>();
                for (int index2 = 0; index2 < colors.length; index2++) {
                        //构建区域数据节点
                        String text = areaNames[index] + String.valueOf(index2);// 对应需要显示的内容
                        TextNode node = new TextNode(text);
                        node.setBindType(String.valueOf(index2)); // 绑定区域类型

                        Font font = new Font(30, colors[index2]);
                        node.setFont(font);

                        nodes.add(node);
                }
                
                //构建区域数据节点
                AreaNode areaNode = new AreaNode(nodes.toArray(new ContentNode[nodes.size()]));
                areaNode.setX(index * 64); // 依次往后排
                areaNode.setY(0);
                areaNode.setWidth(64);
                areaNode.setHeight(64);

                
                areaNode.setBindType(bindString); // 绑定区域类型

                areas.add(areaNode);
        }

        // 2. 创建节目的数据节点
        ProgramNode programNode = new ProgramNode(areas.toArray(new AreaNode[areas.size()]));

        // 3. 实例化节目接口对象
        Program program = new Program();
        // 4. 添加节目到设备
        String jsonResult = program.replace(new String[] { "" }, programNode);
        // 5. 打印结果
        System.out.println(jsonResult);
    }

}
