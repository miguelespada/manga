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
    
    bool bPredictorOnline;
    bool bAbletonOnline;
    bool bArduinoOnline;
    bool bRobotOnline;
    
    int midiInstrument;
    
    bool online();
    
    bool extras[4];
    void drawExtras(int x, int y);
    
    
};


#endif
