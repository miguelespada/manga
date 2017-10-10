#include "board.h"

Board::Board(){
    for(int i = 0; i < ROWS; i++)
        board[i] = Line();
    
    cursor = 0;
}

void Board::toggle(int j, int  i){
    board[j].set(i, !board[j].get(i));
}

void Board::set(int j, int i, bool v){
    board[j].set(i, v);
}

bool Board::get(int j, int i){
    return board[j].get(i);
}

void Board::click(int x, int y){
    x = (x - anchor.x);
    y = (y - anchor.y);
    
    int i = x / CELL_SIZE;
    int j = y / CELL_SIZE;
    
    
    toggle(j, i);
}

void Board::draw(int x, int y){
    anchor.x = x;
    anchor.y = y;
    
    ofPushMatrix();
    ofTranslate(anchor);
    for(int i = 0; i < ROWS; i++){
        board[i].draw();
        ofTranslate(0, CELL_SIZE);
    }
    
    ofPopMatrix();
    ofPushMatrix();
    ofTranslate(anchor);
    drawCursor();
    
    ofPopMatrix();
    
}

void Board::drawCursor(){
    float pos = ofMap(cursor, 0, 1, 0, CELL_SIZE * BOARD_SIZE );

    ofSetColor(255, 0, 0);
    ofDrawLine(pos, 0, pos, CELL_SIZE * ROWS);
}


void Board::setCursor(float c){
    cursor = c;
}

int Board::getSize(){
    return BOARD_SIZE;
}

int Board::getNumRows(){
    return ROWS;
}

string Board::serializeRows(){
    return "abc";
}
