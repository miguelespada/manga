#ifndef __<%= name %>__state__
#define __<%= name %>__state__

#include "baseState.h"
#include "app.h"


class <%= name %>State: public BaseState
{
    
public:
    <%= name %>State(App *a);
    <%= name %>State();
    std::string toString() { return "<%= name %>"; }
    void update();
    void draw();
    void next();
    void reset();
    void keyPressed(int key){};
};

#endif
