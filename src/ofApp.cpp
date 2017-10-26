#include "ofApp.h"
#include "states.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("Empty Scafold");
    
    ofLogNotice() << "[OF] init";
    

    ofSetVerticalSync(true);
    ofSetFrameRate(30);
    
    app = new App();
    app->setCurrentState(new CheckOnlineState(app));
    
   // serial = new SerialAdapter(app);
    midi = new MidiAdapter(app);
   // robot = new RobotAdapter(app);
    predictor = new PredictorAdapter(app, robot);
    
    
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
    
