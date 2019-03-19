# speed_optimization_pkg
A ROS package to perform optimization over a fixed joint path for velocity constrained manipulators.
The code gives the minimum time trajectory needed to follow the path while coping with constraints of the type:

  <img src="https://latex.codecogs.com/svg.latex?\Large&space;|\dot{q}|\leq\bar{\dot{q}}" title="\Large |\dot{q}|\leq\bar{\dot{q}}" />  
  
The optimization is carried out using the joint velocities as control input and using the parametrization with respect to the path coordinate <img src="https://latex.codecogs.com/svg.latex?\Large&space;s" title="\Large s" /> presented in:
       
       [D. Verscheure, B. Demeulenaere, J. Swevers, J.  De  Schutter and M. Diehl.] - Time-optimal path tracking for robots: A convex optimization approach. - IEEE Transactions on Automatic Control, 54(10):2318–2327, Oct 2009
The general optimal problem to solve is:

<img src="https://latex.codecogs.com/svg.latex?\Large&space;min_{u}\,T=\int_0^T1dt" title="\Large min\_{u}\,T=\int_0^T1dt" />  
<img src="https://latex.codecogs.com/svg.latex?\Large&space;s.t.\;u(t)\,=\,q'(s(t))\,\dot{s}(t)" title="\Large s.t.\;u(t)\,=\,q'(s(t))\dot{s}(t)" />
<img src="https://latex.codecogs.com/svg.latex?\Large&space;s(0)=0\;and\;s(T)=1" title="\Large s(0)=0\;and\;s(T)=1" />  
<img src="https://latex.codecogs.com/svg.latex?\Large&space;|q'(s(t))\,\dot{s}(t)|\leq\bar{\dot{q}}(s(t))" title="\Large |u(t)|\leq\bar{\dot{q}}(s(t))" />  
<img src="https://latex.codecogs.com/svg.latex?\Large&space;\dot{s}(t)>0" title="\Large \dot{s}(t)>0" />  
<img src="https://latex.codecogs.com/svg.latex?\Large&space;for\;t\in[0,T]" title="\Large s\in[0,1]" />  

Using:

<img src="https://latex.codecogs.com/svg.latex?\Large&space;b(s)=\dot{s}" title="\Large b(s)=\dot{s}" />  

and:

<img src="https://latex.codecogs.com/svg.latex?\Large&space;a(s)=\frac{1}{b(s)}" title="\Large a(s)=\frac{1}{b(s)}" />  

It becomes:

<img src="https://latex.codecogs.com/svg.latex?\Large&space;\min_{u}\,T=\int_0^T1dt=\int_0^1a(s)ds" title="\Large min_{u}\,T=\int_0^T1dt=\int_0^1a(s)ds" />

Using direct transcription, which involves discretizing the path coordinate s on K + 1 grid points:

<img src="https://latex.codecogs.com/svg.latex?\Large&space;\min_{a}\int_0^1a(s)ds=\sum_{k=0}^Ka_k\,\Delta\,s^k" title="\Large int" />
<img src="https://latex.codecogs.com/svg.latex?\Large&space;a_k\ge\max\frac{|q'(s^k)|}{\bar{\dot{q}}(s^k)}" title="\Large int" />
<img src="https://latex.codecogs.com/svg.latex?\Large&space;a_k>0" title="\Large int" />

The solution is trivial and is:

<img src="https://latex.codecogs.com/svg.latex?\Large&space;a_k=\max\frac{|q'(s^k)|}{\bar{\dot{q}}(s^k)}" title="\Large int" />

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

The package offers a Ros Service server with a Joint Trajectory message and a double array as requests.
The Joint Trajectory message is the joint space path to optimize and the array represents the maximum joint velocities <img src="https://latex.codecogs.com/svg.latex?\Large&space;\bar{\dot{q}}" title="\Large \bar{\dot{q}}" /> .
As response, the service gives the optimized joint trajectory, in form of a trajectory_msgs::JointTrajectory.
To launch the server, in a terminal:
    
    roslaunch speed_optimization_pkg speed_optm.launch
    
    
An example for a client is present in this repository. It assumes that you're using a Franka Emika Panda manipulator. 
It reads a trajectory stored in a .txt file and loads the current velocity limits. Then, it sents them as request for the service and publish to the robot the computed trajectory.
In the launch file change the path of the .txt file and the name of the joint trajectory command topic to match your setup.
To launch the client, in a terminal:

    roslaunch speed_optimization_pkg speed_optm_client.launch


