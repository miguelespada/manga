


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
    
    void click(int x, int y, float scale);
};


#endif /* board_hpp */
