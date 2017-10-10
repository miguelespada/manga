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
    
    serviceUrl = "http://127.0.0.1:5000/ping";
    
    lastTime = ofGetElapsedTimef();
}

httpAdapter::~httpAdapter(){
}

void httpAdapter::update(ofEventArgs &args){
    bOnline = isOnline();

}

bool httpAdapter::isOnline(){
    if(ofGetElapsedTimef() - lastTime > 1){
        lastTime = ofGetElapsedTimef();
        
        bool parsingSuccessful = result.open(serviceUrl);
        
        if (parsingSuccessful){
            return true;
        }
        else
        {
            ofLogNotice()  << "Failed to parse JSON";
            return false;
        }
    }
}
