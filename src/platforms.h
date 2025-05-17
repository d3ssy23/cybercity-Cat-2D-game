#ifndef PLATFORMS_H
#define PLATFORMS_H
#include "raylib.h"
#include "lib.h"

#define MAX_PLATFORMS 2

extern Texture2D tileL;
extern Texture2D tileR;
extern Texture2D tileM;
extern Vector2 catPosition;



typedef struct {

    double positionX;
    double positionY;
    double Twidth;
    double Theight;
    int midCount;
    bool offscreen;



} Platform;

float tileScale = 0.2f;

Platform platforms[MAX_PLATFORMS];

void set_positions(Platform *platform){
    platform->positionX = screenWidth;
    platform->positionY = 360.0f;

}


void get_width_height(Platform *platform){
    platform->Twidth = tileL.width + tileM.width * platform->midCount + tileR.width;
    platform->Theight = tileL.height;
}

void scale_tile(Platform *platform){
    platforms->Twidth *= tileScale;
    platforms->Theight *= tileScale;
}


void SpawnPlatform(int i, float x, float y) {
   // for(int j=0; j<i;j++){
    platforms[i] = (Platform){
        .positionX = x ,
        .positionY = y,
        .midCount = GetRandomValue(1, 2),
        .offscreen = false
    };
   // set_positions(&platforms[i]);
   get_width_height(&platforms[i]); 
   scale_tile(&platforms[i]);  
//}
}

void DrawPlatform(Platform* platform){

  //  platforms->midCount = GetRandomValue(0,4);


    float x = platform->positionX;
    float y = platform->positionY;

    DrawTextureEx(tileL,(Vector2){x,y},0.0f, tileScale, WHITE);
    x += tileL.width * tileScale;

    for(int i=0; i<platforms->midCount; i++){
        DrawTextureEx(tileM,(Vector2){x,y},0.0f,tileScale, WHITE);
        x += tileM.width * tileScale; 
      
    }
    DrawTextureEx(tileR,(Vector2){x,y},0.0f,tileScale, WHITE);

 
}


void platformCycle(){

    // scroll and delete
    for(int i =0; i< MAX_PLATFORMS;i++){
        set_positions(&platforms[i]);
    platforms[i].positionX +=  2.0f;
    if(platforms[i].positionX >= screenWidth-50.0f){
        platforms[i].offscreen = true;
    }
    if (platforms[i].offscreen) {
        SpawnPlatform(i, GetScreenWidth() + 40.0f, GetRandomValue(200, 300));
    }
    }
}



#endif