//
//  line.hpp
//  mangaPlayer
//
//  Created by miguel on 10/10/2017.
//
//



#define CELL_SIZE 40
#define BOARD_SIZE 12

#ifndef line_h
#define line_h


#include "ofMain.h"


class Line
{
    
    bool board[BOARD_SIZE];
    
public:
    Line();
    ~Line(){};
    
    void draw();
    
    void toggle(int i);
    bool set(int i, bool v);
    bool get(int i);
    
    string toString();
    
    bool isClean();
};


#endif /* line_h */
