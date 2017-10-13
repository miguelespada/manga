//
//  httpAdapter.cpp
//  mangaPlayer
//
//  Created by miguel on 09/10/2017.
//
//

#include "httpAdapter.h"
#include "states.h"

httpAdapter::httpAdapter(App *a){
    app = a;
    bOnline = false;
    ofAddListener(ofEvents().update, this, &httpAdapter::update);
    
    string baseRoute = "http://127.0.0.1:5000/";
    
    serviceUrl = baseRoute + "ping";
    predictorUrl = baseRoute + "predict/";
    
    lastTime = ofGetElapsedTimef();
    
    ofAddListener(ofEvents().keyPressed, this, &httpAdapter::keyPressed);
    bMustPredict = false;
}

httpAdapter::~httpAdapter(){
}

void httpAdapter::update(ofEventArgs &args){
    app->bPredictorOnline = bOnline;
    
    if(isOnline() && !bOnline){
        bOnline = true;
        ofLogNotice() << "Predictor is online";
    }
    
    
    if(app->board.lastHumanActivity > 0){
    if(ofGetElapsedTimef() - app->board.lastHumanActivity> Assets::getInstance()->getInactivityTime()){
        predict();
        app->board.lastHumanActivity = -1;
    }
    }
    
       
//    if(ofGetElapsedTimef() -  app->board.lastActivity > Assets::getInstance()->getMaxIdleTime() && !bMustPredict){
//        predict();
//    }
}

bool httpAdapter::isOnline(){
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

void httpAdapter::predict(){
    string board = app->board.toString();
    bool parsingSuccessful = result.open(predictorUrl + board);
    string prediction =  result.get("prediction", "").asString();
    app->board.fromString(prediction);
}

void httpAdapter::keyPressed(ofKeyEventArgs& eventArgs){
    if (eventArgs.key == 'p') {
        predict();
    }
}


