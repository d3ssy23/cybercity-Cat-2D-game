#ifndef LIB_H
#define LIB_H

#include "raylib.h"

enum CatState {
    RUNNING,
    JUMPING,
    SLIDING,
    DEAD
};

enum CatState currentState = RUNNING;

 // background move speed
 float scrollingBack = 0.0f;
 float scrollingMid = 0.0f;
 float scrollingFore = 0.0f;

void scrollings(){
    scrollingBack -= 0.7f;
    scrollingMid -= 1.0f;
    scrollingFore -= 1.7f; 

}
void scrollingsFore(){
    scrollingBack += 0.5f;
    scrollingMid += 0.9f;
    scrollingFore += 1.5f; 

}


// platform collision





#endif