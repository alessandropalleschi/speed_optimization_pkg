# speed_optimization_pkg
A ROS package to perform optimization over a fixed joint path for velocity constrained 7-DoF manipulators.
The code gives the minimum time trajectory needed to follow the path while coping with constraints of the type:

  <img src="https://latex.codecogs.com/svg.latex?\Large&space;|\dot{q}|\leq\bar{\dot{q}}" title="\Large |\dot{q}|\leq\bar{\dot{q}}" />  
  
# Requirements:

    A PC with Ubuntu 16.04 and ROS kinetic (not tested for other versions)

# Installation:

In a terminal:

    mkdir -p ~/catkin_ws/src
    cd ~/catkin_ws/src
    catkin_init_workspace
    git clone https://github.com/alessandropalleschi/speed_optimization_pkg.git
    cd ~/catkin_ws
    catkin_make

# Setup

The package offers a Ros Service server with a Joint Trajectory message as request.
The Joint Trajectory message is used to store the joint space path to optimize and the maximum joint velocities <img src="https://latex.codecogs.com/svg.latex?\Large&space;\bar{\dot{q}}" title="\Large \bar{\dot{q}}" /> for each point of the trajectory.
The path is stored in the points.positions field of the message, while the speed limits are stored in the points.velocities field.
As response, the service gives the optimized joint trajectory, in form of a trajectory_msgs::JointTrajectory, with suitable velocities and time_from_start for each waypoint.
To launch the server, in a terminal:
    
    roslaunch speed_optimization_pkg speed_optm.launch
      
An example for a client is present in this repository. It assumes that you're using a Franka Emika Panda manipulator. 
It reads a trajectory stored in a .txt file and loads the current velocity limits. Then, it sents them as request for the service and publish to the robot the computed trajectory.
In the launch file change the path of the .txt file and the name of the joint trajectory command topic to match your setup.
To launch the client, in a terminal:

    roslaunch speed_optimization_pkg speed_optm_client.launch

Note: The robot has to start in this configuration:

      q(0)= [0.0000000000 -1.0021375297 0.0000000000 -2.6342514899 0.0000000000 1.6321139602 0.0000000000]
