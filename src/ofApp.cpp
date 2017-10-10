#include "ofApp.h"
#include "states.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("Empty Scafold");
    
    ofLogNotice() << "[OF] init";

    ofSetVerticalSync(true);
    ofSetFrameRate(30);
    
    app = new App();
    app->setCurrentState(new StandbyState(app));
    osc = new OscAdapter(app);
    serial = new SerialAdapter(app);
    midi = new MidiAdapter(app);
//    http = new httpAdapter(app);
    
    app->w = 1920;
    app->h = 1080;
    
#ifdef DEBUG
    ofLogNotice() << ("[OF] debug mode");
    app->scale = 0.5;
#else
    ofLogNotice() << "[OF] realease mode";
    app->toggleFullScreen();
    ofHideCursor();
    app->scale = 1;
#endif
    
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    app->draw();
}

void ofApp::mousePressed(int x, int y, int button){
    app->mousePressed(x, y, button);
}
    
