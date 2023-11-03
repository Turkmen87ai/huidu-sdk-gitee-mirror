package cn.huidu.device.api.demo.demo3_baseProgram;

import cn.huidu.device.api.sdk.Program;
import cn.huidu.device.api.sdk.data.program.ProgramNode;
import cn.huidu.device.api.sdk.data.program.area.content.ImageNode;

public class image {
    public static void main(String[] args) {
        // 替换成你自己的参数
        // String host = "${YourHost}";
        // String sdkKey = "${YourSdkKey}";
        // String sdkSecret = "${YourSdkSecret}";
        // Config.InitSdk(host, sdkKey, sdkSecret);

        // 1. 构建节目数据节点，只有一个图片区域
        ProgramNode programNode = new ProgramNode(new ImageNode("D:/WorkSpace/TestFiles/Images/1600829925_1836547993.dat.gif"));
        // 2. 实例化节目接口对象
        Program program = new Program();
        
        // 3. 添加节目到设备
        String jsonResult = program.replace(new String[] { "" }, programNode);
        // 4. 打印结果
        System.out.println(jsonResult);
    }

}
