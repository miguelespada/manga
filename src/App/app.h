#ifndef __app__
#define __app__

#include "baseApp.h"
#include "board.h"

class App: public BaseApp
{
    
    
public:
    App();

    ~App(){};
    
    void keyPressed (int key);
    void drawBoard(int x, int y);
    Board  board;
    
    void mousePressed(int x, int y, int button);
};


#endif
