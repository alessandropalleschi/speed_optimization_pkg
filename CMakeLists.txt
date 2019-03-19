cmake_minimum_required(VERSION 2.8.3)
project(speed_optimization_pkg)

add_definitions(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  tf
  trajectory_msgs
  message_generation
)

add_service_files(
  FILES
  TrajectoryOptimization.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
  trajectory_msgs
)

catkin_package(
 INCLUDE_DIRS include
 CATKIN_DEPENDS
)
find_package (Eigen3)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)


add_executable(speed_optm_server_node src/speed_optm.cpp src/speed_optm_server_main.cpp)
add_dependencies(speed_optm_server_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(speed_optm_server_node ${catkin_LIBRARIES})


add_executable(speed_optm_client_node src/speed_optm_client.cpp src/speed_optm_client_main.cpp)
add_dependencies(speed_optm_client_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(speed_optm_client_node ${catkin_LIBRARIES})
