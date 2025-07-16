package cn.huidu.device.demo.demo3_baseProgram;

import cn.huidu.device.sdk.Program;
import cn.huidu.device.sdk.data.program.ProgramNode;
import cn.huidu.device.sdk.data.program.area.content.VideoNode;

public class video {
    public static void main(String[] args) {
        // 替换成你自己的参数
        // String host = "${YourHost}";
        // String sdkKey = "${YourSdkKey}";
        // String sdkSecret = "${YourSdkSecret}";
        // Config.InitSdk(host, sdkKey, sdkSecret);

        // 1. 构建节目数据节点，只有一个视频区域
        ProgramNode programNode = new ProgramNode(new VideoNode("D:/WorkSpace/TestFiles/Video/[1080P]周杰伦-超跑女神.mp4"));
        // 2. 实例化节目接口对象
        Program program = new Program();
        // 3. 添加节目到设备
        String jsonResult = program.replace(new String[] { "" }, programNode);
        // 4. 打印结果
        System.out.println(jsonResult);
    }

}
