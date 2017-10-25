//
//  httpAdapter.hpp
//  mangaPlayer
//
//  Created by miguel on 09/10/2017.
//
//

#ifndef httpAdapter_h
#define httpAdapter_h

#include "ofMain.h"
#include "ofxJSON.h"
#include "app.h"
#include "OscSender.h"

class httpAdapter{
    App *app;
    ofxJSONElement result;
    string serviceUrl;
    string predictorUrl;
    string plannerUrl;
    
    float lastTime;
    
    OscSender *oscSender;
    
public:
    httpAdapter(App *a);
    void keyPressed(ofKeyEventArgs& eventArgs);
    
    ~httpAdapter();
    bool bOnline;
    void update(ofEventArgs &args);
    bool isOnline();
    
    bool bMustPredict;
    void predict();
    
    string serializeChanges(vector<ofPoint> changes);
    void plan(string changes);
};




#endif /* httpAdapter_hpp */
