//
//  OscAdapter.cpp
//  carrousel
//
//  Created by miguel on 14/10/14.
//
//

#include "OscAdapter.h"
#include "assets.h"


OscAdapter::OscAdapter(App *a){
    app = a;
    int localPort = Assets::getInstance()->getLocalPort();
    receiver = new ofxOscReceiver;
    receiver->setup(localPort);
    ofLogNotice() << "listening for osc messages on port " << localPort;
    bOnline = false;
    ofAddListener(ofEvents().update, this, &OscAdapter::update);
    app->bRobotOnline = bOnline;
}

OscAdapter::~OscAdapter(){
    delete receiver;
}

void OscAdapter::update(ofEventArgs &args){
    
    app->bRobotOnline = bOnline;
    
    while(receiver->hasWaitingMessages()){
        ofxOscMessage m;
        receiver->getNextMessage(&m);
        if(m.getAddress() == "/reset") app->reset();
        if(m.getAddress() == "/ping") bOnline = true;
    }
}
