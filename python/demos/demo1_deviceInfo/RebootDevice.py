from sdk.common.Config import Config
from sdk.Device import Device
import json

def main():
    # with your own parameters
    # host = "${YourHost}"
    # sdk_key = "${YourSdkKey}"
    # sdk_secret = "${YourSdkSecret}"
    # Config.init_sdk(host, sdk_key, sdk_secret)

    host = "http://192.168.90.153:30080"
    sdk_key = "a7fa6795aaa891e2"
    sdk_secret = "696b35024ea5c2ba0db2876663254a78"
    Config.init_sdk(host, sdk_key, sdk_secret)

    # Instantiate a device interface object
    device = Device()

    # Device reboot
    device_id = ["C16L-D00-A000F"]
    result = device.device(device_id, "rebootDevice")

    # Print the result
    print("API Respond to the results:")
    print(json.dumps(result, indent=2))

if __name__ == "__main__":
    main()
