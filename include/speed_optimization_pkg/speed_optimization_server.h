#include <ros/ros.h>
#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/Bool.h>
#include <trajectory_msgs/JointTrajectory.h>
#include <atomic>
#include <fstream>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <eigen3/Eigen/Dense>
#include <speed_optimization_pkg/TrajectoryOptimization.h>


class speed_optimization_server
{
public:
    speed_optimization_server();
    ~speed_optimization_server();
    bool speed_optimization(speed_optimization_pkg::TrajectoryOptimization::Request  &req,
         speed_optimization_pkg::TrajectoryOptimization::Response  &res);

private:
    typedef Eigen::Matrix<double, 7,1> Vector7d;
    ros::NodeHandle nh_;
    Vector7d diff_aux_;
    Vector7d bound_aux_;
    double time_, ds_;
    float elapsed_time_, start_, end_;
    std::vector<double> dt_;
    std::vector<double> a_k_, b_k_;
    std::vector<double> qd_max_;
    trajectory_msgs::JointTrajectory sent_traj_;
    trajectory_msgs::JointTrajectory optm_traj_;
    ros::ServiceServer service_;
    std::vector<double> velocity_command_;

};