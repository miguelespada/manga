//
//  OscSender.cpp
//  mangaPlayer
//
//  Created by miguel on 25/10/2017.
//

#include "OscSender.h"

#include "assets.h"


OscSender::OscSender(){
    int localPort = Assets::getInstance()->getLocalPort();
    sender = new ofxOscSender();
    
    sender->setup("localhost", localPort);
    ofLog() << "Sending OSC to " << localPort << endl;
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
}

void OscSender::sendTestTwo(){
}
