#include<ros/ros.h>
#include<maidbot_laser/Position.h>
#include<math.h>
#include<stdio.h>


int main(int argc,char** argv)
{
    ros::init(argc,argv,"send_pose");
    ros::NodeHandle n;
    ros::Publisher pose_pub = n.advertise<maidbot_laser::Position>("pose",1000);
    maidbot_laser::Position pose_msg;
    float theta = 0;
    float increment = 0.0174533;
    float radius = 2;
    // running the node at 10 hz
    ros::Rate rate(10);
    while(ros::ok())
    {
        // making the robot move in a circle of given radius
        pose_msg.x = radius*cos(theta);
        pose_msg.y = radius*sin(theta);
        pose_msg.angle = theta;
        pose_pub.publish(pose_msg);
        theta = theta+increment;
        // resetting theta to zero once it gets over 360 deg
        if(theta > 6.282)
        {
            theta = 0;
        }
        ros::spinOnce();
        rate.sleep();
    }
}