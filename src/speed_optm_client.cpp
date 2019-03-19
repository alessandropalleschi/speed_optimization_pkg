
#include "speed_optimization_pkg/speed_optimization_client.h"


speed_optimization_client::speed_optimization_client() 
{
   
  if( !nh_.getParam("/qd_max", qd_max_) || !nh_.getParam ( "fileID", fileID_) || !nh_.getParam("joint_trajectory_command_topic",joint_trajectory_command_topic_))
  {
    ROS_ERROR("Failed to get parameter from server.");
    return;
  }

  // pub_command_right = nh.advertise<trajectory_msgs::JointTrajectory>("/panda_arm/panda_arm_controller/command", 1);
  pub_command_right_ = nh_.advertise<trajectory_msgs::JointTrajectory>("/panda_arm/panda_arm_controller/command", 1);



}
speed_optimization_client::~speed_optimization_client() 
{

}


bool speed_optimization_client::read_trajectory(std::string fileID, trajectory_msgs::JointTrajectory &traj)
{

  trajectory_msgs::JointTrajectoryPoint point_vec;
  traj.joint_names.resize(7);
  point_vec.positions.resize(7);
  
  read_traj_.open(fileID);
  
  if(read_traj_.is_open())
  {
    ROS_INFO("Open File");
  }
  else
  { 
    ROS_ERROR("Failed to open file, check file path");
    return false;
  }

  while ((read_traj_ >> point_vec.positions.at(0) >> point_vec.positions.at(1)  >> point_vec.positions.at(2)  >> point_vec.positions.at(3) >> point_vec.positions.at(4) >> point_vec.positions.at(5) >> point_vec.positions.at(6)))
  {   
      traj.points.push_back(point_vec);
  }

  read_traj_.close();
  return true;

}


bool speed_optimization_client::call_service(speed_optimization_pkg::TrajectoryOptimization &srv)
{
  ros::ServiceClient client = nh_.serviceClient<speed_optimization_pkg::TrajectoryOptimization>("velocity_path_optimization");
  if (client.call(srv))
  {
    ROS_INFO("Service successfully called");
    return true;
  }
  else
  {
    ROS_ERROR("Failed to call service");
    return 0;
  }
}


void speed_optimization_client::send_trajectory(trajectory_msgs::JointTrajectory traj)
{   
    

    traj.joint_names.resize(7);
    traj.joint_names.at(0) = "panda_joint1";
    traj.joint_names.at(1)= "panda_joint2";
    traj.joint_names.at(2)= "panda_joint3";
    traj.joint_names.at(3)= "panda_joint4";
    traj.joint_names.at(4)= "panda_joint5";
    traj.joint_names.at(5)= "panda_joint6";
    traj.joint_names.at(6)= "panda_joint7";
    traj.header.stamp = ros::Time::now()+ros::Duration(0.1);
    pub_command_right_.publish(traj);  

}

