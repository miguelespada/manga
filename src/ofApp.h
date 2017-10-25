#pragma once

#include "ofMain.h"
#include "app.h"
#include "SerialAdapter.h"
#include "MidiAdapter.h"
#include "PredictorAdapter.h"
#include "RobotAdapter.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
        void draw();
        App *app;
        void mousePressed(int x, int y, int button);
    
    SerialAdapter *serial;
    MidiAdapter *midi;
    PredictorAdapter *predictor;
    RobotAdapter *robot;
    
		
};
