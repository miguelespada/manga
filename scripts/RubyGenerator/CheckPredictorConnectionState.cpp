#include "states.h"

CheckPredictorConnectionState::CheckPredictorConnectionState(App *a):BaseState(a){
    BaseState::initialize();
};

CheckPredictorConnectionState::~CheckPredictorConnectionState(){
};

void CheckPredictorConnectionState::draw(){
    ofBackground(0);
    ofSetColor(255);
    ofDrawBitmapString(toString(), 10, 10);
};

void CheckPredictorConnectionState::update(){
};


void CheckPredictorConnectionState::next(){
    app->setCurrentState(new CheckPredictorConnectionState(app));
    delete this;
};


void CheckPredictorConnectionState::reset(){
    app->setCurrentState(new StandbyState(app));
    delete this;
}

