#include<ros/ros.h>
#include<stdio.h>
#include<sensor_msgs/LaserScan.h>
#include<tf/transform_broadcaster.h>
#include<maidbot_laser/position.h>


class Robot
{
    public:
        Robot(ros::NodeHandle n);
        ~Robot();
        void run();
        ros::NodeHandle n;

    
    private:
        // update_pose();
        void generate_scan();
        void send_transforms();
        void pose_cb(const maidbot_laser::position::ConstPtr &msg);
        std::array<float,359> ar;
        sensor_msgs::LaserScan scan;
        tf::Transform transform;
        tf::TransformBroadcaster br;
        ros::Publisher scan_pub = n.advertise<sensor_msgs::LaserScan>("scan",1000);
        ros::Subscriber pos_sub = n.subscribe<maidbot_laser::position>("pose",1000,&Robot::pose_cb,this);
};


Robot::Robot(ros::NodeHandle n):n(n){}

Robot::~Robot(){}

void Robot::generate_scan()
{
    this -> scan.header.stamp = ros::Time::now();
    this -> scan.header.frame_id = "laser_frame";
    this -> scan.angle_min = -3.12414;
    this -> scan.angle_max = 3.14159265359;
    this -> scan.angle_increment = 0.0174533;
    this -> scan.time_increment = 0;
    this -> scan.scan_time = 0;
    this -> scan.range_min = 0;
    this -> scan.range_max = 5;

    this -> ar.fill(2.0);
    ROS_INFO("filling in scan values");
    this -> scan.ranges.resize(359);

    for(int i = 0 ; i < 359 ; i ++)
    {
        this -> scan.ranges[i] = this->ar[i];
    }

    this -> scan_pub.publish(this->scan);
    ROS_INFO("scans sent");

}

void Robot::pose_cb(const maidbot_laser::position::ConstPtr &msg)
{
      this -> transform.setOrigin( tf::Vector3(msg->x, msg->y, 0.0) );
      tf::Quaternion q;
      q.setRPY(0, 0, msg->angle);
      this -> transform.setRotation(q);
      this -> br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", "base_frame"));
      ROS_INFO("transform published");
}

void Robot::run()
{
    this->generate_scan();
}

int main(int argc,char** argv)
{
    ros::init(argc,argv,"laser_node");
    ROS_INFO("initialised");
    ros::NodeHandle nh;
    Robot robot=Robot(nh);
    while(ros::ok())
    {
        ros::spinOnce();
        robot.run();
    }
    
}