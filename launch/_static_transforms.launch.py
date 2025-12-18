import math

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition, UnlessCondition
from launch.substitutions import PathJoinSubstitution, LaunchConfiguration, TextSubstitution

from launch_ros.actions import Node


def generate_launch_description():
    ld = LaunchDescription()

    # simulation_arg = DeclareLaunchArgument('simulation', description='Run simulation', default_value='True')
    # ld.add_action(simulation_arg)

    robot_name_arg = DeclareLaunchArgument(
        'robot_name', default_value=TextSubstitution(text='solo12')
    )
    ld.add_action(robot_name_arg)

    st_w_wo = Node(package="tf2_ros",
                   executable="static_transform_publisher",
                   arguments=["0", "0", "0", "0", "0",
                              str(math.pi / 2), "world_flu", "world_fur"],
                #    condition=UnlessCondition(LaunchConfiguration("simulation"))
    )
    ld.add_action(st_w_wo)

    st_w_wp = Node(package="tf2_ros",
                   executable="static_transform_publisher",
                   arguments=["0", "0", "0", "0", "0", str(math.pi), "world_flu", "world_frd"])
    ld.add_action(st_w_wp)

    st_robot_fur_flu = Node(
        package="tf2_ros",
        executable="static_transform_publisher",
        arguments=["0", "0", "0", "0", "0",
                   str(-math.pi / 2), [LaunchConfiguration('robot_name'), '_fur_ot'], [LaunchConfiguration('robot_name'), '_flu_ot']],
        # condition=UnlessCondition(LaunchConfiguration("simulation"))
    )
    ld.add_action(st_robot_fur_flu)

    st_robot_flu_frd = Node(package="tf2_ros",
                              executable="static_transform_publisher",
                              arguments=["0", "0", "0", "0", "0",
                                         str(math.pi), [LaunchConfiguration('robot_name'), '_flu_ot'], [LaunchConfiguration('robot_name'), '_frd_ot']],
                            #   condition=UnlessCondition(LaunchConfiguration("simulation"))
    )
    ld.add_action(st_robot_flu_frd)

    return ld