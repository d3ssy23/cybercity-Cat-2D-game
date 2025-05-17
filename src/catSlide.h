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
#ifndef CATSLIDE_H
#define CATSLIDE_H

#define JUMP_ATLAS_IMAGE_PATH      "catJump.png"
#define JUMP_ATLAS_SPRITE_COUNT    8
#define CATSLIDE_PATH      "atlas.png"
#define CATSLIDE_COUNT    10
#include "raylib.h"

// Atlas sprite properties
typedef struct  {
    const char *nameId;
    int originX, originY;
    int positionX, positionY;
    int sourceWidth, sourceHeight;
    int padding;
    bool trimmed;
    int trimRecX, trimRecY, trimRecWidth, trimRecHeight;
} catSlide;

// Atlas sprites array
static catSlide catSlideAtlas[10] = {
    { "Slide (1)", 0, 0, 0, 0, 542, 474, 0, false, 26, 118, 317, 344 },
    { "Slide (2)", 0, 0, 542, 0, 542, 474, 0, false, 24, 118, 319, 343 },
    { "Slide (3)", 0, 0, 1084, 0, 542, 474, 0, false, 17, 118, 326, 343 },
    { "Slide (4)", 0, 0, 0, 474, 542, 474, 0, false, 17, 118, 326, 343 },
    { "Slide (5)", 0, 0, 542, 474, 542, 474, 0, false, 24, 118, 319, 343 },
    { "Slide (6)", 0, 0, 1084, 474, 542, 474, 0, false, 26, 118, 317, 344 },
    { "Slide (7)", 0, 0, 0, 948, 542, 474, 0, false, 24, 118, 319, 343 },
    { "Slide (8)", 0, 0, 542, 948, 542, 474, 0, false, 17, 118, 326, 343 },
    { "Slide (9)", 0, 0, 1084, 948, 542, 474, 0, false, 18, 118, 325, 343 },
    { "Slide (10)", 0, 0, 0, 1422, 542, 474, 0, false, 24, 118, 319, 343 },
};
Rectangle CatSlideFrame(int frameIndex){
    if(frameIndex>=0 && frameIndex < CATSLIDE_COUNT){
        return (Rectangle){
        (float)catSlideAtlas[frameIndex].positionX,
        (float)catSlideAtlas[frameIndex].positionY,
        (float)catSlideAtlas[frameIndex].sourceWidth,
        (float)catSlideAtlas[frameIndex].sourceHeight,
    };
}
return (Rectangle){0,0,0,0}; 
}

int currentSlideFrame = 0;
int slideFrameCounter = 0;
const int slideFrameSpeed = 10;

#endif