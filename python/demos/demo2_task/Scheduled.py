from sdk.common.Config import Config
from sdk.deviceTask.ScheduledTask import ScheduledTask
from sdk.data.task.ScheduledTaskInfo import ScheduledTaskInfo
import json

def main():
    # with your own parameters
    # host = "${YourHost}"
    # sdk_key = "${YourSdkKey}"
    # sdk_secret = "${YourSdkSecret}"
    # Config.init_sdk(host, sdk_key, sdk_secret)

    # Instantiate task interface objects
    scheduled_task = ScheduledTask()

    # Prepare the task configuration
    task_info = ScheduledTaskInfo()
    task_info.time_range = "06:00:00~19:00:01"  # Set the time frame

    task_infos = {
        "screen": [task_info]  # The task force is called "screen"
    }

    result = scheduled_task.set_scheduled_task("C16L-D00-A000F", task_infos)
    print("Scheduled task setting results:")
    print(json.dumps(result, indent=2))

if __name__ == "__main__":
    main()
