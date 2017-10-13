#include "app.h"


App::App():BaseApp(){
    bPredictorOnline = false;
    bAbletonOnline = false;
    bArduinoOnline = false;
    midiInstrument = 10;
}

void App::drawBoard(int x, int y){
    board.draw(x, y);
}

void App::keyPressed (int key){
    if(isalnum(key)){
        if(key == '0')
            midiInstrument = 10;
        else
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
        default:
            break;
       }
    }
}

void App::mousePressed(int x, int y, int button){
    board.click(x, y);
};
