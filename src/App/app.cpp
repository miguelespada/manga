#include "app.h"


App::App():BaseApp(){
    bPredictorOnline = true;
    bAbletonOnline = true;
    bArduinoOnline = true;
    bRobotDriverOnline = true;
    midiInstrument = 1;
    bRotate = false;
    bRobotBusy = false;
    bInverseMidi = false;
    
    bAutoUpdatePredictions = Assets::getInstance()->getAutoUpdatePredictions();
    
    for(int i = 0; i < 4; i ++){
        extras[i] = false;
    }
    
    
    idleMessages.push_back("Let's play");
    idleMessages.push_back("Let's rock");
    idleMessages.push_back("Play with me");
}

void App::drawBoard(int x, int y){
    board.draw(x, y);
}

void App::drawExtras(int x, int y){
    
    for(int i = 0; i < 4; i ++){
        ofSetColor(255, 0, 0);
        if(extras[i])
            ofSetColor(0, 0, 255);
        ofDrawCircle(x + i * 25, y, 10);
    }
}

void App::nextMidiInstrument(){
    midiInstrument += 1;
    if(midiInstrument == 4)
        midiInstrument = 1;
}

void App::keyPressed (int key){
    if(key >= '1' && key <= '3'){
        midiInstrument = key - '0';
    }
    else{
       switch (key) {
           case 'f':
                scale = 1;
                toggleFullScreen();
               break;
           case ' ':
               next();
               break;
           case 'a':
               bAutoUpdatePredictions = !bAutoUpdatePredictions;
               break;
           case 'r':
               bRotate = !bRotate;
               break;
           case 'i':
               bInverseMidi = !bInverseMidi;
               break;
        default:
            break;
       }
    }
}

void App::mousePressed(int x, int y, int button){
    board.click(x, y);
}

bool App::online(){
    return bArduinoOnline && bPredictorOnline && bAbletonOnline && bRobotDriverOnline;
};
