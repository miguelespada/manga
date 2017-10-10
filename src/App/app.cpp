#include "app.h"


App::App():BaseApp(){
}

void App::drawBoard(int x, int y){
    
    ofPushMatrix();
    ofTranslate(x, y);
    board.draw();
    ofPopMatrix();
}

void App::keyPressed (int key){
    if(isdigit(key)){
        board.toggle(key - '0');
    }
    
    
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
