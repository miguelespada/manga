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
        nMachineMsg = (nMachineMsg + 1) % app->rockMessages.size();
        nHumanMsg = (nHumanMsg + 1) % app->humanMessages.size();
    }
    
    string s = app->rockMessages[nMachineMsg];
    ofRectangle boundingBox  =  Assets::getInstance()->font.getStringBoundingBox(s, 0, 0);
    Assets::getInstance()->font.drawString(s, ofGetWidth() / 2 - boundingBox.width / 2, ofGetHeight() / 4);

    s = app->humanMessages[nHumanMsg];
    boundingBox  =  Assets::getInstance()->font.getStringBoundingBox(s, 0, 0);
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

