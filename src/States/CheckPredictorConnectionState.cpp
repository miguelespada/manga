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
    ofDrawBitmapString("Predictor service not connected...", 10, 40);
};

void CheckPredictorConnectionState::update(){
    if(app->bPredictorOnline) next();
};


void CheckPredictorConnectionState::next(){
    app->setCurrentState(new CheckAbletonOnlineState(app));
    delete this;
};


void CheckPredictorConnectionState::reset(){
    app->setCurrentState(new StandbyState(app));
    delete this;
}

