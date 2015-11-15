#include "ros/ros.h"
  
#include "std_msgs/Float64.h"
#include "sensor_msgs/JointState.h"
  
#include <sstream>
 
std_msgs::Float64 pos1;
std_msgs::Float64 pos2;
std_msgs::Float64 pos3;
std_msgs::Float64 pos4;
std_msgs::Float64 pos5;
std_msgs::Float64 pos6;
std_msgs::Float64 pos7;
char renew = 0;
 
void reflect_jointstate(const sensor_msgs::JointState::ConstPtr& jointstate);
 
int main(int argc, char **argv)
{
  ros::init(argc, argv, "reflect_rviz_in_crane");
  
  ros::NodeHandle n;
 
  //publish command message to joints/servos of arm
  ros::Publisher joint1_pub = n.advertise<std_msgs::Float64>("/tilt1_controller/command", 1000);
  ros::Publisher joint2_pub = n.advertise<std_msgs::Float64>("/tilt2_controller/command", 1000);
  ros::Publisher joint3_pub = n.advertise<std_msgs::Float64>("/tilt3_controller/command", 1000);
  ros::Publisher joint4_pub = n.advertise<std_msgs::Float64>("/tilt4_controller/command", 1000);
  ros::Publisher joint5_pub = n.advertise<std_msgs::Float64>("/tilt5_controller/command", 1000);
  ros::Publisher joint6_pub = n.advertise<std_msgs::Float64>("/tilt6_controller/command", 1000);
  ros::Publisher joint7_pub = n.advertise<std_msgs::Float64>("/tilt7_controller/command", 1000);
 
  ros::Subscriber sub = n.subscribe("/joint_states", 10, reflect_jointstate); 
  
  ros::Rate loop_rate(100); 
  while (ros::ok())
    {
      while(ros::ok() && renew==0){
	ros::spinOnce();
	loop_rate.sleep();
      }
      joint1_pub.publish(pos1);
      joint2_pub.publish(pos2);
      joint3_pub.publish(pos3);
      joint4_pub.publish(pos4);
      joint5_pub.publish(pos5);
      joint6_pub.publish(pos6);
      joint7_pub.publish(pos7);
      renew = 0;
 
      ros::spinOnce();
      loop_rate.sleep();
    } 
  return 0;
}
 
void reflect_jointstate(const sensor_msgs::JointState::ConstPtr& jointstate)
{
  pos1.data = jointstate->position[0];
  pos2.data = jointstate->position[1];
  pos3.data = jointstate->position[2]; 
  pos4.data = jointstate->position[3];
  pos5.data = jointstate->position[4];
  pos6.data = jointstate->position[5];
  pos7.data = jointstate->position[6];
 
  renew = 1;
}
