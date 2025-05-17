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
#ifndef CATJUMP_H
#define CATJUMP_H

#define JUMP_ATLAS_IMAGE_PATH      "catJump.png"
#define JUMP_ATLAS_SPRITE_COUNT    8

#include "raylib.h"

// Atlas sprite properties
typedef struct catJump {
    const char *nameId;
    int originX, originY;
    int positionX, positionY;
    int sourceWidth, sourceHeight;
    int padding;
    bool trimmed;
    int trimRecX, trimRecY, trimRecWidth, trimRecHeight;
} catJump;

// Atlas sprites array
static catJump catAtla[8] = {
    { "Jump (1)", 0, 0, 0, 0, 542, 474, 0, false, 134, 26, 291, 436 },
    { "Jump (2)", 0, 0, 542, 0, 542, 474, 0, false, 103, 21, 286, 430 },
    { "Jump (3)", 0, 0, 1084, 0, 542, 474, 0, false, 67, 25, 284, 396 },
    { "Jump (4)", 0, 0, 0, 474, 542, 474, 0, false, 68, 26, 284, 402 },
    { "Jump (5)", 0, 0, 542, 474, 542, 474, 0, false, 70, 28, 283, 407 },
    { "Jump (6)", 0, 0, 1084, 474, 542, 474, 0, false, 68, 26, 284, 402 },
    { "Jump (7)", 0, 0, 0, 948, 542, 474, 0, false, 67, 25, 284, 396 },
    { "Jump (8)", 0, 0, 542, 948, 542, 474, 0, false, 68, 26, 284, 402 },
};

Rectangle CatJumpFrame(int frameIndex){
    if(frameIndex>=0 && frameIndex < JUMP_ATLAS_SPRITE_COUNT){
        return (Rectangle){
        (float)catAtla[frameIndex].positionX,
        (float)catAtla[frameIndex].positionY,
        (float)catAtla[frameIndex].sourceWidth,
        (float)catAtla[frameIndex].sourceHeight,
    };
}
return (Rectangle){0,0,0,0}; 
}

#endif