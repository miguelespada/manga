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

class httpAdapter{
    App *app;
    ofxJSONElement result;
    string serviceUrl;
    string predictorUrl;
    
    float lastTime;
    
public:
    httpAdapter(App *a);
    void keyPressed(ofKeyEventArgs& eventArgs);
    
    ~httpAdapter();
    bool bOnline;
    void update(ofEventArgs &args);
    bool isOnline();
    
    void predict(string board);
};




#endif /* httpAdapter_hpp */
