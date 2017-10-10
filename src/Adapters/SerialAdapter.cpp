#include "SerialAdapter.h"


SerialAdapter::SerialAdapter(App *a){
    app = a;
    bOnline = false;
    ofAddListener(ofEvents().update, this, &SerialAdapter::update);
    
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    
    serial.setup(0, 9600);
    serial.flush();
}

SerialAdapter::~SerialAdapter(){
    serial.close();
}

void SerialAdapter::update(ofEventArgs &args){

    
    int bytesRequired = 2;
    unsigned char bytes[bytesRequired];
    int bytesRemaining = bytesRequired;

    if ( serial.available() > 0 ){
        
        unsigned char c = -1;
        while(serial.readByte() != c){
            
        }
        
        if(!bOnline){
            ofLog() << "Sync..";
            bOnline = true;
        }
        
        while ( bytesRemaining > 0 ) {
            if ( serial.available() > 0 ) {
                int bytesArrayOffset = bytesRequired - bytesRemaining;
                
                int result = serial.readBytes( &bytes[bytesArrayOffset],
                                              bytesRemaining );
                
                if ( result == OF_SERIAL_ERROR )
                {
                    ofLog( OF_LOG_ERROR, "unrecoverable error reading from serial" );
                    break;
                }
                else if ( result == OF_SERIAL_NO_DATA )
                {
                
                }
                else {
                    bytesRemaining -= result;
                }
            }
        }
        
        unsigned char v = bytes[0];
        
        for(int i = 0; i < 8; i ++){
            app->board.set(0, i, bool(v % 2));
            v /= 2;
        }
        
        v = bytes[1];
        for(int i = 0; i < 4; i ++){
            app->board.set(0, i + 8, bool(v % 2));
            v /= 2;
        }
    }
}
