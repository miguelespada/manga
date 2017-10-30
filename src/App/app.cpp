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
    bRobotEnabled = false;
    bFilter = false;
    bSpeed = false;
    bChangeMidi = false;
    
    bAutoUpdatePredictions = Assets::getInstance()->getAutoUpdatePredictions();
    
    for(int i = 0; i < 4; i ++){
        extras[i] = false;
        prevExtras[i] = false;
    }
    
    
    rockMessages.push_back("I'd rather be dead than cool.\nKurt Cobain");
    rockMessages.push_back("Darling,\nmy attitude is 'fuck it'\nI'm doing everything\nwith everyone.\nFreddie Mercury");
    rockMessages.push_back("Society has traditionally\nalways tried to find\nscapegoats for its problems.\nWell here I am.\nMarilyn Manson");
    rockMessages.push_back("Christians are a lot\n like dinosaurs\n- about to become extinct.\nMarilyn Manson");
    rockMessages.push_back("I'm not a woman.\nI'm a force of nature.\nCourtney Love");
    
    
    humanMessages.push_back("Even randonmess\nis within a set of\nparamenters; thresholds...\nClyde DeSouza");
    humanMessages.push_back("By 2029, computers will have\nemotional intelligence\nand be convincing as people\nRay Kurzweil");
    humanMessages.push_back("By the 2030s,\nthe nonbiological portion of our\nintelligence will predominate.\nRay Kurzweil");
    humanMessages.push_back("As order exponentially\nincreases, time exponentially\nspeeds up.\nRay Kurzweil");
    humanMessages.push_back("The cortex craves for\ninformation, but\nit can longer contain\nand creatively process it all.\nStelarc");
    humanMessages.push_back("The risk of something\nseriously dangerous\nhappening is in the five-year\ntimeframe. 10 years at most.\nEllon Musk");
    humanMessages.push_back("The real question is,\nwhen will we draft an\nartificial intelligence\nbill of rights?\nGray Scott");
    humanMessages.push_back("So instead of\nartificial intelligence,\nI think we'll augment\nour intelligence.\nGinni Rometty");
    humanMessages.push_back("You have to talk about\nThe Terminator if you're\ntalking about artificial intelligence.\nGray Scott");
    humanMessages.push_back("The key to artificial intelligence\nhas always been the\nrepresentation.\nJeff Hawkins");
    humanMessages.push_back("Some people worry\nthat artificial intelligence\nwill make us feel inferior,\nbut then, anybody in his right\nmind should have an inferiority\ncomplex every time he looks\nat a flower.\nAlan Kay");
    humanMessages.push_back("The sad thing about\nartificial intelligence is\nthat it lacks artifice and\ntherefore intelligence.\nJean Baudrillard");
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
