#pragma once

#include "ofMain.h"
#include "app.h"
#include "OscAdapter.h"
#include "SerialAdapter.h"
#include "MidiAdapter.h"
#include "httpAdapter.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
        void draw();
        App *app;
    
    OscAdapter *osc;
    SerialAdapter *serial;
    MidiAdapter *midi;
    httpAdapter *http;
    
		
};
