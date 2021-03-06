


#ifndef board_hpp
#define board_hpp

#include "ofMain.h"
#include "line.h"

#define ROWS 6

class Board
{
    Line board[ROWS];
    ofPoint anchor;
    
public:
    Board();
    ~Board(){};
    
    void draw(int x, int y);
    
    void toggle(int j, int i);
    void set(int j,  int i, bool v);
    bool get(int j,  int i);
    
    void drawCursor();
    void setCursor(float c);
    float cursor = 0;
    
    int getSize();
    
    void click(int x, int y);
    
    int getNumRows();
    
    string toString();
    
    vector<ofPoint>  fromPrediction(string values,  bool bAutoUpdate);
    vector<ofPoint>  changesToClean(bool bAutoUpdate);
    
    int pitchToRow(int pitch);
    
    float lastHumanActivity;
    float lastMachineActivity;
    
    void setHumanActivity();
    void unsetHumanActivity();
    
    
    void setMachineActivity();
    void unsetMachineActivity();
    
    int lastNumberOfChanges;
    
    bool isClean();
};


#endif /* board_hpp */
