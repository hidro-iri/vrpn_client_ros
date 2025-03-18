# vrpn_client_ros

> :warning: Use ros2 branch: tested and approved on ros2 galactic :stars:

`vrpn_client_ros` is a ROS2 package that provides a interface for the Virtual-Reality Peripheral Network (VRPN) library. This package allows users to easily connect to VRPN servers and receive tracking and other data from a variety of devices such as motion trackers, joysticks, and haptic devices.

## Installation

To install `vrpn_client_ros`, you can clone the repository into your workspace and build it using colcon:

```console
cd <path/to/ws>/src
git clone https://github.com/hidro-iri/vrpn_client_ros.git
cd ..
colcon build --packages-select vrpn_client_ros
```

## Usage

`vrpn_client_ros` provides a `vrpn_client_node` executable that can be launched to connect to a VRPN server and receive tracking data from a device. The node subscribes to a topic called `/<device_name>/pose` and publishes the latest pose data for the device on that topic.

To use the `vrpn_client_node`, you can launch it with the appropriate configuration. For example, to connect to a VRPN server running on `localhost`, you can run:

```bash
ros2 run vrpn_client_ros vrpn_client_node --ros-args --params-file <path/to/config.yaml>
```

where `config.yaml` contains:

```yaml
vrpn_client_node:
  ros__parameters:
    server: localhost
    frame_id: "world"
    use_server_time: false
    broadcast_tf: true
    refresh_tracker_frequency: 0.2
    update_frequency: 120.0
```

## Configuration

The `vrpn_client_node` can be configured using a YAML file passed as a command-line argument. The configuration file specifies the VRPN server to connect to.

## Launch files

The package provides a launch file `sample.launch.py` that demonstrates how to launch the `vrpn_client_node` with a configuration file.

## Nodes

The package provides a single node, `vrpn_client_node`, that connects to a VRPN server and publishes pose data for devices.

## Topics

The `vrpn_client_node` subscribes to a topic for each device specified in the configuration file. The topic name is in the format `/<device_name>/pose`, where `<device_name>` is the name of the device as specified in the configuration file.

## Services

The package does not provide any services.
