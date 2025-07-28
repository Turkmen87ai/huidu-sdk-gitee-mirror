#include <stdio.h>
#include "Config.h"
#include "ScheduledTask.h"
#include "ScheduledTaskInfo.h"

int main() {
    // Replace it with your own parameters.
    char* host = "${YourHost}";
    char* sdkKey = "${YourSdkKey}";
    char* sdkSecret = "${YourSdkSecret}";
    InitSdk(host, sdkKey, sdkSecret);

    // Instantiate the interface object.
    ScheduledTask* scheduledTask = createScheduledTask();   
    
    const char* keys[] = { "screen" };
    int keyCount = sizeof(keys) / sizeof(keys[0]);

    ScheduledTaskInfo*** taskInfos = (ScheduledTaskInfo***)hdmalloc(keyCount * sizeof(ScheduledTaskInfo**));
    int* taskInfoCounts = (int*)hdmalloc(keyCount * sizeof(int));
    for (int i = 0; i < keyCount; i++) {
        // Create a task array for each key (for example, the weekday has 2 tasks, and the weekend has 1 task).
        taskInfoCounts[i] = (i == 0) ? 2 : 1; // weekday:2, weekend:1
        taskInfos[i] = (ScheduledTaskInfo**)hdmalloc(taskInfoCounts[i] * sizeof(ScheduledTaskInfo*));

        // Fill in the task data.
        for (int j = 0; j < taskInfoCounts[i]; j++) {
            taskInfos[i][j] = createScheduledTaskInfo();

            // Set the task attributes (according to actual requirements).
            if (i == 0) { // weekday
                if (j == 0) {
                    setTimeRangeScheduledTaskInfo(taskInfos[i][j], "08:00:00~12:00:00");
                    setWeekFilterScheduledTaskInfo(taskInfos[i][j], "Mon,Tue,Wed,Thu,Fri");
                    setDataScheduledTaskInfo(taskInfos[i][j], "true");
                }
                else {
                    setTimeRangeScheduledTaskInfo(taskInfos[i][j], "13:00:00~17:00:00");
                    setWeekFilterScheduledTaskInfo(taskInfos[i][j], "Mon,Tue,Wed,Thu,Fri");
                    setDataScheduledTaskInfo(taskInfos[i][j], "true");
                }
            }
            else { // weekend
                setTimeRangeScheduledTaskInfo(taskInfos[i][j], "09:00:00~18:00:00");
                setWeekFilterScheduledTaskInfo(taskInfos[i][j], "Sat,Sun");
                setDataScheduledTaskInfo(taskInfos[i][j], "true");
            }
        }
    }

    char* jsonResult = setScheduledTaskSingle(scheduledTask, "C16L-D00-A000F", keys, taskInfos, taskInfoCounts, 1);

    // Print result
    printf("%s\n", jsonResult);

    // Clear resources
    for (int i = 0; i < keyCount; i++) {
        for (int j = 0; j < taskInfoCounts[i]; j++) {
            destroyScheduledTaskInfo(taskInfos[i][j]);
        }
        hdfree(taskInfos[i]);
    }
    hdfree(taskInfos);
    hdfree(taskInfoCounts);
    hdfree(jsonResult);
    destroyScheduledTask(scheduledTask);

    system("pause");
}