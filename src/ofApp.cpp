#include "ofApp.h"
#include "states.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("Empty Scafold");
    
    ofLogNotice() << "[OF] init";
    

    ofSetVerticalSync(true);
    ofSetFrameRate(30);
    
    app = new App();
    app->setCurrentState(new CheckPredictorConnectionState(app));
    
    
    osc = new OscAdapter(app);
    serial = new SerialAdapter(app);
    midi = new MidiAdapter(app);
    http = new httpAdapter(app);
    
    
#ifdef DEBUG
    ofLogNotice() << ("[OF] debug mode");
#else
    ofLogNotice() << "[OF] realease mode";
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
    
