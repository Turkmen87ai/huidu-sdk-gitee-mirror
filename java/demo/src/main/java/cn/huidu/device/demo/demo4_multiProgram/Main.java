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
                // Replace with your own parameters
                // String host = "${YourHost}";
                // String sdkKey = "${YourSdkKey}";
                // String sdkSecret = "${YourSdkSecret}";
                // Config.InitSdk(host, sdkKey, sdkSecret);

                /**
                 * This example demonstrates 2 programs, where the second program includes left-right combination of two areas
                 */

                // 1. Create text, dynamic, image, video content for the first program
                ArrayList<ContentNode> nodes = new ArrayList<ContentNode>();
                // 2. Create text content
                ContentNode node = new TextNode("测试文本内容区域: 0123456789abcdefg");
                nodes.add(node);
                // 3. Create dynamic content
                node = new DynamicNode("测试动态内容区域:<br> 当前的温度:{{temperature}}<br>剩余车位:{{ParkingSpace}}",
                                "temperature,ParkingSpace");

                nodes.add(node);
                // 4. Create image content
                node = new ImageNode("D:/WorkSpace/TestFiles/Images/15秒.gif");
                nodes.add(node);
                // 5. Create video content
                node = new VideoNode("D:/WorkSpace/TestFiles/Video/[1080P]周杰伦-超跑女神.mp4");
                nodes.add(node);

                // 6. Build first program data node
                ProgramNode programNode = new ProgramNode(nodes.toArray(new ContentNode[nodes.size()]));

                // 7. Create text, dynamic content for the first area of the second program
                nodes.clear();
                // 8. Create text content
                node = new TextNode("第二个节目的第一个区域的文本内容区域: 0123456789abcdefg");
                nodes.add(node);
                // 9. Create dynamic content
                node = new DynamicNode("第二个节目的第一个区域的动态内容区域:<br> 当前的温度:{{temperature}}<br>剩余车位:{{ParkingSpace}}",
                                "temperature,ParkingSpace");
                nodes.add(node);
                // 10. Build first area data node
                AreaNode areaNode = new AreaNode(nodes.toArray(new ContentNode[nodes.size()]));
                areaNode.setWidth(64);
                areaNode.setHeight(64);

                // 11. Create text, dynamic content for the second area of the second program
                nodes.clear();
                // 12. Create text content
                node = new TextNode("第二个节目的第二个区域的文本内容区域: 0123456789abcdefg");
                nodes.add(node);
                // 13. Create dynamic content
                node = new DynamicNode("第二个节目的第二个区域的动态内容区域:<br> 当前的温度:{{temperature}}<br>剩余车位:{{ParkingSpace}}",
                                "temperature,ParkingSpace");
                nodes.add(node);
                // 14. Build second area data node
                AreaNode areaNode2 = new AreaNode(nodes.toArray(new ContentNode[nodes.size()]));
                areaNode2.setX(64);
                areaNode2.setY(0);
                areaNode2.setWidth(64);
                areaNode2.setHeight(64);

                // 15. Create second program data node
                ProgramNode programNode2 = new ProgramNode(new AreaNode[] { areaNode, areaNode2 });

                // 16. Instantiate program interface object
                Program program = new Program();
                // 17. Add program to device
                String jsonResult = program.replace(new String[] { "" },
                                new ProgramNode[] { programNode, programNode2 });
                // 18. Print result
                System.out.println(jsonResult);
        }

}
