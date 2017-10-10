
#ifndef SerialAdapter_h
#define SerialAdapter_h


#include "ofMain.h"
#include "app.h"


class SerialAdapter{
    App *app;
    ofSerial serial;
    
public:
    SerialAdapter(App *a);
    
    ~SerialAdapter();
    bool bOnline;
    void update(ofEventArgs &args);
};



#endif
