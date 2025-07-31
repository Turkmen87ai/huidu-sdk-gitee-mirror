import time
import json
from sdk.deviceTask.PushStatusTask import PushStatusTask
from sdk.common.Config import Config
from sdk.data.ProgramNode import ProgramNode
from sdk.data.area.DynamicNode import DynamicNode
from sdk.Program import Program

def main():
    # with your own parameters
    # host = "${YourHost}"
    # sdk_key = "${YourSdkKey}"
    # sdk_secret = "${YourSdkSecret}"
    # Config.init_sdk(host, sdk_key, sdk_secret)

    text_node = DynamicNode("当前的温度:{{temperature}}<br>剩余车位:{{parkingSpace}}", "temperature,parkingSpace")
    program_node = ProgramNode([text_node])

    # Instantiate program interfaces
    program = Program()

    # Add shows to devices
    device_ids = ["C16L-D00-A000F"]
    result = program.replace(device_ids, program_node)

    print("API Respond to the results:")
    print(json.dumps(result, indent=2))

    pusher = PushStatusTask()

    # Initial reset
    print("Resetting to initial state...")
    reset_values = {
        "temperature": "0",
        "parkingSpace": "0"
    }
    result = pusher.push_status("", reset_values)
    print("Reset result:", result)

    # Wait 3 seconds
    time.sleep(3)

    # Bulk update
    print("Updating to normal values...")
    update_values = {
        "temperature": "25",
        "parkingSpace": "666"
    }
    result = pusher.push_status(device_ids, update_values)
    print("Update result:", result)

    # Countdown simulation
    print("Starting countdown simulation...")
    try:
        for count in range(600, -1, -1):
            # Update parking space count
            result = pusher.push_status(device_ids, "parkingSpace", str(count))
            print(f"Countdown: {count} - Result: {result}")

            # Update temperature every 100 counts
            if count % 100 == 0:
                temp = 25 + (6 - count // 100)
                result = pusher.push_status(device_ids, "temperature", str(temp))
                print(f"Temperature update: {temp}°C - Result: {result}")

            time.sleep(1)

    except KeyboardInterrupt:
        print("\nCountdown interrupted by user")
    finally:
        print("Countdown simulation completed")

if __name__ == "__main__":
    main()
