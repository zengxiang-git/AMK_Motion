// 发布turtle1/cmd_vel话题，消息类型geometry_msgs::Twist
#include "ros/ros.h"
// #include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
// #include <sstream>

int main(int argc, char **argv)
{
    // ros::init(argc, argv, "talker");
    ros::init(argc, argv, "talker");

    ros::NodeHandle n;

    // ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
    ros::Publisher amk_vel_pub = n.advertise<geometry_msgs::Twist>("/amk/cmd_vel", 10);

    ros::Rate loop_rate(10);    // 以 10Hz 的频率运行
    // int count = 0;
    while (ros::ok())
    {
        // std_msgs::String msg;
        // std::stringstream ss;
        // ss << "hello world " << count;
        // msg.data = ss.str();
        // ROS_INFO("%s", msg.data.c_str());
        // chatter_pub.publish(msg);

        // 初始化geometry_msgs::Twist类型的消息,封装数据
		geometry_msgs::Twist vel_msg;  //创建类的对象，包含成员线速度和角速度
		vel_msg.linear.x = 0.5;
		vel_msg.angular.z = 0.2;
	    // 发布消息，amk_vel_pub为创建的Publisher，发送创建的包含线速度角速度的类消息
	    // 通过底层的一系列通讯机制，把数据压入堆栈，队列通过以太网ROS_Topic的TCP通讯机制发出去
		amk_vel_pub.publish(vel_msg);
		ROS_INFO("Publsh amk velocity command[%0.2f m/s, %0.2f rad/s]", 
				vel_msg.linear.x, vel_msg.angular.z);
        // 在这个例子中并不是一定要调用 ros::spinOnce()，因为不接受回调。然而，如果程序里包含其他回调函数，
        // 最好在这里加上 ros::spinOnce()这一语句，否则回调函数就永远也不会被调用了。
        ros::spinOnce();
        loop_rate.sleep();
        // ++count;
    }
    return 0;  
}