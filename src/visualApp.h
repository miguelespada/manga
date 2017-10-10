#pragma once

#include "ofMain.h"
#include "app.h"

class VisualApp : public ofBaseApp{

	public:
		void setup();
		void update();
        void draw();
        App *app;
};
