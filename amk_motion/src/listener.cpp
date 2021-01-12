#include "ros/ros.h"    //"ros/ros.h"包含ROS节点所有节点的必要文件
// #include "std_msgs/String.h"    //"std_msgs/String.h"包含消息类型
#include <geometry_msgs/Twist.h>

void chatterCallback(geometry_msgs::Twist vel_msg)  
{  
  ROS_INFO("Publsh amk velocity command[%0.2f m/s, %0.2f rad/s]", vel_msg.linear.x, vel_msg.angular.z);  
}  

int main(int argc, char **argv)  
{
    ros::init(argc, argv, "listener");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("/amk/cmd_vel", 1000, chatterCallback);
    ros::spin();
    return 0;
}