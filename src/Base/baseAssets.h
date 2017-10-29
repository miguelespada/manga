
#ifndef __baseAssets__
#define __baseAssets__

#include "ofMain.h"
#include "ofxJSON.h"


class BaseAssets{
public:
    BaseAssets();
    Json::Value getData(string key);
    ofxJSONElement settings;
    
    ofTrueTypeFont font;
    
    virtual void loadAssets()=0;
    
    
    void loadImage(ofImage *image, string filename);
    void loadVideo(ofVideoPlayer *video, string filename);
    void stopVideos();
    
    
    
    private:
        vector<ofVideoPlayer*> videos;
    
};


#endif
