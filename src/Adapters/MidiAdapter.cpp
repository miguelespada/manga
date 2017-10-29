//
//  MidiAdapter.cpp
//  emptyScafold
//
//  Created by miguel on 05/10/2017.
//
//

#include "MidiAdapter.h"
#include "assets.h"

#define SUBSAMPLERS 5

MidiAdapter::MidiAdapter(App *a){
    app = a;
    bOnline = false;
    
    midiOut.listPorts();
    midiOut.openPort(0);
    midiIn.openPort(1);

    midiIn.ignoreTypes(false, false, false);
    midiIn.addListener(this);
    midiIn.setVerbose(true);
    
    bNote = false;
    initNoteTime = ofGetElapsedTimef();
    
    subBeat = 0;
    
    
    ofAddListener(ofEvents().keyPressed, this, &MidiAdapter::keyPressed);
    ofAddListener(ofEvents().keyReleased, this, &MidiAdapter::keyReleased);
    
    app->bAbletonOnline = bOnline;
    
    prevSet = 0;
    midiOut.sendNoteOn(0 + 4, 30);
}

MidiAdapter::~MidiAdapter(){
    midiOut.closePort();
    midiIn.closePort();
    midiIn.removeListener(this);
}


void MidiAdapter::newMidiMessage(ofxMidiMessage& msg) {
    bOnline = true;
    app->bAbletonOnline = bOnline;
    
    if(msg.getStatusString(msg.status) == "Start"){
        subBeat = 0;
    }
        
    if(msg.getStatusString(msg.status) == "Time Clock"){
        int totalSamplers = app->board.getSize() * SUBSAMPLERS ;
        subBeat = (subBeat + 1) % totalSamplers;
        app->board.setCursor(ofMap(subBeat, 0, totalSamplers, 0, 1));
        sendNotes();
    }
}

void MidiAdapter::sendNotes(){
    
    for(int j = 0; j < app->board.getNumRows(); j ++){
        if(app->board.get(j, subBeat / SUBSAMPLERS) && subBeat % SUBSAMPLERS == 0){
            
            midiOut.sendNoteOn(app->midiInstrument, Assets::getInstance()->getMidiNote(j, app->bInverseMidi), 80);
        }
        else{
            midiOut.sendNoteOff(app->midiInstrument, Assets::getInstance()->getMidiNote(j, app->bInverseMidi), 80);
        }
    }
}

void MidiAdapter::keyPressed(ofKeyEventArgs& eventArgs){
    if (eventArgs.key == 't') {
        midiOut.sendControlChange(1, 1, 127);
    }
    
    if(eventArgs.key == '1'){
        
        midiOut.sendNoteOn(prevSet + 4, 30);
        midiOut.sendNoteOn(4, 30);
        prevSet = 0;
    }
    if(eventArgs.key == '2'){
        
        midiOut.sendNoteOn(prevSet + 4, 30);
        midiOut.sendNoteOn(5, 30);
        
        prevSet = 1;
    }
    if(eventArgs.key == '3'){
        
        midiOut.sendNoteOn(prevSet + 4, 30);
        midiOut.sendNoteOn(6, 30);
        prevSet = 2;
    }
    
}

void MidiAdapter::keyReleased(ofKeyEventArgs& eventArgs){
    if (eventArgs.key == 't') {
        midiOut.sendControlChange(1, 1, 1);
    }
}

