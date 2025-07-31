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

    # Call the interface to get the online device
    result = device.get_device_property(ids="C16L-D00-A000F")

    # Print the result
    print("API Respond to the results:")
    print(json.dumps(result, indent=2))

if __name__ == "__main__":
    main()
