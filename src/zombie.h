//////////////////////////////////////////////////////////////////////////////////
//                                                                              //
// rTexpacker v4.0 Atlas Descriptor Code exporter v2.0                          //
//                                                                              //
// more info and bugs-report:  github.com/raylibtech/rtools                     //
// feedback and support:       ray[at]raylibtech.com                            //
//                                                                              //
// Copyright (c) 2020-2024 raylib technologies (@raylibtech)                    //
//                                                                              //
//////////////////////////////////////////////////////////////////////////////////
#include "raylib.h"

#define ZOMBIE_PATH      "../resources/zombie.png"
#define ZOMBIE_COUNT    10

#pragma once
// Atlas sprite properties
typedef struct Zombie {
    const char *nameId;
    int originX, originY;
    int positionX, positionY;
    int sourceWidth, sourceHeight;
    int padding;
    bool trimmed;
    int trimRecX, trimRecY, trimRecWidth, trimRecHeight;
    
} Zombie;

typedef struct zombieSpawner{

    Vector2 positions;
    bool active;
} zombieSpawner;

// Atlas sprites array
static Zombie zombieArr[10] = {
    { "Walk (1)", 0, 0, 0, 0, 430, 519, 0, false, 73, 49, 282, 458 },
    { "Walk (2)", 0, 0, 430, 0, 430, 519, 0, false, 40, 45, 313, 474 },
    { "Walk (3)", 0, 0, 860, 0, 430, 519, 0, false, 17, 42, 334, 473 },
    { "Walk (4)", 0, 0, 1290, 0, 430, 519, 0, false, 18, 42, 333, 467 },
    { "Walk (5)", 0, 0, 0, 519, 430, 519, 0, false, 33, 45, 320, 465 },
    { "Walk (6)", 0, 0, 430, 519, 430, 519, 0, false, 46, 49, 309, 458 },
    { "Walk (7)", 0, 0, 860, 519, 430, 519, 0, false, 80, 44, 271, 475 },
    { "Walk (8)", 0, 0, 1290, 519, 430, 519, 0, false, 70, 40, 277, 477 },
    { "Walk (9)", 0, 0, 0, 1038, 430, 519, 0, false, 61, 40, 286, 471 },
    { "Walk (10)", 0, 0, 430, 1038, 430, 519, 0, false, 70, 44, 281, 467 },
};

Rectangle zombieFrame(int frameIndex){
    if(frameIndex >= 0 && frameIndex < ZOMBIE_COUNT){
        return (Rectangle){
            (float)zombieArr[frameIndex].positionX,
            (float)zombieArr[frameIndex].positionY,
            (float)zombieArr[frameIndex].sourceWidth,
            (float)zombieArr[frameIndex].sourceHeight,
        };
    }
    return (Rectangle){0,0,0,0}; // default
};

void trimWidth(Zombie *zombie,int trimW, int trimX){
    zombie->trimRecWidth = trimW;
    zombie->trimRecX = trimX;

    
}

Rectangle zombieFrameFlipped(int frameIndex){
    
    trimWidth(&zombieArr[frameIndex],300,0);
    
    if(frameIndex >= 0 && frameIndex < ATLAS_ATLAS_SPRITE_COUNT){
        return (Rectangle){
            (float)zombieArr[frameIndex].positionX + zombieArr[frameIndex].trimRecWidth,
            (float)zombieArr[frameIndex].positionY,
            (float)zombieArr[frameIndex].sourceWidth -zombieArr[frameIndex].trimRecX,
            (float)zombieArr[frameIndex].sourceHeight,
           // (float)zombieArr[frameIndex].trimRecWidth,
            //(float)zombieArr[frameIndex].trimRecX,


        };
    }
    return (Rectangle){0,0,0,0}; // default
};

