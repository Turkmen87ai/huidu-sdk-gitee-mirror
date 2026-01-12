package cn.huidu.device.demo.demo3_baseProgram;

import cn.huidu.device.sdk.Program;
import cn.huidu.device.sdk.data.program.ProgramNode;
import cn.huidu.device.sdk.data.program.area.content.VideoNode;

public class video {
    public static void main(String[] args) {
        // Replace with your own parameters
        // String host = "${YourHost}";
        // String sdkKey = "${YourSdkKey}";
        // String sdkSecret = "${YourSdkSecret}";
        // Config.InitSdk(host, sdkKey, sdkSecret);

        // 1. Build program data node with only one video area
        ProgramNode programNode = new ProgramNode(new VideoNode("D:/WorkSpace/TestFiles/Video/[1080P]周杰伦-超跑女神.mp4"));
        // 2. Instantiate program interface object
        Program program = new Program();
        // 3. Add program to device
        String jsonResult = program.replace(new String[] { "" }, programNode);
        // 4. Print result
        System.out.println(jsonResult);
    }

}
