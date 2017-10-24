//
//  RobotAdapter.hpp
//  mangaPlayer
//
//  Created by miguel on 23/10/2017.
//

#ifndef RobotAdapter_h
#define RobotAdapter_h

#include "ofMain.h"
#include "ofxOsc.h"
#include "app.h"

class RobotAdapter{
    ofxOscSender  *sender;
    App *app;
    float lastTime;
public:
    RobotAdapter(App *a);
    
    ~RobotAdapter();
    bool bOnline;
    void update(ofEventArgs &args);
};

#endif /* RobotAdapter_hpp */
