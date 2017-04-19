#include<ros/ros.h>
#include<stdio.h>
#include<sensor_msgs/LaserScan.h>
#include<tf/transform_broadcaster.h>
#include<maidbot_laser/Position.h>


class Robot
{
    public:
        Robot();
        ~Robot();
        void run();

    private:
        ros::NodeHandle n_;
        void generateScan();
        void sendTransforms();
        void poseCb(const maidbot_laser::Position::ConstPtr &msg);
        std::array<float,359> scan_array_;
        sensor_msgs::LaserScan scan_;
        tf::Transform transform_;
        tf::TransformBroadcaster base_frame_broadcaster_;
        ros::Publisher scan_pub_ = n_.advertise<sensor_msgs::LaserScan>("scan",1000);
        ros::Subscriber pos_sub_ = n_.subscribe<maidbot_laser::Position>("pose",1000,&Robot::poseCb,this);
};

