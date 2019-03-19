#include "speed_optimization_pkg/speed_optimization_server.h"


 int main(int argc, char **argv)
 {
 	ros::init(argc, argv, "Path Optimization Server");

   ROS_INFO("Waiting for trajectory.");
   speed_optimization_server server;
   ros::spin();

   return 0;
}