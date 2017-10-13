#include "states.h"

StandbyState::StandbyState(App *a):BaseState(a){
    BaseState::initialize();
};

StandbyState::~StandbyState(){
};

void StandbyState::draw(){
    ofBackground(0);
    ofSetColor(255);
    ofDrawBitmapString(toString(), 10, 20);
    
    if( app->board.lastHumanActivity > 0)
        ofDrawBitmapString("Last human activity: " + ofToString(ofGetElapsedTimef() - app->board.lastHumanActivity, 1), 100, 20);
    
    if( app->board.lastMachineActivity > 0)
        ofDrawBitmapString("Last machine activity: " + ofToString(ofGetElapsedTimef() - app->board.lastMachineActivity, 1), 100, 40);
    
    app->drawBoard(20, 60);
};

void StandbyState::update(){
};


void StandbyState::next(){
    app->setCurrentState(new CalibState(app));
    delete this;
};


void StandbyState::reset(){
    app->setCurrentState(new StandbyState(app));
    delete this;
}

