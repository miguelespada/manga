//
//  board.hpp
//  mangaPlayer
//
//  Created by miguel on 05/10/2017.
//
//

#ifndef board_hpp
#define board_hpp

#include "ofMain.h"

#define BOARD_SIZE 12

class Board
{
    
    bool board[BOARD_SIZE];
    
public:
    Board();
    ~Board(){};
    
    void draw();
    void toggle(int i);
    void set(int i, bool v);
    
    string toString();
    bool get(int i);
    
    void drawCursor();
    void setCursor(float c);
    
    float cursor = 0;
    
    int getSize();
    
};


#endif /* board_hpp */
