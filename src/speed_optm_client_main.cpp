#include "speed_optimization_pkg/speed_optimization_client.h"


int main(int argc, char **argv)
{
    ros::init(argc, argv, "Path Optimization Client");
    
    speed_optimization_client client;
    client.read_trajectory(client.fileID_,client.traj_);

    client.srv_.request.sent_traj = client.traj_;
    client.srv_.request.qd_max = client.qd_max_;
    
    if(!client.call_service(client.srv_))
    {
      ROS_ERROR("Something went wrong");
      return 1;
    }  
    ros::Rate f(100);

while (ros::ok())
{
  f.sleep(); 
  ros::spinOnce();
  client.send_trajectory(client.srv_.response.optm_traj);
  f.sleep(); 
  break;
} 

  return 0;
}