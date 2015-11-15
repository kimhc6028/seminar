#!/usr/bin/env python
import rospy
import sys
import numpy as np
from geometry_msgs.msg import Twist
from kobuki_msgs.msg import MotorPower
from geometry_msgs.msg import Vector3

relative_left_x=0.0
relative_left_y=0.0
relative_left_z=0.0
relative_right_x=0.0
relative_right_y=0.0
relative_right_z=0.0

#relative_left_x_first=0.0
#relative_left_y_first=0.0
#relative_left_z_first=0.0
#relative_right_x_first=0.0
#relative_right_y_first=0.0
#relative_right_z_first=0.0
#first_left=True
#first_right=True

#relative_right_angle_yz=0.0#forward/backword movement for robot
#relative_right_angle_xz=0.0#rotation for robot

def left_hand_processing(data):##left hand : relative postion btw left hand and left shoulder
    global relative_left_x,relative_left_y,relative_left_z
    #global relative_left_x_first,relative_left_y_first,relative_left_z_first
    #global first_left
    relative_left_x=data.x
    relative_left_y=data.y
    relative_left_z=data.z
    #if first_left==True:
    #    relative_left_x_first=relative_left_x
    #    relative_left_y_first=relative_left_y
    #    relative_left_z_first=relative_left_z

    #    first_left=False
    #    print relative_left_x,relative_left_y,relative_left_z#erase it

def right_hand_processing(data):##left hand : relative postion btw right hand and right shoulder
    global relative_right_x,relative_right_y,relative_right_z
    #global relative_right_x_first,relative_right_y_first,relative_right_z_first
    
    #global first_right
    relative_right_x=data.x
    relative_right_y=data.y
    relative_right_z=data.z
    #if first_right==True:
    #    relative_right_x_first=relative_right_x
    #    relative_right_y_first=relative_right_y
    #    relative_right_z_first=relative_right_z
 
    #first_right=False
        #    relative_right_angle_yz=180/np.pi*np.arctan(-relative_right_y/relative_right_z)
        #    relative_right_angle_xz=180/np.pi*np.arctan(-relative_right_x/relative_right_z)
    #print relative_right_x-relative_right_x_first,relative_right_z-relative_right_z_first

    #print relative_right_x,relative_right_y,relative_right_z#erase it


def move():
    rospy.init_node('moveop')
    rospy.Subscriber("left_hand",Vector3,left_hand_processing)
    rospy.Subscriber("right_hand",Vector3,right_hand_processing)
    pub_motor_move=rospy.Publisher('mobile_base/commands/velocity',Twist,queue_size=10)
    pub_motor_turnon=rospy.Publisher('mobile_base/commands/motor_power',MotorPower,queue_size=10)
    
    pub_motor_turnon.publish(1)
    #200,-150,-150?

    while not rospy.is_shutdown():
        move_fb=relative_right_z
        turn_rl=relative_right_x
        print move_fb,turn_rl
        v_x=0.0
        w_z=0.0
        
        if move_fb>-100:
            v_x=0.01
        elif move_fb<-300:
            v_x=-0.01
                    
        if turn_rl >250:
            w_z=0.05
        elif turn_rl < 50:
            w_z =-0.05
        v=Vector3(v_x,0,0)
        omega=Vector3(0,0,w_z)
        twist=Twist(v,omega)
        pub_motor_move.publish(twist)
        rospy.sleep(0.1)
        #def listener():



if __name__=='__main__':
    try:
        #        argv=sys.argv
        #        argc=len(argv)
        #        v_x=float(argv[1])
        #        omega_z=float(argv[2])
        move()
        ##        move(0,0)
    except rospy.ROSInterruptException:
        pass
