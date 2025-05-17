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
#ifndef HEARTATLAS_H
#define HEARTATLAS_H


#define HEART_IMAGE      "../resources/heart.png"
#define HEART_COUNT    5
#pragma once
#include "raylib.h"

// Atlas sprite properties
typedef struct heart {
    const char *nameId;
    int originX, originY;
    int positionX, positionY;
    int sourceWidth, sourceHeight;
    int padding;
    bool trimmed;
    int trimRecX, trimRecY, trimRecWidth, trimRecHeight;
} heart;

// Atlas sprites array
static heart heartAtlas[5] = {
    { "heart copy 2", 0, 0, 0, 0, 512, 512, 0, false, 3, 7, 506, 497 },
    { "heart copy 3", 0, 0, 512, 0, 512, 512, 0, false, 3, 7, 506, 497 },
    { "heart copy 4", 0, 0, 1024, 0, 512, 512, 0, false, 3, 7, 506, 497 },
    { "heart copy 5", 0, 0, 1536, 0, 512, 512, 0, false, 3, 7, 506, 497 },
    { "heart copy", 0, 0, 0, 512, 512, 512, 0, false, 3, 7, 506, 497 },
};

Rectangle HeartFrame(int frameIndex){
    if(frameIndex >= 0 && frameIndex < HEART_COUNT){
        return (Rectangle){
            (float)heartAtlas[frameIndex].positionX,
            (float)heartAtlas[frameIndex].positionY,
            (float)heartAtlas[frameIndex].sourceWidth,
            (float)heartAtlas[frameIndex].sourceHeight,
        };
    }
    return (Rectangle){0,0,0,0}; // default
};

#endif