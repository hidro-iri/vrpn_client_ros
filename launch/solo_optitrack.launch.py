from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution, TextSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch.launch_description_sources import PythonLaunchDescriptionSource

def generate_launch_description():
  ld = LaunchDescription()

  vrpn_config_file_arg = DeclareLaunchArgument(
    'vrpn_config_file', 
    default_value=PathJoinSubstitution([
      FindPackageShare('vrpn_client_ros'),
      'config',
      'sample.params.yaml'
    ]),
  )

  robot_name_arg = DeclareLaunchArgument(
    'robot_name', default_value=TextSubstitution(text='solo12')
  )

  simulation_arg = DeclareLaunchArgument('simulation', description='Run simulation', default_value='True')
  
  output_arg = DeclareLaunchArgument(
    'output', default_value=TextSubstitution(text='screen')
  )
  launch_prefix_arg = DeclareLaunchArgument(
    'launch_prefix', default_value=TextSubstitution(text='')
  )

  # Uncomment to add ros interfaces remappings
  # ros_interface_name_ns_arg = DeclareLaunchArgument(
  #   'ros_interface_name_ns', default_value=TextSubstitution(text='ros_interface_name')
  # )

  vrpn_launch = IncludeLaunchDescription(
    PythonLaunchDescriptionSource(
      PathJoinSubstitution([
        FindPackageShare('vrpn_client_ros'),
        'launch',
        '_vrpn_client.launch.py'
      ])
    ),
    launch_arguments={
      'yaml_path': LaunchConfiguration('vrpn_config_file'),
      'robot_name': LaunchConfiguration('robot_name'),
    }.items(),
  )

  static_transforms_launch = IncludeLaunchDescription(
    PythonLaunchDescriptionSource(
      PathJoinSubstitution([
        FindPackageShare('vrpn_client_ros'),
        'launch',
        '_static_transforms.launch.py'
      ])
    ),
    launch_arguments={
      'robot_name': LaunchConfiguration('robot_name'),
      'simulation': TextSubstitution(text='False'),
    }.items(),
  )

  ld.add_action(vrpn_config_file_arg)
  ld.add_action(robot_name_arg)
  ld.add_action(simulation_arg)
  ld.add_action(output_arg)
  ld.add_action(launch_prefix_arg)
  # ld.add_action(ros_interface_name_ns_arg) 
  ld.add_action(vrpn_launch)
  ld.add_action(static_transforms_launch)

  return ld
