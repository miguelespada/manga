#include "states.h"

CheckOnlineState::CheckOnlineState(App *a):BaseState(a){
    BaseState::initialize();
};

CheckOnlineState::~CheckOnlineState(){
};

void CheckOnlineState::draw(){
    ofBackground(0);
    
    ofPushStyle();
    ofPushMatrix();
    
    ofTranslate(10, 0);
    
    ofTranslate(0, 20);
    if(app->bPredictorOnline){
        ofSetColor(0, 255, 0);
        ofDrawBitmapString("Predictor is connected...", 0, 0);
    }
    else{
        ofSetColor(255, 0, 0);
        ofDrawBitmapString("Predictor is not connected...", 0, 0);
    }
    
    
    ofTranslate(0, 20);
    if(app->bArduinoOnline){
        ofSetColor(0, 255, 0);
        ofDrawBitmapString("Arduino is connected...", 0, 0);
    }
    else{
        ofSetColor(255, 0, 0);
        ofDrawBitmapString("Arduino is not connected...", 0, 0);
    }
    
    ofTranslate(0, 20);
    if(app->bAbletonOnline){
        ofSetColor(0, 255, 0);
        ofDrawBitmapString("Ableton is connected...", 0, 0);
    }
    else{
        ofSetColor(255, 0, 0);
        ofDrawBitmapString("Ableton is not connected...", 0, 0);
    }
    
    ofTranslate(0, 20);
    if(app->bRobotDriverOnline){
        ofSetColor(0, 255, 0);
        ofDrawBitmapString("Robot driver is connected...", 0, 0);
    }
    else{
        ofSetColor(255, 0, 0);
        ofDrawBitmapString("Robot driver is not connected...", 0, 0);
    }
    
    ofTranslate(0, 20);
    if(app->bAutoUpdatePredictions){
        ofSetColor(255, 255, 0);
        ofDrawBitmapString("Auto update predictions (enabled) [a]", 0, 0);
    }
    else{
        ofSetColor(0, 255, 255);
        ofDrawBitmapString("Auto update predictions (disabled) [a]", 0, 0);
    }
    ofTranslate(0, 20);
    if(app->bRobotBusy){
        ofSetColor(255, 0, 0);
        ofDrawBitmapString("Robot busy", 0, 0);
    }
    else{
        ofSetColor(0, 255, 0);
        ofDrawBitmapString("Robot not busy", 0, 0);
    }
    
    ofPopStyle();
    ofPopMatrix();
    
};

void CheckOnlineState::update(){
};


void CheckOnlineState::next(){
    app->setCurrentState(new StandbyState(app));
    delete this;
};


void CheckOnlineState::reset(){
    app->setCurrentState(new StandbyState(app));
    delete this;
}

