#include "speed_optimization_pkg/speed_optimization_server.h"




bool speed_optimization_server::speed_optimization(speed_optimization_pkg::TrajectoryOptimization::Request  &req,
         speed_optimization_pkg::TrajectoryOptimization::Response  &res)
{ 
  ros::WallTime start, end;

  start = ros::WallTime::now();
  
  ROS_INFO("Enter");
  
  sent_traj_ = req.sent_traj;
  optm_traj_ = req.sent_traj;
  qd_max_ = req.qd_max;
  
  // One point less since it's assumed that q(0) is the actual position of the robot
  optm_traj_.points.resize(sent_traj_.points.size()-1);

  ds_ = 1.0;
  ds_ = ds_/(sent_traj_.points.size()-1);

  time_ = 0;
  
  for(int i=0;i<sent_traj_.points.size()-1;i++)
  {
      	for(int kk=0;kk<7;kk++)
    	{
        // compute dq/ds
    		diff_aux_(kk) = (sent_traj_.points.at(i+1).positions.at(kk)-sent_traj_.points.at(i).positions.at(kk))/ds_;
    		
        bound_aux_(kk) = fabs(diff_aux_(kk)/(qd_max_.at(kk)));

    	}

      // Compute the coeffiencets
	   	a_k_.push_back(bound_aux_.maxCoeff());
    	b_k_.push_back(1/a_k_.at(i));
      
      // Resize Velocity command
      velocity_command_.resize(7);

    	for(int jj=0;jj<7;jj++){
    		velocity_command_.at(jj) = (b_k_.at(i)*diff_aux_(jj));
    	}


      // Compute dt and next waypoint time_from_start
     	dt_.push_back(a_k_.at(i)*ds_);
    	time_ += dt_.at(i);
      
      // Fill the computed traject0ry
    	optm_traj_.points.at(i).positions = sent_traj_.points.at(i+1).positions;
    	optm_traj_.points.at(i).time_from_start = ros::Duration(time_);
    	optm_traj_.points.at(i).velocities.resize(7);
    	optm_traj_.points.at(i).velocities = velocity_command_;
  }


    res.optm_traj = optm_traj_;
    end = ros::WallTime::now();

  double elapsed_time = (end - start).toNSec() * 1e-6;;
  ROS_INFO("Finished in: %f milliseconds", elapsed_time);

  return true;
}


speed_optimization_server::speed_optimization_server()
{
  ds_ = 1.0;
  time_ = 0;

}

speed_optimization_server::~speed_optimization_server()
{
}


