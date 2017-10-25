//
//  OscSender.hpp
//  mangaPlayer
//
//  Created by miguel on 25/10/2017.
//

#ifndef OscSender_hpp
#define OscSender_hpp

#include "ofMain.h"
#include "ofxOsc.h"
#include "app.h"

class OscSender{
    ofxOscSender *sender;
    App *app;
public:
    OscSender();
    
    ~OscSender();
    
    void sendPath(string path);
    void sendTest();
    void sendTestTwo();
    void sendTestAll();
    void sendZero();
};

#endif /* OscSender_hpp */
