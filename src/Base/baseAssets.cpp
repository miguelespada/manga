#include "baseAssets.h"

BaseAssets::BaseAssets(){
    string path = ofToDataPath("settings.json");

    ofLogNotice() << "Loading settings from: " << path;
    settings.open(path);
    ofTrueTypeFont::setGlobalDpi(72);
    
    font.loadFont("ProximaNova-Bold.otf", 128);
}


void BaseAssets::loadVideo(ofVideoPlayer *video, string filename){
    ofLogNotice() << "Loading: " << ofToDataPath("assets/" + filename);
    video->load(ofToDataPath("assets/" + filename));
    videos.push_back(video);
}

void BaseAssets::loadImage(ofImage *image, string filename){
    ofLogNotice() << "Loading: " << filename;
    image->load(ofToDataPath("assets/" + filename));
}

void BaseAssets::stopVideos(){
    cout << "Stopping videos" << endl;
    for(vector<ofVideoPlayer*>::iterator it = videos.begin(); it != videos.end(); ++it)
        (*it)->stop();
}

Json::Value BaseAssets::getData(string key){
    return settings[key];
}
