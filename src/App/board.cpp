#include "board.h"
#include "assets.h"

Board::Board(){
    for(int i = 0; i < ROWS; i++)
        board[i] = Line();
    
    cursor = 0;
    unsetHumanActivity();
    unsetMachineActivity();
}

void Board::toggle(int j, int  i){
    board[j].set(i, !board[j].get(i));
    setHumanActivity();
}

void Board::set(int j, int i, bool v){
    if(board[j].get(i) != v){
        board[j].set(i, v);
        
        if(j >= ROWS / 2)
            setHumanActivity();
        else
            setMachineActivity();
    }
}


void Board::setMachineActivity(){
    lastMachineActivity = ofGetElapsedTimef();
}

void Board::unsetMachineActivity(){
    lastMachineActivity = -1;
    
}

void Board::setHumanActivity(){
    lastHumanActivity = ofGetElapsedTimef();
}

void Board::unsetHumanActivity(){
    lastHumanActivity = -1;
}

bool Board::get(int j, int i){
    return board[j].get(i);
}

void Board::click(int x, int y){
    x = (x - anchor.x);
    y = (y - anchor.y);
    
    int i = x / CELL_SIZE;
    int j = y / CELL_SIZE;
    
    if(x < 0 || y < 0 || x > CELL_SIZE * BOARD_SIZE || y > CELL_SIZE * ROWS )
        return;
    
    toggle(j, i);
}

void Board::draw(int x, int y){
    anchor.x = x;
    anchor.y = y;
    
    ofPushMatrix();
    ofTranslate(anchor);
    for(int i = 0; i < ROWS; i++){
        board[i].draw();
        ofDrawBitmapString(ofToString(Assets::getInstance()->getMidiNote(i, false)), 10, 25);
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

string Board::toString(){
    string s = "";
    
    for(int i = ROWS / 2; i < ROWS; i++){
        s += ofToString(Assets::getInstance()->getMidiNote(i, false));
        s += ",";
        s += board[i].toString();
        s += ";";
    }
    return s;
}

bool Board::isClean(){
    bool bClean = true;
    
    for(int i = ROWS / 2; i < ROWS; i++){
        if (!board[i].isClean()) return false;
    }
    
    return bClean;
}

int Board::pitchToRow(int pitch){
    for(int i = 0; i < ROWS; i ++){
        if(Assets::getInstance()->getMidiNote(i, false) == pitch) return i;
    }
    return -1;
}


vector<ofPoint> Board::fromPrediction(string values, bool bAutoUpdate){
    vector<string> rows = ofSplitString(values, ";");
    rows.pop_back();
    
    vector<ofPoint> changes;
    lastNumberOfChanges = 0;
    
    for(auto row: rows){
        vector<string> notes = ofSplitString(row, ",");
        int nRow = pitchToRow(ofToInt(notes[0]));
        for(int i = 0; i < notes[1].size(); i ++){
            bool bChanged = false;
            
            
            if(bAutoUpdate){
                if(notes[1][i] == '1')
                    bChanged = board[nRow].set(i, 1);
                else
                    bChanged = board[nRow].set(i, 0);
            }
            else{
                if(notes[1][i] == '1')
                    bChanged = !board[nRow].get(i);
                else
                    bChanged = board[nRow].get(i);
            }
            
            if(bChanged){
                changes.push_back(ofPoint(nRow, i));
            }
        }
        
    }
    lastNumberOfChanges = changes.size();
    return changes;
}

vector<ofPoint> Board::changesToClean(bool bAutoUpdate){
    
    vector<ofPoint> changes;
    lastNumberOfChanges = 0;
    
     for(int nRow = 0; nRow < ROWS / 2; nRow ++){
         for(int i = 0; i < BOARD_SIZE; i++){
            bool bChanged = false;
             
            if(board[nRow].get(i)){
                bChanged = true;
                if(bAutoUpdate) board[nRow].set(i, 0);
            }
             
            if(bChanged){
                changes.push_back(ofPoint(nRow, i));
            }
         }
        
    }
    lastNumberOfChanges = changes.size();
    return changes;
}
