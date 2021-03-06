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
    
    
    int remotePort = Assets::getInstance()->getControllerPort();
    string remoteHost = Assets::getInstance()->getControllerHost();
    int localPort = Assets::getInstance()->getLocalPort();
    
    sender = new ofxOscSender();
    
    sender->setup(remoteHost, remotePort);
    ofLog() << "Sending OSC to " << remoteHost << ":" << remotePort << endl;
    
    receiver = new ofxOscReceiver;
    receiver->setup(localPort);
    ofLogNotice() << "Listening OSC on port " << localPort;
    
    bOnline = false;
    
    ofAddListener(ofEvents().update, this, &RobotAdapter::update);
    lastTime = ofGetElapsedTimef();
    
    sendZero();
}

RobotAdapter::~RobotAdapter(){
    delete sender;
    delete receiver;
}


void RobotAdapter::update(ofEventArgs &args){
    if(ofGetElapsedTimef() - lastTime > 3){
        lastTime = ofGetElapsedTimef();
        ofxOscMessage msg;
        msg.setAddress("/ping");
        sender->sendMessage(msg);
        bOnline = false;
    }
    
    app->bRobotDriverOnline = bOnline;
    
    while(receiver->hasWaitingMessages()){
        ofxOscMessage m;
        receiver->getNextMessage(&m);
        
        if(m.getAddress() == "/reset") app->reset();
        if(m.getAddress() == "/ping") bOnline = true;
        if(m.getAddress() == "/busy") app->bRobotBusy = true;
        if(m.getAddress() == "/noBusy") app->bRobotBusy = false;
        
    }
}

void RobotAdapter::sendPath(string path){
    
    if(app->bRobotEnabled){
        if(!app->bRobotBusy){
            ofxOscMessage msg;
            msg.setAddress("/path");
            msg.addStringArg(path);
            sender->sendMessage(msg);
        }
        else{
            ofLog() << "Prediction skipped";
        }
    }
}


void RobotAdapter::sendZero(){
        ofxOscMessage msg;
        msg.setAddress("/zero");
        sender->sendMessage(msg);
}

void RobotAdapter::sendTest(){
    
    if(!app->bRobotBusy){
        ofxOscMessage msg;
        msg.setAddress("/test");
        sender->sendMessage(msg);
    }
}


