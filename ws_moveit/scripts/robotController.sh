#!/bin/bash

echo "Starting robot controller"

source  /home/miguel/manga/ws_moveit/devel/setup.bash
cd  /home/miguel/manga/ws_moveit/scripts/
python server.py
sleep 5