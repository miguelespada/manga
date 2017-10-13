#ifndef __CheckAbletonOnline__state__
#define __CheckAbletonOnline__state__

#include "baseState.h"
#include "app.h"


class CheckAbletonOnlineState: public BaseState
{
    
public:
    CheckAbletonOnlineState(App *a);
    ~CheckAbletonOnlineState();
    std::string toString() { return "CheckAbletonOnline"; }
    void update();
    void draw();
    void next();
    void reset();
    void keyPressed(int key){};
};

#endif
