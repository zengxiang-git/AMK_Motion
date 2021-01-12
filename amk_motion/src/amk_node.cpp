/**
 * @file amk_node.cpp
 * @author ZX (1476600177@qq.com)
 * @brief 安防机器人（AMK）底盘运动控制节点程序
 * @version 0.1
 * @date 2021-01-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "ros/ros.h"
#include <geometry_msgs/Twist.h>
#include "amk_motion/CanMessage.h"

CanMessage canmsg;


void amkControllCallback(const geometry_msgs::Twist msg)
{
    ROS_INFO("Publsh amk velocity command[%0.2f m/s, %0.2f rad/s]", msg.linear.x, msg.angular.z);
    // canmsg.SetAimSpd(msg.linear.x, msg.angular.z);
}

int main(int argc, char **argv)
{
    // init ros
    ros::init(argc, argv, "amk_node");

    ros::NodeHandle nh;
    ros::Publisher amk_state_pub = nh.advertise<geometry_msgs::Twist>("/amk/state", 10);
    ros::Subscriber amk_control_sub = nh.subscribe<geometry_msgs::Twist>("/cmd_vel", 10, amkControllCallback);

    // init canMessage
    canmsg.OpenDevice();
    canmsg.EnableNodes(true);
    canmsg.SetAimSpd(1.0, 0);

    // run
    ros::spin();
    return 0;
}