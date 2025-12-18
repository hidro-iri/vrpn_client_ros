from launch_ros.actions import Node

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution, TextSubstitution
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    yaml_path_arg = DeclareLaunchArgument(
        'yaml_path', 
        description="Path of the yaml file with VRPN client parameters",
        default_value=PathJoinSubstitution([
            FindPackageShare('vrpn_client_ros'),
            'config',
            'sample.params.yaml'
        ]),
    )

    robot_name_arg = DeclareLaunchArgument(
        'robot_name', default_value=TextSubstitution(text='solo12')
    )

    remappings = [(['/', LaunchConfiguration('robot_name'), 'fur_ot/pose'], ['/optitrack/', LaunchConfiguration('robot_name'), 'fur_ot/pose'])]

    vrpn_client_node = Node(package='vrpn_client_ros',
                            executable='vrpn_client_node',
                            output='screen',
                            emulate_tty=True,
                            parameters=[LaunchConfiguration('yaml_path')],
                            remappings=remappings)

    ld = LaunchDescription()

    ld.add_action(yaml_path_arg)
    ld.add_action(robot_name_arg)
    ld.add_action(vrpn_client_node)

    return ld