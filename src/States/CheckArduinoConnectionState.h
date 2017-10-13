#ifndef __CheckArduinoConnection__state__
#define __CheckArduinoConnection__state__

#include "baseState.h"
#include "app.h"


class CheckArduinoConnectionState: public BaseState
{
    
public:
    CheckArduinoConnectionState(App *a);
    ~CheckArduinoConnectionState();
    std::string toString() { return "CheckArduinoConnection"; }
    void update();
    void draw();
    void next();
    void reset();
    void keyPressed(int key){};
};

#endif
