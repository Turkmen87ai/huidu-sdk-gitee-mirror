package cn.huidu.device.demo.demo6_multiAreaProgramSwitch;

import java.util.ArrayList;
import cn.huidu.device.sdk.Program;
import cn.huidu.device.sdk.data.program.ProgramNode;
import cn.huidu.device.sdk.data.program.area.AreaNode;
import cn.huidu.device.sdk.data.program.area.content.ContentNode;
import cn.huidu.device.sdk.data.program.area.content.TextNode;
import cn.huidu.device.sdk.data.program.other.Font;

public class Main {
        public static void main(String[] args) {
                // Replace with your own parameters
                // String host = "${YourHost}";
                // String sdkKey = "${YourSdkKey}";
                // String sdkSecret = "${YourSdkSecret}";
                // Config.InitSdk(host, sdkKey, sdkSecret);

                /**
                 * This example demonstrates a program with 4 areas, each area has multiple contents, the first one plays by default, others need to be switched through state changes (used with task push, content changes are updated via task push interface).
                 */

                String[] areaNames = new String[] {
                                "东", "南", "西", "北"
                };

                String[] colors = new String[] {
                                "#FFFFFF", "#FF0000", "#FFFF00", "#00FF00"
                };

                ArrayList<AreaNode> areas = new ArrayList<AreaNode>();

                // 1. Create multiple areas and multiple states
                for (int index = 0; index < areaNames.length; index++) {

                        String bindString = areaNames[index];

                        // Create content resources for each area
                        ArrayList<ContentNode> nodes = new ArrayList<ContentNode>();
                        for (int index2 = 0; index2 < colors.length; index2++) {
                                // Build area data node
                                String text = areaNames[index] + String.valueOf(index2);// Content to be displayed
                                TextNode node = new TextNode(text);
                                node.setBindType(String.valueOf(index2)); // Bind area type

                                Font font = new Font(30, colors[index2]);
                                node.setFont(font);

                                nodes.add(node);
                        }

                        // Build area data node
                        AreaNode areaNode = new AreaNode(nodes.toArray(new ContentNode[nodes.size()]));
                        areaNode.setX(index * 64); // Arrange sequentially
                        areaNode.setY(0);
                        areaNode.setWidth(64);
                        areaNode.setHeight(64);

                        areaNode.setBindType(bindString); // Bind area type

                        areas.add(areaNode);
                }

                // 2. Create program data node
                ProgramNode programNode = new ProgramNode(areas.toArray(new AreaNode[areas.size()]));

                // 3. Instantiate program interface object
                Program program = new Program();
                // 4. Add program to device
                String jsonResult = program.replace(new String[] { "" }, programNode);
                // 5. Print result
                System.out.println(jsonResult);
        }

}
