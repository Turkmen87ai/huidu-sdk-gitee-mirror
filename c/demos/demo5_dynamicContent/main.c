#include <stdio.h>
#include "DynamicNode.h"
#include "AreaNode.h"
#include "ProgramNode.h"
#include "Config.h"
#include "Program.h"
#include "ContentNode.h"
#include "PushStatusTask.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

int main() {
    // Replace it with your own parameters.
    char* host = "${YourHost}";
    char* sdkKey = "${YourSdkKey}";
    char* sdkSecret = "${YourSdkSecret}";
    InitSdk(host, sdkKey, sdkSecret);

    DynamicNode* dynamic = createDynamicNodeWithText("parking:{{parkingSpace}}<br>temp:{{temperature}}", "parkingSpace,temperature");

    ContentNode* contents[] = { (ContentNode*)dynamic };
    AreaNode* area = createAreaNodeWithContents(contents, sizeof(contents) / sizeof(ContentNode*));
    setXAreaNode(area, 0);
    setYAreaNode(area, 0);
    setWidthAreaNode(area, 128);
    setHeightAreaNode(area, 64);

    ProgramNode* programNode = createProgramNodeWithArea(area);

    ProgramClient* programClient = createProgramClient();
    const char* devIds[] = { "C16L-D00-A000F" };
    char* jsonResult = replaceSingleProgramClient(programClient, devIds, sizeof(devIds) / sizeof(char*), programNode);
    
    destroyProgramNode(programNode);
    destroyProgramClient(programClient);

    printf("%s\n", jsonResult);

    PushStatusTask *pushStatusTask = createPushStatusTask();
    for (int count = 600; count >= 0; count--) {
        char strTemp[25];
        snprintf(strTemp, sizeof(strTemp), "%d", count);
        char* jsonResult = pushStatusSingle(pushStatusTask, "C16L-D00-A000F", "parkingSpace", strTemp);
        printf("%s\n", jsonResult);
        free(jsonResult);
		
#ifdef _WIN32
        Sleep(1 * 1000);  // Windows Use milliseconds.
#else
        sleep(1);         // Linux Use seconds.
#endif

        if (count % 100 == 0) {
            int temp = 25 + (6 - count / 100);
            memset(strTemp, 0, sizeof(strTemp));
			snprintf(strTemp, sizeof(strTemp), "%d", temp);
            jsonResult = pushStatusSingle(pushStatusTask, "C16L-D00-A000F", "temperature", strTemp);
            printf("%s\n", jsonResult);
            free(jsonResult);
        }
    }
    destroyPushStatusTask(pushStatusTask);
	destroyConfig();

    system("pause");
}