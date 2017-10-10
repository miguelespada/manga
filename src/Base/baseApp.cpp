#include "baseApp.h"


BaseApp::BaseApp(){
    ofLogNotice() << "Initializing app...";
    assets = (Assets *)Assets::getInstance();

    // Register events and actions
    ofAddListener(ofEvents().keyPressed, this, &BaseApp::keyPressed);
    ofAddListener(ofEvents().update, this, &BaseApp::update);
        
    current_state = NULL;
}

void BaseApp::setCurrentState(BaseState *s){
    current_state = s;
}

void BaseApp::next(){
    if(current_state)
        current_state->next();
}

void BaseApp::reset(){
    if(current_state)
        current_state->reset();
}

void BaseApp::update(){
    if(current_state)
        current_state->update();
}

void BaseApp::update(ofEventArgs &args){
    update();
}


void BaseApp::draw(){
    ofPushStyle();
    ofPushMatrix();
    
    current_state->draw();
    
    ofPopMatrix();
    ofPopStyle();
}

Assets * BaseApp::getAssets(){
    return assets;
}

void BaseApp::keyPressed (ofKeyEventArgs& eventArgs){
    current_state->keyPressed(eventArgs.key);
    keyPressed(eventArgs.key);
}

void BaseApp::toggleFullScreen(){
    bInfo = !bInfo;
    if(!bInfo)
        ofSetWindowPosition(Assets::getInstance()->getXpos(), 0);
    
    ofToggleFullscreen();
    
    if(bInfo)
        ofSetWindowPosition(0, 0);
}
