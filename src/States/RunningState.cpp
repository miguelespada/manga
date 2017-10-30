#include "states.h"

RunningState::RunningState(App *a):BaseState(a){
    BaseState::initialize();
    
    ofHideCursor();
    ofSetWindowShape(1080 * 2, 1920);
    ofSetWindowPosition(0, 0);
    //ofSetFullscreen(true);
    
    lastMessageChange = -1;
    a->bRobotEnabled = true;
};

RunningState::~RunningState(){
    
    
    ofSetFullscreen(false);
    ofSetWindowShape(600, 600);
    ofShowCursor();

};

void RunningState::draw(){
    
    ofBackground(255);
    ofSetColor(0);
    
    if(ofGetElapsedTimef() - lastMessageChange > 3){
        lastMessageChange = ofGetElapsedTimef();
        nMsg = (nMsg + 1) % app->idleMessages.size();
        
    }
    
    string s = app->idleMessages[nMsg];
    ofRectangle boundingBox  =  Assets::getInstance()->font.getStringBoundingBox(s, 0, 0);
    Assets::getInstance()->font.drawString(s, ofGetWidth() / 2 - boundingBox.width / 2, ofGetHeight() / 4);

Assets::getInstance()->font.drawString(s, 3* ofGetWidth() / 2 - boundingBox.width / 2, ofGetHeight() / 4);
};

void RunningState::update(){
};


void RunningState::next(){
    app->setCurrentState(new StandbyState(app));
    delete this;
};


void RunningState::reset(){
    app->setCurrentState(new StandbyState(app));
    delete this;
}

