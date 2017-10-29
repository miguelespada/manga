//
//  httpAdapter.cpp
//  mangaPlayer
//
//  Created by miguel on 09/10/2017.
//
//

#include "PredictorAdapter.h"
#include "states.h"

PredictorAdapter::PredictorAdapter(App *a, RobotAdapter *_robotAdapter){
    app = a;
    robotAdapter = _robotAdapter;
    
    bOnline = false;
    ofAddListener(ofEvents().update, this, &PredictorAdapter::update);
    
    string baseRoute = "http://" + Assets::getInstance()->getControllerHost() + ":5000/";
    
    serviceUrl = baseRoute + "ping";
    predictorUrl = baseRoute + "predict/";
    
    lastTime = ofGetElapsedTimef();
    
    ofAddListener(ofEvents().keyPressed, this, &PredictorAdapter::keyPressed);
    bMustPredict = false;
    
}

PredictorAdapter::~PredictorAdapter(){
}

void PredictorAdapter::update(ofEventArgs &args){
    app->bPredictorOnline = bOnline;
    
    if(isOnline() && !bOnline){
        bOnline = true;
        ofLogNotice() << "Predictor is online";
    }
    
    if(app->board.lastHumanActivity > 0){
        if(ofGetElapsedTimef() - app->board.lastHumanActivity > Assets::getInstance()->getInactivityTime()){
            if(!app->bRobotBusy) {
                predict();
                app->board.lastHumanActivity = -1;
            }
        }
    }
}

bool PredictorAdapter::isOnline(){
    if(ofGetElapsedTimef() - lastTime > 3){

        lastTime = ofGetElapsedTimef();
        
        bool parsingSuccessful = result.open(serviceUrl);
        
        if (parsingSuccessful){
            return true;
        }
        else {
            ofLogNotice()  << "Failed to parse JSON";
            bOnline = false;
            return false;
        }
    }
}

void PredictorAdapter::predict(){
    string board = app->board.toString();
    bool parsingSuccessful = result.open(predictorUrl + board);
    string prediction =  result.get("prediction", "").asString();
    vector<ofPoint> changes = app->board.fromPrediction(prediction, app->bAutoUpdatePredictions);
    plan(serializeChanges(changes));
}

void PredictorAdapter::keyPressed(ofKeyEventArgs& eventArgs){
    if (eventArgs.key == 'p')
        predict();
    
    if (eventArgs.key == 'z'){
        if(robotAdapter != NULL)
            robotAdapter->sendZero();
    }
    
    if (eventArgs.key == 'x'){
        if(robotAdapter != NULL)
            robotAdapter->sendTest();
    }
}

string PredictorAdapter::serializeChanges(vector<ofPoint> changes){
    string s = "";
    for(auto c: changes){
        s += ofToString(c.x) + "," + ofToString(c.y) + ";";
    }
    return s;
}

void PredictorAdapter::plan(string changes){
    if(robotAdapter != NULL)  {
        robotAdapter->sendPath(changes);
        ofLog() << "Sending changes " << changes;
    }
}			
