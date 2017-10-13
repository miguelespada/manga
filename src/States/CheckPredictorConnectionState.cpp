#include "states.h"

CheckPredictorConnectionState::CheckPredictorConnectionState(App *a):BaseState(a){
    BaseState::initialize();
};

CheckPredictorConnectionState::~CheckPredictorConnectionState(){
};

void CheckPredictorConnectionState::draw(){
    ofBackground(255);
    ofSetColor(0);
    ofDrawBitmapString(toString(), 10, 10);
    ofDrawBitmapString("Predictor service not connected...", 10, 40);
};

void CheckPredictorConnectionState::update(){
    if(app->bPredictorOnline) next();
};


void CheckPredictorConnectionState::next(){
    app->setCurrentState(new StandbyState(app));
    delete this;
};


void CheckPredictorConnectionState::reset(){
    app->setCurrentState(new StandbyState(app));
    delete this;
}

