#ifndef __CheckPredictorConnection__state__
#define __CheckPredictorConnection__state__

#include "baseState.h"
#include "app.h"


class CheckPredictorConnectionState: public BaseState
{
    
public:
    CheckPredictorConnectionState(App *a);
    ~CheckPredictorConnectionState();
    std::string toString() { return "CheckPredictorConnection"; }
    void update();
    void draw();
    void next();
    void reset();
    void keyPressed(int key){};
};

#endif
