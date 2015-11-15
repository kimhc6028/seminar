#include "ros/ros.h"
   
#include "std_msgs/Float64.h"
#include "sensor_msgs/JointState.h"
#include "dynamixel_msgs/MotorStateList.h"
   
#include <sstream>
  
#define PI 3.14159265
#define MIDDLE_VAL 512
#define CHANGE_TO_DEG (300.0/1024.0)
#define CHANGE_TO_RAD (PI/180.0)
 
sensor_msgs::JointState jointstate;
char renew = 0;
  
void reflect_jointstate(const dynamixel_msgs::MotorStateList::ConstPtr& motorstates);
  
int main(int argc, char **argv)
{
  ros::init(argc, argv, "reflect_crane_in_rviz");
   
  ros::NodeHandle n;
  
  ros::Publisher joint_states_pub = n.advertise<sensor_msgs::JointState>("/joint_states_source", 10);
  
  ros::Subscriber sub = n.subscribe("/motor_states/pan_tilt_port", 10, reflect_jointstate); 
  
  ros::Rate loop_rate(100); 
  
  jointstate.name.push_back("joint1");
  jointstate.name.push_back("joint2");
  jointstate.name.push_back("joint3");
  jointstate.name.push_back("joint4");
  jointstate.name.push_back("joint5");
  jointstate.name.push_back("joint6");
  jointstate.name.push_back("joint7");
  jointstate.position.push_back(0.0);
  jointstate.position.push_back(0.0);
  jointstate.position.push_back(0.0);
  jointstate.position.push_back(0.0);
  jointstate.position.push_back(0.0);
  jointstate.position.push_back(0.0);
  jointstate.position.push_back(0.0);
  
  while (ros::ok())
    {
      while(ros::ok() && renew==0){
	ros::spinOnce(); 
	loop_rate.sleep();
      }
      jointstate.header.stamp = ros::Time::now();
      joint_states_pub.publish(jointstate);
      renew = 0;
  
      ros::spinOnce();
      loop_rate.sleep();
    } 
  return 0;
}
  
void reflect_jointstate(const dynamixel_msgs::MotorStateList::ConstPtr& motorstates)
{
  int id;
  for(id=1;id<=7;id++){
    jointstate.position[id-1] = ((double)(motorstates->motor_states[id-1].position)-MIDDLE_VAL)*CHANGE_TO_DEG*CHANGE_TO_RAD; 
  }
  renew = 1;
}
