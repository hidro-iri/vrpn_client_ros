// Copyright (C) 2025 Institut de Robotica i Informatica Industrial, CSIC-UPC.
// Author: TODO: Your name
// Maintainer: labroboticamobil@iri.upc.edu
// All rights reserved.
//
// TODO: Update to the license that we are going to use (Apache 2.0??).
// TODO: Update ros scripts link.
//
// This file is part of iri-ros-pkg
// iri-ros-pkg is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// 
// IMPORTANT NOTE: This code has been generated through a script from the 
// iri_ros_scripts. Please do NOT delete any comments to guarantee the correctness
// of the scripts. ROS topics can be easily add by using those scripts. Please
// refer to the IRI ros scripts main page for more information:
// https://gitlab.iri.upc.edu/labrobotica/ros/iri_core/iri_ros_scripts

#ifndef _IRI_TRANSFORM_FUR_ODOM_TO_FLU_H
#define _IRI_TRANSFORM_FUR_ODOM_TO_FLU_H

// [ROS headers]
#include <rclcpp/rclcpp.hpp>

#include "rclcpp/rclcpp.hpp"
#include "tf2/exceptions.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include <tf2/transform_datatypes.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

// [msg headers]
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>

// [service headers]

// [action headers]

// [other headers]
#include <chrono>
#include <functional>
#include <memory>


/**
 * \class TransformFurOdomToFlu
 * \brief A template with IRI's ROS2 node desired structure.
 */
class TransformFurOdomToFlu : public rclcpp::Node
{
  private:

    // [structural arguments]
    std::string robot_name_; ///< Robot name
    tf2::Transform world_fur_to_flu_; ///< Transform from world to FLU
    tf2::Transform robot_fur_to_flu_; ///< Transform from robot to FLU
    std::unique_ptr<tf2_ros::Buffer> tf_buffer_; ///< TF2 buffer
    std::shared_ptr<tf2_ros::TransformListener> tf_listener_; ///< TF2

    // [parameters handlers]

    // [publisher attributes]
    rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr pose_out_publisher_; ///< Publisher for the topic.
    geometry_msgs::msg::PoseStamped pose_out_msg_; ///< Message to be published.

    // [subscriber attributes]
    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr pose_in_subscriber_; ///< Subscriber for the pose_in topic.

    // [service server attributes]

    // [service client attributes]

    // [action server attributes]

    // [action client attributes]



    // [structural functions]

    // [parameters functions]
    /**
     * \brief Function to declare and configure the parameters and its handlers.
     */
    void configure_parameters(void);

    // [subscriber functions]
    /**
     * \brief Callback function for chatter topic' subscriber.
     * 
     * This function is called when a message is received on the chatter topic.
     * 
     * \param msg The received message.
     */
    void pose_in_callback(const geometry_msgs::msg::PoseStamped::ConstSharedPtr & msg);


    // [service server functions]

    // [service client functions]

    // [action server functions]

    // [action client functions]

  public:
    /**
     * \brief Constructor for the TransformFurOdomToFlu class.
     * 
     * This constructor initializes the node and sets up the timer.
     */
    TransformFurOdomToFlu(void);

    /**
     * \brief Destructor for the TransformFurOdomToFlu class.
     */
    ~TransformFurOdomToFlu(void);

    // [structural public functions]
  
  protected:
};

#endif // _IRI_TRANSFORM_FUR_ODOM_TO_FLU_H