//
//  MidiAdapter.cpp
//  emptyScafold
//
//  Created by miguel on 05/10/2017.
//
//

#include "MidiAdapter.h"

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
}

MidiAdapter::~MidiAdapter(){
    midiOut.closePort();
    midiIn.closePort();
    midiIn.removeListener(this);
}


void MidiAdapter::newMidiMessage(ofxMidiMessage& msg) {
    
    if(msg.getStatusString(msg.status) == "Start"){
        subBeat = 0;
    }
        
    if(msg.getStatusString(msg.status) == "Time Clock"){
        
        int totalSamplers = app->board.getSize() * SUBSAMPLERS ;
        
        subBeat = (subBeat + 1) % totalSamplers;
    
        app->board.setCursor(ofMap(subBeat, 0, totalSamplers, 0, 1));
        
        if(app->board.get(subBeat / SUBSAMPLERS) && subBeat % SUBSAMPLERS == 0){
            midiOut.sendNoteOn(10, 38,  80);
            midiOut.sendNoteOff(10, 38,  80);
        }
    }
    
    
}

