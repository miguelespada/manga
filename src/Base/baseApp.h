#ifndef __baseApp__
#define __baseApp__

#include "ofMain.h"
#include "baseState.h"
#include "assets.h"

class BaseApp
{
    
protected:
    class BaseState *current_state;
    Assets *assets;
    
public:
    BaseApp();
    
    void setCurrentState(BaseState *s);
    virtual void keyPressed(ofKeyEventArgs& eventArgs);
    void update(ofEventArgs &args);
    virtual void keyPressed(int key)=0;
    void update();
    void draw();
    void next();
    void reset();
    
    int w, h;
    float scale = 1;
    
    bool bInfo;
    
    
    void toggleFullScreen();
    
    bool bConnected;
    
    Assets *getAssets();
    
};

#endif
