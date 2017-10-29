#!/bin/bash

echo "Starting driver"
source  /home/miguel/manga/ws_moveit/devel/setup.bash
roslaunch ur_modern_driver ur5_bringup.launch robot_ip:=192.168.1.123
sleep 5