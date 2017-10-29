#include "ofMain.h"
#include "ofApp.h"


//========================================================================
int main( ){
//	ofSetupOpenGL(600,400,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
    
    ofGLWindowSettings settings;
    settings.width = 600;
    settings.height = 600;
    settings.setPosition(ofVec2f(0,0));
    auto mainWindow = ofCreateWindow(settings);
    auto mainApp = make_shared<ofApp>();
    
    
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
    
	ofRunApp(new ofApp());
}
