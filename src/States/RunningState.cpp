#include "states.h"

RunningState::RunningState(App *a):BaseState(a){
    BaseState::initialize();
    
    ofHideCursor();
    ofSetWindowShape(1080 * 2, 1920);
    ofSetWindowPosition(0, 0);
    
    lastHumanMessageChange = -1;
    nMachineMsg = 0;
    lastMachineMessageChange = -1;
    nHumanMsg = 0;
    a->bRobotEnabled = true;
};

RunningState::~RunningState(){
    
    
    ofSetFullscreen(false);
    ofSetWindowShape(600, 600);
    ofShowCursor();

};

void RunningState::draw(){
    
    ofBackground(255);
    ofSetColor(0);
    
    if(ofGetElapsedTimef() - lastMachineMessageChange > 1 && ofGetElapsedTimef() - app->board.lastMachineActivity < 0.5 ){
        lastMachineMessageChange = ofGetElapsedTimef();
        nMachineMsg = int(ofRandom(app->rockMessages.size()));
    }
    
    if(ofGetElapsedTimef() - lastHumanMessageChange > 1 && ofGetElapsedTimef() - app->board.lastHumanActivity < 0.5 ){
        lastHumanMessageChange = ofGetElapsedTimef();
        nHumanMsg = int(ofRandom(app->humanMessages.size()));
    }
    
    string s = app->rockMessages[nMachineMsg];
    ofRectangle boundingBox  =  Assets::getInstance()->font.getStringBoundingBox(s, 0, 0);
    Assets::getInstance()->font.drawString(s, ofGetWidth() / 2 - boundingBox.width / 2, ofGetHeight() / 4);

    s = app->humanMessages[nHumanMsg];
    boundingBox  =  Assets::getInstance()->font.getStringBoundingBox(s, 0, 0);
    Assets::getInstance()->font.drawString(s, 3* ofGetWidth() / 2 - boundingBox.width / 2, ofGetHeight() / 4);
	
    
    app->drawBoard(1080/2 - CELL_SIZE * 6, 1400);
    app->drawBoard(3*1080/2 - CELL_SIZE * 6 , 1400);
};

void RunningState::update(){
};


void RunningState::next(){
    app->setCurrentState(new StandbyState(app));
    delete this;
};


void RunningState::reset(){
    app->setCurrentState(new StandbyState(app));
    delete this;
}

