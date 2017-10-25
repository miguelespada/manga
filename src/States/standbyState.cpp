#include "states.h"

StandbyState::StandbyState(App *a):BaseState(a){
    BaseState::initialize();
};

StandbyState::~StandbyState(){
};

void StandbyState::draw(){
    ofBackground(0);
    ofSetColor(255);
    
    if(app->board.lastHumanActivity > 0)
        ofDrawBitmapString("Last human activity: " + ofToString(ofGetElapsedTimef() - app->board.lastHumanActivity, 1), 20, 20);
    
    if(app->board.lastMachineActivity > 0)
        ofDrawBitmapString("Last machine activity: " + ofToString(ofGetElapsedTimef() - app->board.lastMachineActivity, 1), 20, 40);
    
    ofDrawBitmapString("Last number of changes: " + ofToString(app->board.lastNumberOfChanges), 20, 60);
    
    
    ofDrawBitmapString("Midi instrument [0..9]: " + ofToString(app->midiInstrument), 280, 20);

    
    
    ofPushStyle();
    ofPushMatrix();
    
    ofTranslate(510, 0);
    
    ofTranslate(0, 20);
    if(app->bPredictorOnline){
        ofSetColor(0, 255, 0);
        ofDrawBitmapString("Predictor", 0, 0);
    }
    else{
        ofSetColor(255, 0, 0);
        ofDrawBitmapString("Predictor", 0, 0);
    }
    
    
    ofTranslate(0, 20);
    if(app->bArduinoOnline){
        ofSetColor(0, 255, 0);
        ofDrawBitmapString("Arduino", 0, 0);
    }
    else{
        ofSetColor(255, 0, 0);
        ofDrawBitmapString("Arduino", 0, 0);
    }
    
    ofTranslate(0, 20);
    if(app->bAbletonOnline){
        ofSetColor(0, 255, 0);
        ofDrawBitmapString("Ableton", 0, 0);
    }
    else{
        ofSetColor(255, 0, 0);
        ofDrawBitmapString("Ableton", 0, 0);
    }
    
    ofTranslate(0, 20);
    if(app->bRobotDriverOnline){
        ofSetColor(0, 255, 0);
        ofDrawBitmapString("Robot", 0, 0);
    }
    else{
        ofSetColor(255, 0, 0);
        ofDrawBitmapString("Robot", 0, 0);
    }
    
    ofTranslate(0, 20);
    if(app->bAutoUpdatePredictions){
        ofSetColor(0, 255, 255);
        ofDrawBitmapString("Auto (a)", 0, 0);
    }
    
    ofPopStyle();
    ofPopMatrix();
    
    app->drawBoard(20, 80);
    app->drawExtras(40, 350);
};

void StandbyState::update(){
};


void StandbyState::next(){
    app->setCurrentState(new CheckOnlineState(app));
    delete this;
};


void StandbyState::reset(){
    app->setCurrentState(new StandbyState(app));
    delete this;
}

