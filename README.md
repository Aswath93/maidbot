# maidbot
ros package for the task given by maid bot
Maidbot ROS Task
This is a brief description of my approach to the task. 

There are two nodes in the package :
laser_node 
send_pose

The laser node generates the fake laser(circular scan) scan data in the laser_frame and publishes it it the scan topic. The laser_frame is offset from the base_link frame. This transform is published by a static transform publisher. Additionally laser_node also listens to the pose topic that has the information about the position of the robot. This information is used to update the tf between map frame and the base link frame.

The send_pose node publishes a custom message that has x,y,angle fields. The node publishes data imitating a robot moving along a circular path.

The laser.launch file runs the both the above mentioned nodes , the static transform and rviz with the laser.rviz configuration.

command to be run "roslaunch maidbot_laser laser.launch"
