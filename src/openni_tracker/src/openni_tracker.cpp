// openni_tracker.cpp

#include <ros/ros.h>
#include <ros/package.h>
///////////////////////////////
#include <geometry_msgs/Vector3.h>
////////////////////////////////
#include <tf/transform_broadcaster.h>
#include <kdl/frames.hpp>

#include <XnOpenNI.h>
#include <XnCodecIDs.h>
#include <XnCppWrapper.h>

using std::string;

xn::Context        g_Context;
xn::DepthGenerator g_DepthGenerator;
xn::UserGenerator  g_UserGenerator;

XnBool g_bNeedPose   = FALSE;
XnChar g_strPose[20] = "";

/////

int get_user =TRUE;
double left_hand_x,left_hand_y,left_hand_z;
double left_shoulder_x,left_shoulder_y,left_shoulder_z;
double right_hand_x,right_hand_y,right_hand_z;
double right_shoulder_x,right_shoulder_y,right_shoulder_z;
double relative_right_x,relative_right_y,relative_right_z;
double relative_left_x,relative_left_y,relative_left_z;
////////////////////////////////////
geometry_msgs::Vector3 right_hand_msg;
geometry_msgs::Vector3 left_hand_msg;

/////////////////////////////////////


////


void XN_CALLBACK_TYPE User_NewUser(xn::UserGenerator& generator, XnUserID nId, void* pCookie) {
  //////////////
  if(nId==1){
    //////////////
	ROS_INFO("New User %d", nId);

	if (g_bNeedPose)
		g_UserGenerator.GetPoseDetectionCap().StartPoseDetection(g_strPose, nId);
	else
		g_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);
	/////////
  }
  /////////
}
void XN_CALLBACK_TYPE User_LostUser(xn::UserGenerator& generator, XnUserID nId, void* pCookie) {
  /////////////// 
 if(nId==1){
   ////////////
	ROS_INFO("Lost user %d", nId);
	/////////// 
 }
 ///////////
}

void XN_CALLBACK_TYPE UserCalibration_CalibrationStart(xn::SkeletonCapability& capability, XnUserID nId, void* pCookie) {
  /////////////
  if(nId==1){
    ///////////
    ROS_INFO("Calibration started for user %d", nId);
    ///////////
  }
  ////////////
}

void XN_CALLBACK_TYPE UserCalibration_CalibrationEnd(xn::SkeletonCapability& capability, XnUserID nId, XnBool bSuccess, void* pCookie) {
  /////////// 
  if(nId==1){
    //////////////
	if (bSuccess) {
		ROS_INFO("Calibration complete, start tracking user %d", nId);
		g_UserGenerator.GetSkeletonCap().StartTracking(nId);
	}
	else {
		ROS_INFO("Calibration failed for user %d", nId);
		if (g_bNeedPose)
			g_UserGenerator.GetPoseDetectionCap().StartPoseDetection(g_strPose, nId);
		else
			g_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);
	}
	///////////
  }
  //////////
}

void XN_CALLBACK_TYPE UserPose_PoseDetected(xn::PoseDetectionCapability& capability, XnChar const* strPose, XnUserID nId, void* pCookie) {
  ////////////// 
 if(nId==1){
   ////////////
    ROS_INFO("Pose %s detected for user %d", strPose, nId);
    g_UserGenerator.GetPoseDetectionCap().StopPoseDetection(nId);
    g_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);
    /////////////
 }
 ///////////
}
void publishTransform(XnUserID const& user, XnSkeletonJoint const& joint, string const& frame_id, string const& child_frame_id) {
    static tf::TransformBroadcaster br;

    XnSkeletonJointPosition joint_position;
    g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(user, joint, joint_position);
    double x = -joint_position.position.X / 1000.0;
    double y = joint_position.position.Y / 1000.0;
    double z = joint_position.position.Z / 1000.0;
    /////////////////////////////////////XN_SKEL_RIGHT_HAND is right part of body which kinect see. Thus, it would be left hand for most of the time.
    if(joint==XN_SKEL_RIGHT_HAND){
    left_hand_x=x;
    left_hand_y=y;
    left_hand_z=z;
    }
    if(joint==XN_SKEL_RIGHT_SHOULDER){
    left_shoulder_x=x;
    left_shoulder_y=y;
    left_shoulder_z=z;
    }

    if(joint==XN_SKEL_LEFT_HAND){
    right_hand_x=x;
    right_hand_y=y;
    right_hand_z=z;
    }
    if(joint==XN_SKEL_LEFT_SHOULDER){
    right_shoulder_x=x;
    right_shoulder_y=y;
    right_shoulder_z=z;
    }

    ////////////////////////////////////
    XnSkeletonJointOrientation joint_orientation;
    g_UserGenerator.GetSkeletonCap().GetSkeletonJointOrientation(user, joint, joint_orientation);

    XnFloat* m = joint_orientation.orientation.elements;
    KDL::Rotation rotation(m[0], m[1], m[2],
    					   m[3], m[4], m[5],
    					   m[6], m[7], m[8]);
    double qx, qy, qz, qw;
    rotation.GetQuaternion(qx, qy, qz, qw);

    char child_frame_no[128];
    snprintf(child_frame_no, sizeof(child_frame_no), "%s_%d", child_frame_id.c_str(), user);

    tf::Transform transform;
    transform.setOrigin(tf::Vector3(x, y, z));
    transform.setRotation(tf::Quaternion(qx, -qy, -qz, qw));

    // #4994
    tf::Transform change_frame;
    change_frame.setOrigin(tf::Vector3(0, 0, 0));
    tf::Quaternion frame_rotation;
    frame_rotation.setEulerZYX(1.5708, 0, 1.5708);
    change_frame.setRotation(frame_rotation);

    transform = change_frame * transform;

    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), frame_id, child_frame_no));
}

