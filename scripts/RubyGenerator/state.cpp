#include "states.h"

<%= name %>State::<%= name %>State(App *a):BaseState(a){
    BaseState::initialize();
};

<%= name %>State::~<%= name %>State(){
};

void <%= name %>State::draw(){
    ofBackground(0);
    ofSetColor(255);
    ofDrawBitmapString(toString(), 10, 10);
};

void <%= name %>State::update(){
};


void <%= name %>State::next(){
    app->setCurrentState(new <%= name %>State(app));
    delete this;
};


void <%= name %>State::reset(){
    app->setCurrentState(new StandbyState(app));
    delete this;
}

