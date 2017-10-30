#include "SerialAdapter.h"


SerialAdapter::SerialAdapter(App *a){
    app = a;
    bOnline = false;
    ofAddListener(ofEvents().update, this, &SerialAdapter::update);
    
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    
    serial.setup(0, 9600);
    serial.flush();
    prevTempo = -1;
}

SerialAdapter::~SerialAdapter(){
    serial.close();
}

void SerialAdapter::update(ofEventArgs &args){
    app->bArduinoOnline = bOnline;
    sendTempo();
    readBoard();
    
    app->bInverseMidi = app->extras[0];
    app->bSpeed = app->extras[3];
}

void SerialAdapter::sendTempo(){
    uint8 time = int(ofMap(app->board.cursor, 0, 1, 0, 49));
    
    if(prevTempo != time){
        serial.writeByte(time);
        prevTempo = time;
    }
    
}

void SerialAdapter::readBoard(){

    while ( serial.available() > 0 ){
        int bytesRequired = 3;
        unsigned char bytes[bytesRequired];
        int bytesRemaining = bytesRequired;
        
        unsigned char c = -1;
        while(serial.readByte() != c){
        }
        
        if(!bOnline){
            ofLog() << "Sync.. arduino";
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
        updateBoard(bytes);
    }
}

void SerialAdapter::updateBoard(unsigned char bytes[]){
    int channel = int(bytes[0]);
    unsigned char v = bytes[1];
    for(int i = 0; i < 8; i ++){
        app->board.set(channel, i, bool(v % 2));
        v /= 2;
    }
    v = bytes[2];
    
    for(int i = 0; i < 4; i ++){
        app->board.set(channel, i + 8, bool(v % 2));
        v /= 2;
    }
    
    
    for(int i = 0; i < 4; i ++){
        app->prevExtras[i] = app->extras[i];
    }
    
    if(channel == 4){
        app->extras[0] = bool(v % 2);
        v /= 2;
        app->extras[1] = bool(v % 2);
        v /= 2;
    }
    
    if(channel == 1){
        app->extras[2] = bool(v % 2);
        v /= 2;
        app->extras[3] = bool(v % 2);
        v /= 2;
    }
    
    
    if( app->extras[1] != app->prevExtras[1] ){
        app->bFilter = true;
    }
    
    if( app->extras[2] != app->prevExtras[2] ){
        app->bChangeMidi = true;
    }
}

