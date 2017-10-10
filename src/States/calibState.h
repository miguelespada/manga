#ifndef __Calib__state__
#define __Calib__state__

#include "baseState.h"
#include "app.h"


class CalibState: public BaseState
{
    
public:
    CalibState(App *a);
    ~CalibState();
    std::string toString() { return "Calib"; }
    void update();
    void draw();
    void next();
    void reset();
    void keyPressed(int key){};
};

#endif
