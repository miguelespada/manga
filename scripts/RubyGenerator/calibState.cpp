#include "states.h"

CalibState::CalibState(App *a):BaseState(a){
    BaseState::initialize();
};

~CalibState::~CalibState(){
};

void CalibState::draw(){
    ofBackground(0);
    ofSetColor(255);
    ofDrawBitmapString(toString(), 10, 10);
};

void CalibState::update(){
};


void CalibState::next(){
    app->setCurrentState(new CalibState(app));
    delete this;
};


void CalibState::reset(){
    app->setCurrentState(new StandbyState(app));
    delete this;
}

