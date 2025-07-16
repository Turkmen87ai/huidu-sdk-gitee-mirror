package cn.huidu.device.demo.demo5_dynamicContent;

import cn.huidu.device.sdk.Program;
import cn.huidu.device.sdk.data.program.ProgramNode;
import cn.huidu.device.sdk.data.program.area.content.DynamicNode;

public class Main {
    public static void main(String[] args) {
        // 替换成你自己的参数
        // String host = "${YourHost}";
        // String sdkKey = "${YourSdkKey}";
        // String sdkSecret = "${YourSdkSecret}";
        // Config.InitSdk(host, sdkKey, sdkSecret);

        /**
         * 本示例展示了节目区域的动态内容模板（配合任务推送使用，内容变化有任务推送接口更新）。
         */

        // 2. 创建节目的数据节点和动态模板
        ProgramNode programNode = new ProgramNode(
                new DynamicNode("大型智能停车场信息<br>当前的温度:{{temperature}} ℃<br>剩余车位:{{parkingSpace}} 个",
                        "temperature,parkingSpace"));

        // 3. 实例化节目接口对象
        Program program = new Program();
        // 4. 添加节目到设备
        String jsonResult = program.replace(new String[] { "" }, programNode);
        // 5. 打印结果
        System.out.println(jsonResult);
    }

}
