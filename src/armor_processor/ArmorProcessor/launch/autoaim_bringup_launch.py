from launch import LaunchDescription
from launch_ros.actions import Node
camera_id= 3 # 0:USB,1:Daheng,2:Mindvision,3:Haikang
serial=True 
def generate_launch_description():
    ld = LaunchDescription()
    #像机选取
    if camera_id==0:
        camera = Node(
            package='usb_camera',
            executable='usb_camera_node',
            name='camera'
        )
    if camera_id==1:
        camera = Node(
            package='daheng_camera',
            executable='daheng_camera_node',
            name='camera'
        )
    if camera_id==2:
        camera = Node(
            package='mindvision_camera',
            executable='mindvision_camera_node',
            name='camera'
        )
    if camera_id==3:
        camera = Node(
            package='Haikang_camera',
            executable='Haikang_camera_node',
            name='camera'
        )
    ld.add_action(camera)
    #其余节点
    node2 = Node(
        package='armor_detector',
        executable='armor_detector_node',
        name='detector'
    )
    ld.add_action(node2)
    # 添加节点1
    node3 = Node(
        package='armor_processor',
        executable='armor_processor_node',
        name='processor',
    )
    ld.add_action(node3)
    node4 = Node(
        package='rm_serial_port',
        executable='rm_serial_port_node',
        name='serial'
    )

    ld.add_action(node4)
    return ld