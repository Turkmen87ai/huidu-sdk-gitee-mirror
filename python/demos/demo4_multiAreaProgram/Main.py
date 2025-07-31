from sdk.common.Config import Config
from sdk.data.ProgramNode import ProgramNode
from sdk.Program import Program
from sdk.data.area.TextNode import TextNode
from sdk.data.area.ImageNode import ImageNode
from sdk.data.area.AreaNode import AreaNode
import json

def main():
    # with your own parameters
    # host = "${YourHost}"
    # sdk_key = "${YourSdkKey}"
    # sdk_secret = "${YourSdkSecret}"
    # Config.init_sdk(host, sdk_key, sdk_secret)

    text_node = TextNode("第一个节目")
    text_node.set_valignment(TextNode.VAlignment.MIDDLE)
    nodes1 = [
        text_node
    ]
    # Build the first program node
    program1 = ProgramNode(nodes1)
    program1.uuid = "program1"
    program1.set_name("p1")

    area1_nodes = [
        TextNode("第二个节目")
    ]
    area1 = AreaNode()
    area1.set_x(0)
    area1.set_y(0)
    area1.set_width(128)
    area1.set_height(64)
    area1.set_item(area1_nodes)
    area1.uuid = "area1"
    area1.set_name("a1")

    image_path = "E:/Desktop/1b35.jpg"
    area2_nodes = [
        ImageNode(image_path)
    ]
    area2 = AreaNode()
    area2.set_x(0)
    area2.set_y(0)
    area2.set_width(128)
    area2.set_height(64)
    area2.set_item(area2_nodes)
    area2.uuid = "area2"
    area2.set_name("a2")

    # Build a second program node
    program2 = ProgramNode([area2, area1])
    program2.uuid = "program2"
    program2.set_name("p2")

    # Instantiate program interfaces
    program = Program()

    # Add shows to devices
    device_ids = ["C16L-D00-A000F"]
    result = program.replace(device_ids, [program1, program2])

    print("API Respond to the results:")
    print(json.dumps(result, indent=2))

if __name__ == "__main__":
    main()
