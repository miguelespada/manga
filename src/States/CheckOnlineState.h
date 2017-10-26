#ifndef __CheckOnlineState__state__
#define __CheckOnlineState__state__

#include "baseState.h"
#include "app.h"


class CheckOnlineState: public BaseState
{
    
public:
    CheckOnlineState(App *a);
    ~CheckOnlineState();
    std::string toString() { return "CheckOnline"; }
    void update();
    void draw();
    void next();
    void reset();
    void keyPressed(int key){};
};

#endif
