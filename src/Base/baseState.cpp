#include "baseState.h"

BaseState::BaseState(App *a){
    initTime = ofGetElapsedTimef();
    app = a;
}

void BaseState::initialize(){
    ofLogNotice() << "State: " << toString();
}
