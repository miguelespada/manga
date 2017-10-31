#ifndef __assets__
#define __assets__

#include "baseAssets.h"


class Assets: public BaseAssets
{
    static Assets* instance;
    Assets();

    
public:
    ofImage eys;
    ofImage jessica;
    
    static Assets* getInstance();
    void loadAssets();
    
    int getLocalPort();
    string getRemoteHost();
    int getRemotePort();
    
    
    string getControllerHost();
    int getControllerPort();
    
    int getXpos();
    string getServer();
    
    int getMidiNote(int i, bool bInverse);
    
    int getInactivityTime();
    int getMaxIdleTime();
    
    bool getAutoUpdatePredictions();
    
};

#endif
