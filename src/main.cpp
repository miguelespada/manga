#include "ofMain.h"
#include "ofApp.h"
#include "visualApp.h"


//========================================================================
int main( ){
//	ofSetupOpenGL(600,400,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
    
    ofGLWindowSettings settings;
    settings.width = 600;
    settings.height = 400;
    settings.setPosition(ofVec2f(300,0));
    auto mainWindow = ofCreateWindow(settings);
    
    settings.width = 600;
    settings.height = 400;
    settings.setPosition(ofVec2f(0,0));
    auto visualWindow = ofCreateWindow(settings);
    
    auto mainApp = make_shared<ofApp>();
    auto visualApp = make_shared<VisualApp>();
    
    
    ofRunApp(visualWindow, visualApp);
    
    visualApp->app = mainApp->app;
    
    
    ofRunApp(mainWindow, mainApp);

    ofRunMainLoop();
    

//	ofRunApp(new ofApp());

}
