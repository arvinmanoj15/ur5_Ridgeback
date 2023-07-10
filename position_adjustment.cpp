#include <ros/ros.h>
#include <std_msgs/Float64MultiArray.h>
#include <geometry_msgs/Twist.h>

ros::Publisher velocity_pub;
ros::Subscriber object_position_sub;

void objectPositionCallback(const std_msgs::Float64MultiArray::ConstPtr& msg)
{
    if (msg->data.size() >= 3)
    {
        double x = msg->data[0];
        double y = msg->data[1];
        double z = msg->data[2];
        //std::cout << "Here ... !!"<< std::endl;
        
        if (x >= 330)
        {
            //std::cout << "Cooking...!!"<< std::endl;
            geometry_msgs::Twist velocity_cmd;
            velocity_cmd.linear.x = 0.1;
            velocity_pub.publish(velocity_cmd);
        }
        else
        {
            // Shutdown the subscriber and ROS node
            object_position_sub.shutdown();
            ros::shutdown();
        }
    }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "transformed_object_subscriber");
    ros::NodeHandle nh;

    velocity_pub = nh.advertise<geometry_msgs::Twist>("/ridgeback_velocity_controller/cmd_vel", 10);
    object_position_sub = nh.subscribe("/transformed_object_position", 10, objectPositionCallback);

    ros::spin();

    return 0;
}
