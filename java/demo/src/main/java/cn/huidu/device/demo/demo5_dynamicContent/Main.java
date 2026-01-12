package cn.huidu.device.demo.demo5_dynamicContent;

import cn.huidu.device.sdk.Program;
import cn.huidu.device.sdk.data.program.ProgramNode;
import cn.huidu.device.sdk.data.program.area.content.DynamicNode;

public class Main {
    public static void main(String[] args) {
        // Replace with your own parameters
        // String host = "${YourHost}";
        // String sdkKey = "${YourSdkKey}";
        // String sdkSecret = "${YourSdkSecret}";
        // Config.InitSdk(host, sdkKey, sdkSecret);

        /**
         * This example demonstrates dynamic content template for program area (used with task push, content changes are updated via task push interface).
         */

        // 2. Create program data node and dynamic template
        ProgramNode programNode = new ProgramNode(
                new DynamicNode("大型智能停车场信息<br>当前的温度:{{temperature}} ℃<br>剩余车位:{{parkingSpace}} 个",
                        "temperature,parkingSpace"));

        // 3. Instantiate program interface object
        Program program = new Program();
        // 4. Add program to device
        String jsonResult = program.replace(new String[] { "" }, programNode);
        // 5. Print result
        System.out.println(jsonResult);
    }

}
