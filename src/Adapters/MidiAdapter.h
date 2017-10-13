//
//  MidiAdapter.hpp
//  emptyScafold
//
//  Created by miguel on 05/10/2017.
//
//

#ifndef MidiAdapter_h
#define MidiAdapter_h



#include "ofMain.h"
#include "app.h"
#include "ofxMidi.h"


class MidiAdapter: public ofxMidiListener{
    
    App *app;
    ofxMidiOut midiOut;
    
    void newMidiMessage(ofxMidiMessage& eventArgs);
    void keyPressed(ofKeyEventArgs& eventArgs);
    
    stringstream text;
    
    ofxMidiIn midiIn;
    
    int channel;
    
    unsigned int currentPgm;
    int note, velocity;
    int pan, bend, touch, polytouch;
    
    bool bNote;
    float initNoteTime;
    
    int subBeat;
    
    void sendNotes();
    
public:
    MidiAdapter(App *a);
    
    ~MidiAdapter();
    bool bOnline;
};

#endif /* MidiAdapter_hpp */
