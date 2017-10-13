#include "app.h"


App::App():BaseApp(){
    bPredictorOnline = false;
}

void App::drawBoard(int x, int y){
    board.draw(x, y);
}

void App::keyPressed (int key){
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

void App::mousePressed(int x, int y, int button){
    board.click(x, y);
};
