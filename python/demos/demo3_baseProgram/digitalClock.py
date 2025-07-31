from sdk.common.Config import Config
from sdk.data.ProgramNode import ProgramNode
from sdk.Program import Program
from sdk.data.area.DigitalClockNode import DigitalClockNode
import json

def main():
    # with your own parameters
    # host = "${YourHost}"
    # sdk_key = "${YourSdkKey}"
    # sdk_secret = "${YourSdkSecret}"
    # Config.init_sdk(host, sdk_key, sdk_secret)

    # Build program data nodes
    digitalClock_node = DigitalClockNode()
    program_node = ProgramNode([digitalClock_node])

    # Instantiate program interfaces
    program = Program()

    # Add shows to devices
    device_ids = ["C16L-D00-A000F"]
    result = program.replace(device_ids, program_node)

    print("API Respond to the results:")
    print(json.dumps(result, indent=2))

if __name__ == "__main__":
    main()
