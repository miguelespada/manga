//
//  OscSender.cpp
//  mangaPlayer
//
//  Created by miguel on 25/10/2017.
//

#include "OscSender.h"

#include "assets.h"


OscSender::OscSender(){
    int remotePort = Assets::getInstance()->getControllerPort();
    string remoteHost = Assets::getInstance()->getControllerHost();
    sender = new ofxOscSender();
    
    sender->setup(remoteHost, remotePort);
    ofLog() << "Sending OSC to " << remoteHost << ":" << remotePort << endl;
}

OscSender::~OscSender(){
    delete sender;
}

void OscSender::sendPath(string path){
    ofxOscMessage msg;
    msg.setAddress("/path");
    msg.addStringArg(path);
    sender->sendMessage(msg);
}

void OscSender::sendTestAll(){
}

void OscSender::sendZero(){
    ofxOscMessage msg;
    msg.setAddress("/zero");
    sender->sendMessage(msg);
    
}

void OscSender::sendTestTwo(){
    ofxOscMessage msg;
    msg.setAddress("/one");
    sender->sendMessage(msg);
}
