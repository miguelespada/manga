#!/bin/bash
source  /home/miguel/manga/scripts/magenta/Magenta/bin/activate
export FLASK_DEBUG=1
echo "Starting predictor"
cd /home/miguel/manga/scripts/magenta/
python ./predictor.py
sleep 5