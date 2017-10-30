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
    bool bRobotDriverOnline;
    bool bRotate;
    
    bool bAutoUpdatePredictions;
    
    bool bRobotBusy;
    int midiInstrument;
    void nextMidiInstrument();
    bool bInverseMidi;
    
    bool bFilter;
    bool bSpeed;
    bool bChangeMidi;
    
    bool bRobotEnabled;
    
    bool online();
    
    bool extras[4];
    bool prevExtras[4];
    void drawExtras(int x, int y);
    
    vector<string> rockMessages;
    vector<string> humanMessages;
    
    
};


#endif
