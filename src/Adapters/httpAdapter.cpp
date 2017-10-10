//
//  httpAdapter.cpp
//  mangaPlayer
//
//  Created by miguel on 09/10/2017.
//
//

#include "httpAdapter.h"

httpAdapter::httpAdapter(App *a){
    app = a;
    bOnline = false;
    ofAddListener(ofEvents().update, this, &httpAdapter::update);
    
    string baseRoute = "http://127.0.0.1:5000/";
    
    serviceUrl = baseRoute + "ping";
    predictorUrl = baseRoute + "predict/";
    
    lastTime = ofGetElapsedTimef();
    
    
    ofAddListener(ofEvents().keyPressed, this, &httpAdapter::keyPressed);
}

httpAdapter::~httpAdapter(){
}

void httpAdapter::update(ofEventArgs &args){
    if(isOnline() && !bOnline){
        bOnline = true;
        ofLogNotice() << "Predictor is online";
    }

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

void httpAdapter::predict(string board){
    bool parsingSuccessful = result.open(predictorUrl + board);
    
    cout << result.get("ok", "") << endl;
}

void httpAdapter::keyPressed(ofKeyEventArgs& eventArgs){
    if (eventArgs.key == 'p') {
        string board = app->board.serializeRows();
        predict(board);
    }
}


