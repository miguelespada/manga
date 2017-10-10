//
//  board.cpp
//  mangaPlayer
//
//  Created by miguel on 05/10/2017.
//
//

#include "board.h"

#define CELL_SIZE 80

Board::Board(){
    for(int i = 0; i < BOARD_SIZE; i++)
        board[i] = false;
    cursor = 0;
}

void Board::toggle(int i){
    board[i] = !board[i];
}



void Board::set(int i, bool v){
    board[i] = v;
}


void Board::draw(){
    
    ofPushMatrix();
    ofPushStyle();
    
    int s = CELL_SIZE;
    
    for(int i = 0; i < BOARD_SIZE; i++){
        ofSetColor(100);
        
        if(board[i])
            ofSetColor(255);
    
        ofDrawRectangle(0, 0, s, s);
        ofTranslate(s, 0);
    }
    
    ofPopMatrix();
    drawCursor();
    ofPopStyle();
}

void Board::drawCursor(){
    float pos = ofMap(cursor, 0, 1, 0, CELL_SIZE * BOARD_SIZE );

    ofSetColor(255, 0, 0);
    ofDrawLine(pos, 0, pos, CELL_SIZE);
}

bool Board::get(int i){
    return board[i];
}

void Board::setCursor(float c){
    cursor = c;
}

string Board::toString(){
    string s;
    for(int i = 0; i < 10; i++){
     
        s += ofToString(board[i]);
        
    }
    s += "\n";
    return s;
}

int Board::getSize(){
    return BOARD_SIZE;
}
