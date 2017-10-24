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

    app->drawBoard(20, 80);
    app->drawExtras(40, 350);
};

void StandbyState::update(){
    if(!app->online())
        app->setCurrentState(new CheckPredictorConnectionState(app));
};


void StandbyState::next(){
    app->setCurrentState(new CalibState(app));
    delete this;
};


void StandbyState::reset(){
    app->setCurrentState(new StandbyState(app));
    delete this;
}

