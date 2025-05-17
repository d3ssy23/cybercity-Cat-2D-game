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
#ifndef CATDEAD_H
#define CATDEAD_H

#define ATLAS_ATLAS_IMAGE_PATH      "atlas.png"
#define DCAT_COUNT    10

// Atlas sprite properties
typedef struct deadCat {
    const char *nameId;
    int originX, originY;
    int positionX, positionY;
    int sourceWidth, sourceHeight;
    int padding;
    bool trimmed;
    int trimRecX, trimRecY, trimRecWidth, trimRecHeight;
} deadCat;

// Atlas sprites array
static deadCat deadCatAtlas[10] = {
    { "Dead (1)", 0, 0, 0, 0, 556, 504, 0, false, 7, 68, 319, 385 },
    { "Dead (2)", 0, 0, 556, 0, 556, 504, 0, false, 62, 17, 336, 437 },
    { "Dead (3)", 0, 0, 1112, 0, 556, 504, 0, false, 89, 25, 380, 433 },
    { "Dead (4)", 0, 0, 0, 504, 556, 504, 0, false, 127, 125, 376, 332 },
    { "Dead (5)", 0, 0, 556, 504, 556, 504, 0, false, 130, 105, 406, 352 },
    { "Dead (6)", 0, 0, 1112, 504, 556, 504, 0, false, 135, 126, 393, 329 },
    { "Dead (7)", 0, 0, 0, 1008, 556, 504, 0, false, 137, 138, 384, 318 },
    { "Dead (8)", 0, 0, 556, 1008, 556, 504, 0, false, 137, 145, 383, 311 },
    { "Dead (9)", 0, 0, 1112, 1008, 556, 504, 0, false, 137, 148, 387, 312 },
    { "Dead (10)", 0, 0, 0, 1512, 556, 504, 0, false, 137, 148, 387, 312 },
};

Rectangle deadCatFrame(int frameIndex){
    if(frameIndex >= 0 && frameIndex < DCAT_COUNT){
        return (Rectangle){
            (float)deadCatAtlas[frameIndex].positionX,
            (float)deadCatAtlas[frameIndex].positionY,
            (float)deadCatAtlas[frameIndex].sourceWidth,
            (float)deadCatAtlas[frameIndex].sourceHeight,
        };
    }
    return (Rectangle){0,0,0,0}; // default
};

#endif