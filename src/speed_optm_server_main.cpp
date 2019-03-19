#include "speed_optimization_pkg/speed_optimization_server.h"


 int main(int argc, char **argv)
 {
 	ros::init(argc, argv, "Path Optimization Server");

   ROS_INFO("Waiting for trajectory.");
   speed_optimization_server server;
   ros::NodeHandle nh;

   ros::ServiceServer service = nh.advertiseService("velocity_path_optimization", &speed_optimization_server::speed_optimization,&server);

   ros::spin();

   return 0;
}