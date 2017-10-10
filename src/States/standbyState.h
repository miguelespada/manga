
#ifndef __standby__state__
#define __standby__state__

#include "baseState.h"
#include "app.h"


class StandbyState: public BaseState
{
    int bpm = 120;
    int subBeat;
    
public:
    StandbyState(App *a);
    ~StandbyState();
    std::string toString() { return "standby"; }
    void update();
    void draw();
    void next();
    void reset();
    void keyPressed(int key){};
};

#endif
