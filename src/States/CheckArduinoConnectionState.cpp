#include "states.h"

CheckArduinoConnectionState::CheckArduinoConnectionState(App *a):BaseState(a){
    BaseState::initialize();
};

CheckArduinoConnectionState::~CheckArduinoConnectionState(){
};

void CheckArduinoConnectionState::draw(){
    ofBackground(0);
    ofSetColor(255);
    ofDrawBitmapString(toString(), 10, 10);
};

void CheckArduinoConnectionState::update(){
    next();
};


void CheckArduinoConnectionState::next(){
    app->setCurrentState(new StandbyState(app));
    delete this;
};


void CheckArduinoConnectionState::reset(){
    app->setCurrentState(new StandbyState(app));
    delete this;
}

