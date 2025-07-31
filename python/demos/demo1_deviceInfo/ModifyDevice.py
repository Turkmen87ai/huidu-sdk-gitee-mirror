from sdk.common.Config import Config
from sdk.Device import Device
import json

def main():
    # with your own parameters
    # host = "${YourHost}"
    # sdk_key = "${YourSdkKey}"
    # sdk_secret = "${YourSdkSecret}"
    # Config.init_sdk(host, sdk_key, sdk_secret)

    # Instantiate a device interface object
    device = Device()

    # Set the device name
    # result = device.set_device_name("C16L-D00-A000F", "coffee")
    # Get the device name
    result = device.get_device_property("C16L-D00-A000F", "name")

    # Print the result
    print("API Respond to the results:")
    print(json.dumps(result, indent=2))

if __name__ == "__main__":
    main()