void publishTransforms(const std::string& frame_id) {

    XnUserID users[15];
    XnUInt16 users_count = 15;
    g_UserGenerator.GetUsers(users, users_count);

    
    for (int i = 0; i < users_count; ++i) {
        XnUserID user = users[i];
        if (!g_UserGenerator.GetSkeletonCap().IsTracking(user))
            continue;

	
        publishTransform(user, XN_SKEL_HEAD,           frame_id, "head");
        publishTransform(user, XN_SKEL_NECK,           frame_id, "neck");
        publishTransform(user, XN_SKEL_TORSO,          frame_id, "torso");

        publishTransform(user, XN_SKEL_LEFT_SHOULDER,  frame_id, "left_shoulder");
        publishTransform(user, XN_SKEL_LEFT_ELBOW,     frame_id, "left_elbow");
	//	printf("left_elbow: [%f,%f,%f]\n",left_elbow_x,left_elbow_y,left_elbow_z);

	
	publishTransform(user, XN_SKEL_LEFT_HAND,      frame_id, "left_hand");
	//	printf("left_hand : [%f,%f,%f]\n",left_hand_x,left_hand_y,left_hand_z);
        publishTransform(user, XN_SKEL_RIGHT_SHOULDER, frame_id, "right_shoulder");
        publishTransform(user, XN_SKEL_RIGHT_ELBOW,    frame_id, "right_elbow");
        publishTransform(user, XN_SKEL_RIGHT_HAND,     frame_id, "right_hand");

        publishTransform(user, XN_SKEL_LEFT_HIP,       frame_id, "left_hip");
        publishTransform(user, XN_SKEL_LEFT_KNEE,      frame_id, "left_knee");
        publishTransform(user, XN_SKEL_LEFT_FOOT,      frame_id, "left_foot");

        publishTransform(user, XN_SKEL_RIGHT_HIP,      frame_id, "right_hip");
        publishTransform(user, XN_SKEL_RIGHT_KNEE,     frame_id, "right_knee");
        publishTransform(user, XN_SKEL_RIGHT_FOOT,     frame_id, "right_foot");
	//////////////////////////
	relative_left_x=left_hand_x-left_shoulder_x;
	relative_left_y=left_hand_y-left_shoulder_y;
	relative_left_z=left_hand_z-left_shoulder_z;
	relative_left_x=relative_left_x*1000;
	relative_left_y=relative_left_y*1000;
	relative_left_z=relative_left_z*1000;

	relative_right_x=right_hand_x-right_shoulder_x;
	relative_right_y=right_hand_y-right_shoulder_y;
	relative_right_z=right_hand_z-right_shoulder_z;
	relative_right_x=relative_right_x*1000;
	relative_right_y=relative_right_y*1000;
	relative_right_z=relative_right_z*1000;

	////////////////////////////
	left_hand_msg.x=relative_left_x;
	left_hand_msg.y=relative_left_y;
	left_hand_msg.z=relative_left_z;


	right_hand_msg.x=relative_right_x;
	right_hand_msg.y=relative_right_y;
	right_hand_msg.z=relative_right_z;
	

	///////////////////////////
	
	//	printf("relative_right_position : [%f,%f,%f]\n",right_hand_msg.x,right_hand_msg.y,right_hand_msg.z);
	//printf("relative_left_position : [%f,%f,%f]\n",left_hand_msg.x,left_hand_msg.y,left_hand_msg.z);
    }
}

