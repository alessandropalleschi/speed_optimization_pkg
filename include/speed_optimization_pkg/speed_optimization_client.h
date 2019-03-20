#include <ros/ros.h>
#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/Bool.h>
#include <trajectory_msgs/JointTrajectory.h>
#include <geometry_msgs/Pose.h>
#include <atomic>
#include <fstream>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <eigen3/Eigen/Dense>
#include <speed_optimization_pkg/TrajectoryOptimization.h>

class speed_optimization_client
{
public:
	speed_optimization_client();
	~speed_optimization_client();
	bool read_trajectory(std::string fileID, trajectory_msgs::JointTrajectory &traj);
	bool call_service(speed_optimization_pkg::TrajectoryOptimization &srv);
	void send_trajectory(trajectory_msgs::JointTrajectory traj);
  	
  	speed_optimization_pkg::TrajectoryOptimization srv_;
	std::vector<double> qd_max_;
	trajectory_msgs::JointTrajectory traj_;
	std::string fileID_, joint_trajectory_command_topic_;
    	ros::Publisher pub_command_right_;

private:

	typedef Eigen::Matrix<double, 7,1> Vector7d;

	std::ifstream read_traj_;

    	ros::NodeHandle nh_;

};
