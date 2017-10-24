#include "states.h"

CheckAbletonOnlineState::CheckAbletonOnlineState(App *a):BaseState(a){
    BaseState::initialize();
};

CheckAbletonOnlineState::~CheckAbletonOnlineState(){
};

void CheckAbletonOnlineState::draw(){
    ofBackground(0);
    ofSetColor(255);
    ofDrawBitmapString(toString(), 10, 10);
    ofDrawBitmapString("Ableton not running or paused...", 10, 40);
};

void CheckAbletonOnlineState::update(){
    if(app->bAbletonOnline) next();
};


void CheckAbletonOnlineState::next(){
    app->setCurrentState(new CheckArduinoConnectionState(app));
    delete this;
};


void CheckAbletonOnlineState::reset(){
    app->setCurrentState(new StandbyState(app));
    delete this;
}

