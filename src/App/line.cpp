
#include "line.h"

Line::Line(){
    for(int i = 0; i < BOARD_SIZE; i++)
        board[i] = false;
}

void Line::toggle(int i){
    board[i] = !board[i];
}

void Line::set(int i, bool v){
    board[i] = v;
}

bool Line::get(int i){
    return board[i];
}

void Line::draw(){
    
    ofPushMatrix();
    ofPushStyle();
    
    int s = CELL_SIZE;
    
    for(int i = 0; i < BOARD_SIZE; i++){
        
        ofFill();
        ofSetColor(100);
        
        if(board[i])
            ofSetColor(255);
        
        ofDrawRectangle(0, 0, s, s);
        
        ofSetColor(255);
        ofNoFill();
        ofDrawRectangle(0, 0, s, s);
        
        ofTranslate(s, 0);
    }
    
    ofPopMatrix();
    ofPopStyle();
}

string Line::toString(){
    string s = "";
    for(int i = 0; i < BOARD_SIZE; i++){
        if(board[i])
            s+= '1';
        else
            s += '0';
    }
    return s;
    
}
