How to operate 7dof arm with moveit:
roslaunch my_dynamixel_tutorial controller_manager.launch 
roslaunch my_dynamixel_tutorial start_tilt_controller.launch ##this two command line will make the arm able to move

roslaunch 7dof_arm_moveit_config/launch/demo.launch ##moveit can control virtual arm in rviz
roscd crane_urdf/src ##get to crane_urdf/src to make next command line available
rosrun create_urdf reflect_rviz_in_crane ##crane will hear from rviz

Next Thing I have to do :
	using moveit without rviz:
		/move_group hears /tf from /robot_state_publisher and /joint_states from /joint_state_publisher and publish /move_group/fake_controller_joint_states to /joint_state_publisher
		/joint_states also publishes from /joint_state_publisher to /reflect_rviz_in_crane(?) maybe....
		Thus, I need to find /joint_state_publisher node and /robot_state_publisher node. moveit_controller hears /left_arm_relative_something from openni. This node will be connnected with /robot_state_publisher and /joint_state_publisher. Then, that is all!
		moveit planning library : PRMkConfigDefault
