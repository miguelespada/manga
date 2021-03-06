
#ifndef SerialAdapter_h
#define SerialAdapter_h


#include "ofMain.h"
#include "app.h"


class SerialAdapter{
    App *app;
    ofSerial serial;
    uint8 prevTempo; 
public:
    SerialAdapter(App *a);
    
    ~SerialAdapter();
    bool bOnline;
    void update(ofEventArgs &args);
    
    void sendTempo();
    void readBoard();
    void updateBoard(unsigned char bytes[]);
};



#endif
