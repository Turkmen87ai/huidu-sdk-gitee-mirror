#include <stdio.h>
#include "TextNode.h"
#include "VideoNode.h"
#include "AreaNode.h"
#include "ProgramNode.h"
#include "Config.h"
#include "Program.h"
#include "ContentNode.h"

int main() {
    // Replace it with your own parameters.
    char* host = "${YourHost}";
    char* sdkKey = "${YourSdkKey}";
    char* sdkSecret = "${YourSdkSecret}";
    InitSdk(host, sdkKey, sdkSecret);

    // Create the text program for the first section of the first episode.
    TextNode* text = createWithTextTextNode("huidu");
    ContentNode* contents1[] = { (ContentNode*)text };
    AreaNode* area1 = createAreaNodeWithContents(contents1, 1);
    setXAreaNode(area1, 0);
    setYAreaNode(area1, 0);
    setWidthAreaNode(area1, 128);
    setHeightAreaNode(area1, 32);
    
    // Create the video program for the second area of the first episode for HTTP download.
    VideoNode* video = createWithUrlFileSizeMd5VideoNode("https://persuasion.yingkeiot.cn/attachment/screen/2024-03-19/822091ba-f9e7-4096-8baa-318d785a60ef.mp4",
        33417203,
        "46318c4df4968f716061e5fc2ad22401");
    ContentNode* contents2[] = { (ContentNode*)video };
    AreaNode* area2 = createAreaNodeWithContents(contents2, 1);
    setXAreaNode(area2, 0);
    setYAreaNode(area2, 32);
    setWidthAreaNode(area2, 128);
    setHeightAreaNode(area2, 32);
    AreaNode* areas[] = { area1, area2 };
    ProgramNode* programNode1 = createProgramNodeWithAreas(areas, sizeof(areas) / sizeof(AreaNode*));

    // Add the program to the device.
    ProgramClient* programClient = createProgramClient();
    const char* devIds[] = { "C16L-D00-A000F" };
    ProgramNode* programNodes[] = { programNode1 };
    char* jsonResult = replaceProgramClient(programClient, devIds, 1, programNodes, sizeof(programNodes) / sizeof(ProgramNode*));
    
    // Release resources
    for (int i = 0; i < sizeof(programNodes) / sizeof(ProgramNode*); ++i) {
        destroyProgramNode(programNodes[i]);
    }
    
    destroyProgramClient(programClient);
	destroyConfig();

    // Print result
    printf("%s\n", jsonResult);

    system("pause");
}