#include <stdio.h>
#include "DialClockNode.h"
#include "DigitalClockNode.h"
#include "TextNode.h"
#include "ImageNode.h"
#include "VideoNode.h"
#include "AreaNode.h"
#include "ProgramNode.h"
#include "Config.h"
#include "Program.h"
#include "ContentNode.h"

int main() {
    // Replace with your own parameters
    char* host = "${YourHost}";
    char* sdkKey = "${YourSdkKey}";
    char* sdkSecret = "${YourSdkSecret}";
    InitSdk(host, sdkKey, sdkSecret);

    //// 1. Instantiate the interface object.
    //// Text Program
    //TextNode* text = createWithTextTextNode("1234");
    //// Simulated Clock Program
    //DialClockNode* dialClock = createDialClockNode();
    //// Digital Clock Program
    //DigitalClockNode* digitalClock = createDigitalClockNode();
    //// Image Program Local Upload
    ImageNode* image = createWithLocalPathImageNode("E:/Desktop/1.png");
    //// Image program HTTP download
    //ImageNode* image = createWithUrlFileSizeMd5ImageNode("https://persuasion.yingkeiot.cn/attachment/violations/11/2024-06-03/80602000-58c6-43b5-adc9-b072ec04c792.jpg",
    //    337460,
    //    "498c7bbab17011a3d257cf0468bcff08");
	//// Video Program Local Upload
    //VideoNode* video = createWithPathVideoNode("E:/Desktop/0d40fafa06c67b082843dbb63c964b46-128x64-q2-v1-au.mp4");
    
    // 2. Construct the program data node.
    ContentNode* contents[] = { (ContentNode*)image };
    AreaNode* area = createAreaNodeWithContents(contents, sizeof(contents) / sizeof(ContentNode*));
    setXAreaNode(area, 0);
    setYAreaNode(area, 0);
    setWidthAreaNode(area, 128);
    setHeightAreaNode(area, 64);

    // 3. Instantiate the program interface object.
    ProgramNode* programNode = createProgramNodeWithArea(area);

    // 4. Add the program to the device.
    ProgramClient* programClient = createProgramClient();
    const char* devIds[] = { "C16L-D00-A000F" };
    char* jsonResult = replaceSingleProgramClient(programClient, devIds, sizeof(devIds) / sizeof(char*), programNode);
    
    // 5. Release resources
    destroyProgramNode(programNode);
    destroyProgramClient(programClient);
	destroyConfig();

    // 6. Print result
    printf("%s\n", jsonResult);

    system("pause");
}
