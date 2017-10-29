#ifndef __Running__state__
#define __Running__state__

#include "baseState.h"
#include "app.h"


class RunningState: public BaseState
{
    float lastMessageChange;
    int nMsg;
public:
    RunningState(App *a);
    ~RunningState();
    std::string toString() { return "Running"; }
    void update();
    void draw();
    void next();
    void reset();
    void keyPressed(int key){};
};

#endif
