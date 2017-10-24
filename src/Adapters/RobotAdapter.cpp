//
//  RobotAdapter.cpp
//  mangaPlayer
//
//  Created by miguel on 23/10/2017.
//

#include "RobotAdapter.h"
#include "assets.h"


RobotAdapter::RobotAdapter(App *a){
    app = a;
    
    int remotePort = Assets::getInstance()->getRemotePort();
    string remoteHost = Assets::getInstance()->getRemoteHost();
    ofLogNotice() << "sending osc messages to port " << remoteHost << ":" << remotePort;
    bOnline = false;
    
    sender = new ofxOscSender();
    sender->setup("localhost", remotePort);
    ofAddListener(ofEvents().update, this, &RobotAdapter::update);
    lastTime = ofGetElapsedTimef();
}

RobotAdapter::~RobotAdapter(){
    delete sender;
}


void RobotAdapter::update(ofEventArgs &args){
    if(ofGetElapsedTimef() - lastTime > 3){
        lastTime = ofGetElapsedTimef();
        ofxOscMessage msg;
        msg.setAddress("/ping");
        sender->sendMessage(msg);
    }
}