#define CHECK_RC(nRetVal, what)										\
	if (nRetVal != XN_STATUS_OK)									\
	{																\
		ROS_ERROR("%s failed: %s", what, xnGetStatusString(nRetVal));\
		return nRetVal;												\
	}

int main(int argc, char **argv) {
    ros::init(argc, argv, "openni_tracker");
    ros::NodeHandle nh;
    /////////////////////////////
    ros::Publisher chatter_pub1 = nh.advertise<geometry_msgs::Vector3>("right_hand",1000);
    ros::Publisher chatter_pub2 = nh.advertise<geometry_msgs::Vector3>("left_hand",1000);

    ////////////////////////////

    string configFilename = ros::package::getPath("openni_tracker") + "/openni_tracker.xml";
    XnStatus nRetVal = g_Context.InitFromXmlFile(configFilename.c_str());
    CHECK_RC(nRetVal, "InitFromXml");

    nRetVal = g_Context.FindExistingNode(XN_NODE_TYPE_DEPTH, g_DepthGenerator);
    CHECK_RC(nRetVal, "Find depth generator");

	nRetVal = g_Context.FindExistingNode(XN_NODE_TYPE_USER, g_UserGenerator);
	if (nRetVal != XN_STATUS_OK) {
		nRetVal = g_UserGenerator.Create(g_Context);
	    if (nRetVal != XN_STATUS_OK) {
		    ROS_ERROR("NITE is likely missing: Please install NITE >= 1.5.2.21. Check the readme for download information. Error Info: User generator failed: %s", xnGetStatusString(nRetVal));
            return nRetVal;
	    }
	}

	if (!g_UserGenerator.IsCapabilitySupported(XN_CAPABILITY_SKELETON)) {
		ROS_INFO("Supplied user generator doesn't support skeleton");
		return 1;
	}

    XnCallbackHandle hUserCallbacks;
    //////////////////////////////////////////////////////////
   	g_UserGenerator.RegisterUserCallbacks(User_NewUser, User_LostUser, NULL, hUserCallbacks);





    /* if(get_user==TRUE){g_UserGenerator.RegisterUserCallbacks(User_NewUser, User_LostUser, NULL, hUserCallbacks);
      get_user=FALSE;
    }
    else{
      ROS_INFO("Other user interrupt! Get Out of Kinect range!");
    }
    printf("%d\n",get_user);
    */


	//////////////////////////////////////////////////////////
	XnCallbackHandle hCalibrationCallbacks;
	g_UserGenerator.GetSkeletonCap().RegisterCalibrationCallbacks(UserCalibration_CalibrationStart, UserCalibration_CalibrationEnd, NULL, hCalibrationCallbacks);

	if (g_UserGenerator.GetSkeletonCap().NeedPoseForCalibration()) {
		g_bNeedPose = TRUE;
		if (!g_UserGenerator.IsCapabilitySupported(XN_CAPABILITY_POSE_DETECTION)) {
			ROS_INFO("Pose required, but not supported");
			return 1;
		}

		XnCallbackHandle hPoseCallbacks;
		g_UserGenerator.GetPoseDetectionCap().RegisterToPoseCallbacks(UserPose_PoseDetected, NULL, NULL, hPoseCallbacks);

		g_UserGenerator.GetSkeletonCap().GetCalibrationPose(g_strPose);
	}

	g_UserGenerator.GetSkeletonCap().SetSkeletonProfile(XN_SKEL_PROFILE_ALL);

	nRetVal = g_Context.StartGeneratingAll();
	CHECK_RC(nRetVal, "StartGenerating");

	ros::Rate r(30);

        
        ros::NodeHandle pnh("~");
	string frame_id("openni_depth_frame");
	pnh.getParam("camera_frame_id", frame_id);
	//	string frame_id("camera_link");
	//pnh.getParam("camera_frame_id", frame_id);
	while (ros::ok()) {
		g_Context.WaitAndUpdateAll();
		publishTransforms(frame_id);

		/////////////////////////
		chatter_pub1.publish(right_hand_msg);
		chatter_pub2.publish(left_hand_msg);
		/////////////////////////

		r.sleep();
	}

	g_Context.Shutdown();
	return 0;
}
