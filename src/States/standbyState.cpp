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
    
    app->drawBoard(20, 40);
    
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

