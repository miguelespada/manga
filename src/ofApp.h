#pragma once

#include "ofMain.h"
#include "app.h"
#include "OscAdapter.h"
#include "SerialAdapter.h"
#include "MidiAdapter.h"
#include "httpAdapter.h"
#include "RobotAdapter.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
        void draw();
        App *app;
        void mousePressed(int x, int y, int button);
    
    OscAdapter *osc;
    SerialAdapter *serial;
    MidiAdapter *midi;
    httpAdapter *http;
    RobotAdapter *robot;
    
		
};
