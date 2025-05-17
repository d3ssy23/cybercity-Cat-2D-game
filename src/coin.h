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

#ifndef COIN_H
#define COIN_H
#define COIN_IMAGE_PATH      "../resources/coin.png"
#define ATLAS_ATLAS_SPRITE_COUNT    10

// Atlas sprite properties
typedef struct coinSprite {
    const char *nameId;
    int originX, originY;
    int positionX, positionY;
    int sourceWidth, sourceHeight;
    int padding;
    bool trimmed;
    int trimRecX, trimRecY, trimRecWidth, trimRecHeight;
} coinSprite;

// Atlas sprites array
static coinSprite coinAtlas[10] = {
    { "Gold_21", 0, 0, 1360, 0, 563, 564, 0, false, 0, 0, 563, 564 },
    { "Gold_22", 0, 0, 632, 565, 559, 564, 0, false, 0, 0, 559, 564 },
    { "Gold_23", 0, 0, 856, 0, 504, 564, 0, false, 0, 0, 504, 564 },
    { "Gold_24", 0, 0, 0, 0, 428, 565, 0, false, 0, 0, 428, 565 },
    { "Gold_25", 0, 0, 0, 565, 262, 564, 0, false, 0, 0, 262, 564 },
    { "Gold_26", 0, 0, 262, 565, 108, 564, 0, false, 0, 0, 108, 564 },
    { "Gold_27", 0, 0, 370, 565, 262, 564, 0, false, 0, 0, 262, 564 },
    { "Gold_28", 0, 0, 428, 0, 428, 565, 0, false, 0, 0, 428, 565 },
    { "Gold_29", 0, 0, 1191, 565, 503, 564, 0, false, 0, 0, 503, 564 },
    { "Gold_30", 0, 0, 0, 1129, 559, 564, 0, false, 0, 0, 559, 564 },
};


Rectangle CoinFrame(int frameIndex){
    if(frameIndex >= 0 && frameIndex < ATLAS_ATLAS_SPRITE_COUNT){
        return (Rectangle){
            (float)coinAtlas[frameIndex].positionX,
            (float)coinAtlas[frameIndex].positionY,
            (float)coinAtlas[frameIndex].sourceWidth,
            (float)coinAtlas[frameIndex].sourceHeight,
        };
    }
    return (Rectangle){0,0,0,0}; // default
};
#endif