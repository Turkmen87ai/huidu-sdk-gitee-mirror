package cn.huidu.device.demo.demo4_multiProgram;

import java.util.ArrayList;

import cn.huidu.device.sdk.Program;
import cn.huidu.device.sdk.data.program.ProgramNode;
import cn.huidu.device.sdk.data.program.area.AreaNode;
import cn.huidu.device.sdk.data.program.area.content.ContentNode;
import cn.huidu.device.sdk.data.program.area.content.DynamicNode;
import cn.huidu.device.sdk.data.program.area.content.ImageNode;
import cn.huidu.device.sdk.data.program.area.content.TextNode;
import cn.huidu.device.sdk.data.program.area.content.VideoNode;

public class Main {
        public static void main(String[] args) {
                // 替换成你自己的参数
                // String host = "${YourHost}";
                // String sdkKey = "${YourSdkKey}";
                // String sdkSecret = "${YourSdkSecret}";
                // Config.InitSdk(host, sdkKey, sdkSecret);

                /**
                 * 本示例展示了2个节目，其中第二个节目包括两个区域的左右组合
                 */

                // 1. 创建第一个节目的文本、动态、图片、视频等内容
                ArrayList<ContentNode> nodes = new ArrayList<ContentNode>();
                // 2. 创建文本内容
                ContentNode node = new TextNode("测试文本内容区域: 0123456789abcdefg");
                nodes.add(node);
                // 3. 创建动态内容
                node = new DynamicNode("测试动态内容区域:<br> 当前的温度:{{temperature}}<br>剩余车位:{{ParkingSpace}}",
                                "temperature,ParkingSpace");

                nodes.add(node);
                // 4. 创建图片内容
                node = new ImageNode("D:/WorkSpace/TestFiles/Images/15秒.gif");
                nodes.add(node);
                // 5. 创建视频内容
                node = new VideoNode("D:/WorkSpace/TestFiles/Video/[1080P]周杰伦-超跑女神.mp4");
                nodes.add(node);

                // 6. 构建第一个节目数据节点
                ProgramNode programNode = new ProgramNode(nodes.toArray(new ContentNode[nodes.size()]));

                // 7. 创建第二个节目的第一个区域的文本、动态等内容
                nodes.clear();
                // 8. 创建文本内容
                node = new TextNode("第二个节目的第一个区域的文本内容区域: 0123456789abcdefg");
                nodes.add(node);
                // 9. 创建动态内容
                node = new DynamicNode("第二个节目的第一个区域的动态内容区域:<br> 当前的温度:{{temperature}}<br>剩余车位:{{ParkingSpace}}",
                                "temperature,ParkingSpace");
                nodes.add(node);
                // 10. 构建第一个区域数据节点
                AreaNode areaNode = new AreaNode(nodes.toArray(new ContentNode[nodes.size()]));
                areaNode.setWidth(64);
                areaNode.setHeight(64);

                // 11. 创建第二个节目的第一个区域的文本、动态等内容
                nodes.clear();
                // 12. 创建文本内容
                node = new TextNode("第二个节目的第二个区域的文本内容区域: 0123456789abcdefg");
                nodes.add(node);
                // 13. 创建动态内容
                node = new DynamicNode("第二个节目的第二个区域的动态内容区域:<br> 当前的温度:{{temperature}}<br>剩余车位:{{ParkingSpace}}",
                                "temperature,ParkingSpace");
                nodes.add(node);
                // 14. 构建第一个区域数据节点
                AreaNode areaNode2 = new AreaNode(nodes.toArray(new ContentNode[nodes.size()]));
                areaNode2.setX(64);
                areaNode2.setY(0);
                areaNode2.setWidth(64);
                areaNode2.setHeight(64);

                // 15. 创建第二个节目的数据节点
                ProgramNode programNode2 = new ProgramNode(new AreaNode[] { areaNode, areaNode2 });

                // 16. 实例化节目接口对象
                Program program = new Program();
                // 17. 添加节目到设备
                String jsonResult = program.replace(new String[] { "" },
                                new ProgramNode[] { programNode, programNode2 });
                // 18. 打印结果
                System.out.println(jsonResult);
        }

}
