#include "states.h"

CheckArduinoConnectionState::CheckArduinoConnectionState(App *a):BaseState(a){
    BaseState::initialize();
};

CheckArduinoConnectionState::~CheckArduinoConnectionState(){
};

void CheckArduinoConnectionState::draw(){
    ofBackground(255);
    ofSetColor(0);
    ofDrawBitmapString(toString(), 10, 10);
    ofDrawBitmapString("Arduino not running or paused...", 10, 40);
};

void CheckArduinoConnectionState::update(){
    if(app->bArduinoOnline) next();
};


void CheckArduinoConnectionState::next(){
    app->setCurrentState(new StandbyState(app));
    delete this;
};


void CheckArduinoConnectionState::reset(){
    app->setCurrentState(new StandbyState(app));
    delete this;
}

