#include "vrpn_client_ros/transform_fur_odom_to_flu.h"


TransformFurOdomToFlu::TransformFurOdomToFlu() :
  Node("transform_fur_odom_to_flu")
{
  // [init class attributes]

  // [declare parameters]
  configure_parameters();
  
  // [parameter callbacks and handlers]

  // [init publishers]
  pose_out_publisher_ = this->create_publisher<geometry_msgs::msg::PoseStamped>("pose_out", 1);

  // [init subscribers]
  pose_in_subscriber_ = this->create_subscription<geometry_msgs::msg::PoseStamped>("pose_in", 1, std::bind(&TransformFurOdomToFlu::pose_in_callback, this, std::placeholders::_1));

  // [init service servers]

  // [init service clients]

  // [init action servers]

  // [init action clients]

  tf_buffer_ =
      std::make_unique<tf2_ros::Buffer>(this->get_clock());
    tf_listener_ =
      std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

}

TransformFurOdomToFlu::~TransformFurOdomToFlu(void)
{
  // [free dynamic memory]
}

// [parameters functions]
void TransformFurOdomToFlu::configure_parameters(void)
{
  // [structural parameters]
  rcl_interfaces::msg::ParameterDescriptor descriptor;
  descriptor.description = "Robot name";
  descriptor.read_only = true;
  robot_name_ = this->declare_parameter<std::string>("robot_name", "solo12", descriptor);

  // [other parameters]

}

// [subscriber functions]
void TransformFurOdomToFlu::pose_in_callback(const geometry_msgs::msg::PoseStamped::ConstSharedPtr & msg)
{
  static bool tf_received = false;
  std::string from_robot = robot_name_ + "_fur_ot";
  std::string to_robot  = robot_name_ + "_flu_ot";
  tf2::Transform tf_world_fur_to_robot_fur;
  tf2::Transform tf_world_flu_to_robot_flu;
  if (!tf_received)
  {
    try {
      geometry_msgs::msg::TransformStamped t;
      t = tf_buffer_->lookupTransform("world_flu", "world_fur", tf2::TimePointZero);
      tf2::fromMsg(t.transform, world_fur_to_flu_);

      t = tf_buffer_->lookupTransform(to_robot, from_robot, tf2::TimePointZero);
      tf2::fromMsg(t.transform, robot_fur_to_flu_);

      tf_received = true;
      RCLCPP_INFO(this->get_logger(), "Transform from FUR to FLU received");
    } catch (const tf2::TransformException & ex) {
      RCLCPP_INFO(
        this->get_logger(), "Could not transform: %s",
        ex.what());
      return;
    }
  }
  if (tf_received)
  {
    // Transform pose from FUR ODOM to FLU
    tf2::fromMsg(msg->pose, tf_world_fur_to_robot_fur);

    tf_world_flu_to_robot_flu = world_fur_to_flu_.inverse()*tf_world_fur_to_robot_fur*robot_fur_to_flu_;

    geometry_msgs::msg::Transform tf_msg = tf2::toMsg(tf_world_flu_to_robot_flu);
    
    pose_out_msg_.header = msg->header;
    pose_out_msg_.pose.position.x = tf_msg.translation.x;
    pose_out_msg_.pose.position.y = tf_msg.translation.y;
    pose_out_msg_.pose.position.z = tf_msg.translation.z;
    pose_out_msg_.pose.orientation = tf_msg.rotation;

    // Publish transformed pose
    pose_out_publisher_->publish(pose_out_msg_);
  }
}

// [service server functions]

// [action server functions]

// [action client functions]

/////////// Main ///////////
int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<TransformFurOdomToFlu>();
  rclcpp::executors::SingleThreadedExecutor single_exec;
  single_exec.add_node(node);

  single_exec.spin();
  
  rclcpp::shutdown();
  return 0;
}