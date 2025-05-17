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
#ifndef CATRUN_H
#define CATRUN_H

#define JUMP_ATLAS_IMAGE_PATH      "catJump.png"
#define JUMP_ATLAS_SPRITE_COUNT    8
#include "raylib.h"


#define CATRUN_PATH      "atlas.png"
#define ATLAS_ATLAS_SPRITE_COUNT    10

// Atlas sprite properties
typedef struct catSprite {
    const char *nameId;
    int originX, originY;
    int positionX, positionY;
    int sourceWidth, sourceHeight;
    int padding;
    bool trimmed;
    int trimRecX, trimRecY, trimRecWidth, trimRecHeight;
} catSprite;

// Atlas sprites array
static catSprite catAtlas[10] = {
    { "Walk (1)", 0, 0, 0, 0, 542, 474, 0, false, 105, 27, 287, 435 },
    { "Walk (2)", 0, 0, 542, 0, 542, 474, 0, false, 102, 25, 287, 433 },
    { "Walk (3)", 0, 0, 1084, 0, 542, 474, 0, false, 100, 23, 287, 428 },
    { "Walk (4)", 0, 0, 0, 474, 542, 474, 0, false, 100, 23, 287, 427 },
    { "Walk (5)", 0, 0, 542, 474, 542, 474, 0, false, 102, 25, 287, 432 },
    { "Walk (6)", 0, 0, 1084, 474, 542, 474, 0, false, 105, 27, 287, 435 },
    { "Walk (7)", 0, 0, 0, 948, 542, 474, 0, false, 102, 26, 287, 434 },
    { "Walk (8)", 0, 0, 542, 948, 542, 474, 0, false, 100, 24, 287, 430 },
    { "Walk (9)", 0, 0, 1084, 948, 542, 474, 0, false, 100, 24, 287, 430 },
    { "Walk (10)", 0, 0, 0, 1422, 542, 474, 0, false, 102, 26, 287, 434 },
};

Rectangle CatFrame(int frameIndex){
    if(frameIndex>=0 && frameIndex < ATLAS_ATLAS_SPRITE_COUNT){
        return (Rectangle){
        (float)catAtlas[frameIndex].positionX,
        (float)catAtlas[frameIndex].positionY,
        (float)catAtlas[frameIndex].sourceWidth,
        (float)catAtlas[frameIndex].sourceHeight,
    };
}
return (Rectangle){0,0,0,0}; 
}


#endif