#include"laser_node.h"

// Robot::Robot(ros::NodeHandle n):n(n){}
Robot::Robot(){}

Robot::~Robot(){}

// generate and publish laser scan data on the scan topic
void Robot::generateScan()
{
    scan_.header.stamp = ros::Time::now();
    scan_.header.frame_id = "laser_frame";
    scan_.angle_min = -3.12414;
    scan_.angle_max = 3.14159265359;
    scan_.angle_increment = 0.0174533;
    scan_.time_increment = 0;
    scan_.scan_time = 0;
    scan_.range_min = 0;
    scan_.range_max = 5;

    scan_array_.fill(2.0);
    scan_.ranges.resize(359);
    // populate the msg with the values.Here the values are the same,so they form a circle
    for(int i = 0 ; i < 359 ; i ++)
    {
        scan_.ranges[i] = scan_array_[i];
    }

    scan_pub_.publish(scan_);
}

// Call back for the position subscriber.Uses the position data to transform the robot's base frame
void Robot::poseCb(const maidbot_laser::Position::ConstPtr &msg)
{
      transform_.setOrigin( tf::Vector3(msg->x, msg->y, 0.0) );
      tf::Quaternion q;
      q.setRPY(0, 0, msg->angle);
      transform_.setRotation(q);
      base_frame_broadcaster_.sendTransform(tf::StampedTransform(transform_, ros::Time::now(), "map", "base_link"));
}

void Robot::run()
{
    generateScan();
}

int main(int argc,char** argv)
{
    ros::init(argc,argv,"laser_node");
    // ros::NodeHandle nh;
    // Robot robot = Robot(nh);
    Robot robot = Robot();
    ros::Rate rate(10);
    while(ros::ok())
    {
        ros::spinOnce();
        robot.run();
        rate.sleep();
    }
}