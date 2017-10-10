#ifndef __State__
#define __State__

#include "ofMain.h"

class App;

class BaseState
{
    
protected:
    App *app;
    float initTime;
    
public:
    BaseState(App *a);
    void initialize();
    
    
    virtual void next()=0;
    virtual string toString()=0;
    virtual void draw()=0;
    virtual void update()=0;
    virtual void reset()=0;
    
    virtual void keyPressed(int key){};
    
    
};


#endif
