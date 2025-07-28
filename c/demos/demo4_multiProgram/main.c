#include <stdio.h>
#include "TextNode.h"
#include "ImageNode.h"
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
    setHeightAreaNode(area1, 64);
    ProgramNode* programNode1 = createProgramNodeWithArea(area1);

    // Create the image program for the first area of the second show for HTTP download.
    ImageNode* image = createWithUrlFileSizeMd5ImageNode("https://persuasion.yingkeiot.cn/attachment/violations/11/2024-06-03/80602000-58c6-43b5-adc9-b072ec04c792.jpg",
        337460,
        "498c7bbab17011a3d257cf0468bcff08");
    ContentNode* contents2[] = { (ContentNode*)image };
    AreaNode* area2 = createAreaNodeWithContents(contents2, 1);
    setXAreaNode(area2, 0);
    setYAreaNode(area2, 0);
    setWidthAreaNode(area2, 128);
    setHeightAreaNode(area2, 64);
    ProgramNode* programNode2 = createProgramNodeWithArea(area2);

    // Add the program to the device.
    ProgramClient* programClient = createProgramClient();
    const char* devIds[] = { "C16L-D00-A000F" };
    ProgramNode* programNodes[] = { programNode1 , programNode2 };
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