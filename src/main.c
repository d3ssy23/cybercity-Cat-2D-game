
#include "raylib.h"
#include "catRun.h"
#include "constants.h"
#include "coin.h"
#include "catJump.h"
#include "zombie.h"
#include "heartAtlas.h"
#include "catDead.h"
#include "catSlide.h"
#include "platforms.h"

#include "math.h"
#include "lib.h"

#define COIN_COUNT 8
#define MAX_ZOMBIE 3
#define MAX_LIVES 5

Texture2D tileL;
 Texture2D tileR;
Texture2D tileM;
Vector2 catPosition;


int main(void)
{


// ----------------------Pre game processing-------------------

    InitWindow(screenWidth, screenHeight, "Follow the path");
    InitAudioDevice();
    SetMasterVolume(1.0f);


     // Character frame Variables
     int currentFrame = 0;
     int framesCounter = 0;
     int framesSpeed = 6;
     int randValuePlatformsY = 30;
     int randValuePlatformsY2 = 40;
     int midPlatformCount = GetRandomValue(1,4);
     int heartDecreaseCooldown = 0.0f;


     Image zombieImage = LoadImage("../resources/zombie.png");
     ImageFlipHorizontal(&zombieImage);
 

 // Character Textures
    Texture2D catRun = LoadTexture("../resources/catRun.png");
    Texture2D catJump = LoadTexture("../resources/catJump.png");
    Texture2D catDead = LoadTexture("../resources/deadcat.png");
    Texture2D catSlide = LoadTexture("../resources/catSlide.png");
    Texture2D coinT = LoadTexture(COIN_IMAGE_PATH);
    Texture2D zombie = LoadTexture(ZOMBIE_PATH);
    Texture2D zombieFlipped = LoadTextureFromImage(zombieImage);
    Texture2D heart = LoadTexture(HEART_IMAGE);

// Platforms 
Platform pl1[MAX_PLATFORMS];
Platform pl2[MAX_PLATFORMS];
double pl1_posX = pl1->positionX;
double pl2_posX = pl2->positionX;
// pl1->positionY = 500;
// pl2->positionY = 800;
get_width_height(pl1); 
scale_tile(pl1);
get_width_height(pl2); 
scale_tile(pl2);
bool catPlatformCollision = false;

// Hearts
Vector2 heartPositions[MAX_LIVES];
 // health bar hearts

    


// Tile textures

tileL = LoadTexture("../resources/platform1.png");
tileR = LoadTexture("../resources/platform1.3.png");
tileM = LoadTexture("../resources/platform1.2.png");

// Sounds
    Sound damage = LoadSound("../resources/punch.mp3");
    Sound footsteps = LoadSound("../resources/footsteps/step_cloth1.ogg");
    Sound coinSound = LoadSound("../resources/coin.mp3");
    Sound slide = LoadSound("../resources/slide.mp3");
    Sound jump = LoadSound("../resources/jump.mp3");
    SetSoundVolume(coinSound, 0.1f);
    SetSoundVolume(footsteps, 1.5f);
   
    
    // Positions
   catPosition = (Vector2){0.0f,0.0f}; 
    Vector2 heartPosition =  {740.0f,20.0f};
    Vector2 zombiePosition = {screenWidth - 130, screenHeight - 130};

     //Scaling
    Vector2 coinScale = {0.05f,0.05f};
    Vector2 catScale = {0.2f,0.2f};
    Vector2 zombieScale = {0.2f,0.2f};
    Vector2 heartScale = {0.05f,0.05f};

    

// Coins
    int score = 0;
    float coinSpeed = 3.0f;
    int coinFrame = 0;
    int coinFrameCounter = 0;
    int coinFrameSpeed = 8;

    int currentFrameZ = 0;
    int currentFrameZFlipped = 0;
    int framesCounterZombie = 0;
    int framesCounterZombieFlipped = 0;

    float totalDistanceMoved = 0.0f;
    const float respawnDistance = 100.0f;

 // Vars
 
    int heart_count = MAX_LIVES;
    int is_dead = false;
    static int bufferSizeGap = 0;
    float zombieSpeed = 1.5f;

 // Frames 
    Rectangle frameCatRec = CatFrame(4+currentFrame);
    Rectangle frameCatJumpRec = CatJumpFrame(4+currentFrame);
    Rectangle frameCatDead = deadCatFrame(4+currentFrame);
    Rectangle frameCatSlide =CatSlideFrame(4+currentFrame);
    Rectangle frameRecCoin = CoinFrame(4+coinFrame);
    Rectangle frameZombie = zombieFrame(4+currentFrame);
    Rectangle frameZombieFlipped = zombieFrameFlipped(4+currentFrameZFlipped);
    Rectangle frameRecHeart = HeartFrame(currentFrame);
    Rectangle zombieRect = { zombiePosition.x, zombiePosition.y,frameZombie.width * zombieScale.x,frameZombie.height * zombieScale.y};
    

   

// Dynamic SPAWNERS

float spawnTime =0;
float spawnDistance = 2.0f;

 //coins
    Vector2 coinPositions[COIN_COUNT];


    for(int i =0; i<COIN_COUNT;i++){
        
        coinPositions[i].x = GetRandomValue(150,800);
        coinPositions[i].y = GetRandomValue(300,400);
    }

//zombies
    //  Vector2 zombiePositions[MAX_ZOMBIE];

    // for(int i =0; i<MAX_ZOMBIE;i++){
        
    //     zombiePositions[i].x = GetRandomValue(screenWidth,1800);
    //    // zombiePositions[i].y = GetRandomValue(300,330);
    // }

 

    // Background textures 
    Texture2D background = LoadTexture("../resources/far-buildings.png");
    Texture2D midground = LoadTexture("../resources/back-buildings.png");
    Texture2D foreground = LoadTexture("../resources/foreground.png");
    Texture2D foreground2 = LoadTexture("../resources/green/foreground.png");


   

    // Has the game begun?
    bool is_started = false;
    bool is_moving = true;
    bool is_going_right = true;


    SetTargetFPS(60);               

     // Cat jump logic variables
     float yPos = catPosition.y;
     float yNew = catPosition.y + 3.0f;
     float ySpeed = 5.0f;


    // Camera2D following
    Camera2D camera = { 0 };
    camera.target = (Vector2){pl1->positionX,pl1->positionY};
    camera.offset = (Vector2){ 0, 0 };
    camera.zoom = 1.0f;

    //Platforms
    for(int i = 0; i < MAX_PLATFORMS;i++){
       // platformCycle();

        SpawnPlatform(i, screenWidth + i * 200.0f, GetRandomValue(300, 400));
       

    }
  

// ----------------------Game loop-------------------------------

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

  
        bool movingUp = true;
        currentState = RUNNING;



// ************ Zombie logic **************

    Vector2 zombiePositions[MAX_ZOMBIE];
    zombieSpawner zombies[MAX_ZOMBIE];

    spawnTime += GetFrameTime();
    if(spawnTime >= spawnDistance){
        spawnTime = 0.0;
    }

    
    Rectangle catRect = { catPosition.x, catPosition.y, frameCatRec.width * catScale.x, frameCatRec.height * catScale.y };
    for(int i =0; i<MAX_ZOMBIE;i++)
{
    if(!zombies[i].active){
    zombies[i].active = true;
    zombies[i].positions.x = screenWidth + GetRandomValue(50,150);
    zombies[i].positions.y = GetRandomValue(280,360);
    zombiePositions[i].x = screenWidth - GetRandomValue(50,150);
    zombiePositions[i].y = GetRandomValue(280,360);
    }
 //  Zombie + cat collision - health decrament
    Rectangle zombieRect = {zombiePosition.x,zombiePosition.y,frameZombie.width * zombieScale.x,frameZombie.height * zombieScale.y};

    for (int i = 0; i < ZOMBIE_COUNT; i++) {
           

        if(heartDecreaseCooldown <= 0.0f && CheckCollisionRecs(catRect,zombieRect)){
            catPosition.y =  catPosition.y - 9.0f;
            
            heart_count = heart_count - 1;
            heartDecreaseCooldown = 100.0f;
            PlaySound(damage);

            if(heart_count == 0){
                is_dead = true;
                currentState = DEAD;
                break;
            }

        }
    }
    for(int i=0;i<heart_count;i++)
    {
        heartPositions[i].x = heartPosition.x + ((i*(heart.width*heartScale.x -130) ));
        heartPositions[i].y = heartPosition.y;
    }
    if (heartDecreaseCooldown > 0.0f) {
        heartDecreaseCooldown -= GetFrameTime();
    }

    
    if(zombies[i].active){
        zombiePositions[i].x -= zombieSpeed;
    }
    if(zombies[i].positions.x < -50){
    zombies[i].active = false;
    }
}

 // Collecting coins
        for(int i = 0; i<COIN_COUNT;i++){
            Rectangle coinRect = { coinPositions[i].x, coinPositions[i].y, frameRecCoin.width * coinScale.x, frameRecCoin.height * coinScale.y };
            
        if(CheckCollisionRecs(coinRect,catRect)){
            PlaySound(coinSound);
             score++; 
             coinPositions[i].x = coinSpeed + GetRandomValue(300, 900); 
             coinPositions[i].y = 320.0f;
           
        } 
        if(coinPositions[i].x <= - 550.0f){
        coinPositions[i].x = coinSpeed * 10; 
        coinPositions[i].y = coinSpeed * 100;
        }
              
        }
 //GAME start menu

 // *********** Character frame logic ************
        framesCounter++;
        if(framesCounter >= (60/framesSpeed)){
            framesCounter = 0;
            currentFrame = (currentFrame +1) % 4;

        }

        // Zombie frame
        framesCounterZombie++;
        if(framesCounterZombie >= (60/framesSpeed)){
            framesCounterZombie = 0;
            currentFrameZ = (currentFrameZ +1) % 4;

        }
        framesCounterZombieFlipped++;
        if(framesCounterZombieFlipped >= (60/framesSpeed)){
            framesCounterZombieFlipped = 0;
            currentFrameZFlipped = (currentFrameZFlipped + 1) % 4;

        }
        frameZombieFlipped = zombieFrameFlipped(4+currentFrameZFlipped);
        frameZombie = zombieFrame(4+currentFrameZ);


        // Coin frame logic
        coinFrameCounter++;
        if(coinFrameCounter >= (60/coinFrameSpeed)){
            coinFrameCounter =0 ;
            coinFrame = (coinFrame +1) % 4;

        }

         frameRecCoin = CoinFrame(4+coinFrame);


// ********** Zombie Logic **********

// Zombie reverse character and trajectory
    float zombieSpeed = 2.0f;

    if(is_going_right){
            zombiePosition.x += zombieSpeed;
        if(zombiePosition.x >= 700) {
            is_going_right = false;
           
        }
     }
    else{
            zombiePosition.x -= zombieSpeed;
            if(zombiePosition.x <= screenWidth- 500.0f)
             is_going_right = true;
        }
// Zombie pattern        
    for(int i =0; i< ZOMBIE_COUNT;i++){
        //zombiePosition.y = 330.0f;
        if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_DOWN)){

            zombiePosition.x -= 0.5f;
            
           }
            
            if (zombiePosition.x < -150.0f) {
           
                zombiePosition.x = screenWidth + 150.0f ;
                //randValuePlatforms = GetRandomValue(200,300);
                
    
            }
    }

        

 // ************ Buttons setting Cat character ******************
                  
 //  if(IsKeyDown(KEY_LEFT)){
                    //     //catPosition.x -= 2.0f;
                    //     scrollingsFore();
                    //  }

        if(IsKeyDown(KEY_RIGHT)){
           
            currentState = RUNNING;
            
            frameCatRec = CatFrame(4+currentFrame);
            if(bufferSizeGap == 0){
            PlaySound(footsteps);
            bufferSizeGap = 15;
            }
        
            for(int i =0; i<COIN_COUNT;i++){  // get the coins closer to the cat
            coinPositions[i].x -= coinSpeed;
            }
          
         

            
            scrollings();

            }
            if(bufferSizeGap > 0) bufferSizeGap--;

        if(IsKeyDown(KEY_SPACE) && movingUp){
            
                currentState = JUMPING;
                catPosition.y -= ySpeed;
                frameCatJumpRec = CatJumpFrame(4+currentFrame);
                
                currentFrame = (currentFrame + 1) % 4;
                if(bufferSizeGap == 0){
                    PlaySound(jump);
                }
                                
                 
            if(catPosition.y <= 20.0f){
               catPosition.y += ySpeed;
            }
            for(int i =0; i<COIN_COUNT;i++){
                coinPositions[i].x -= coinSpeed;
                }
                
               scrollings();

            
        }
        else{
               movingUp = false;
               is_moving = false;
            if(catPosition.y <= 330.0f)
                catPosition.y += ySpeed;
            }

        if(IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_SPACE)){

            currentState = SLIDING;
  
            frameCatSlide = CatSlideFrame(4+currentFrame);
            currentFrame = (currentFrame + 1) % 4;
            if(bufferSizeGap == 0){
                PlaySound(slide);
                bufferSizeGap = 100;
                }


            for(int i =0; i<COIN_COUNT;i++){
                coinPositions[i].x -= coinSpeed;
                }

            scrollings();
  
        }
        if(bufferSizeGap > 0) bufferSizeGap--;

        
//   @@@@@@@@ Platform @@@@@@@

       for (int i = 0; i < MAX_PLATFORMS; i++) {
        

        pl1[i].positionY = randValuePlatformsY;
        pl2[i].positionY = randValuePlatformsY2;

        if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_DOWN)){

        pl1[i].positionX -= 2.0f; 
        pl2[i].positionX -= 2.0f; 

        }
        if(IsKeyDown(KEY_SPACE) && IsKeyDown(KEY_RIGHT)){
            pl1[i].positionX -= 3.0f; 
           pl2[i].positionX -= 3.0f; 

        }
        if (pl1[i].positionX < -150.0f) {
           
            pl1[i].positionX = screenWidth + pl1->Twidth + 150.0f ;

            randValuePlatformsY = GetRandomValue(200,250);

            pl1[i].midCount = GetRandomValue(10,90);


        }
        if( pl2[i].positionX < -400.0f){
            pl2[i].positionX = screenWidth + pl2->Twidth + 150.0f ;
            randValuePlatformsY2 = GetRandomValue(250,300);
            pl2[i].midCount = 6;

        }
      

    }
        // Collision platform + cat
        for (int i = 0; i < MAX_PLATFORMS; i++) {
           
            Rectangle platformRect = {pl1[i].positionX,pl1[i].positionY,pl1[i].Twidth +120.0f,pl1[i].Theight + 120.0f};
            Rectangle platformRect2 = {pl2[i].positionX,pl2[i].positionY,pl2[i].Twidth +120.0f,pl2[i].Theight + 120.0f};

                if(CheckCollisionRecs(catRect,platformRect)){
                    catPlatformCollision = true; 
                   
                    if(catPosition.y + catRect.height<= pl1[i].positionY +pl1[i].Theight +10.0f){
                    catPosition.y = pl1[i].positionY - catRect.height + 1.0f;

                    if(currentState == JUMPING){
                        //pl1[i].positionY += 0.4;
                        catPosition.y = pl1[i].positionY  - catRect.height - 1.0f;
                       // catPosition.y -= 10.0f;
                    }
                }
            }
                if(CheckCollisionRecs(catRect,platformRect2)){
                    catPlatformCollision = true; 
                   
                    if(catPosition.y + catRect.height<= pl2[i].positionY +pl2[i].Theight +10.0f){
                    catPosition.y = pl2[i].positionY - catRect.height + 1.0f;

                    if(currentState == JUMPING){
                        //pl1[i].positionY += 0.4;
                        catPosition.y = pl2[i].positionY  - catRect.height - 1.0f;
                       // catPosition.y -= 10.0f;
                    }
                }
   
            }
                
            }



        // NOTE: Texture is scaled twice its size, so it sould be considered on scrolling
        if (scrollingBack <= -background.width*2) scrollingBack = 0;
        if (scrollingMid <= -midground.width*2) scrollingMid = 0;
        if (scrollingFore <= -foreground.width*2) scrollingFore = 0;
       

// ------------------------DRAW---------------------
        BeginDrawing();

            ClearBackground(GetColor(0x052c46ff));

           
// Draw background image
           
            DrawTextureEx(background, (Vector2){ scrollingBack, 20 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(background, (Vector2){ background.width*2 + scrollingBack, 20 }, 0.0f, 2.0f, WHITE);

            // Draw midground image twice
            DrawTextureEx(midground, (Vector2){ scrollingMid, 20 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(midground, (Vector2){ midground.width*2 + scrollingMid, 20 }, 0.0f, 2.0f, WHITE);

            // Draw foreground image twice
            DrawTextureEx(foreground, (Vector2){ scrollingFore, 70 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(foreground, (Vector2){ foreground.width*2 + scrollingFore, 70 }, 0.0f, 2.0f, WHITE);

            DrawText(TextFormat("Score: %d",score),30,30,30,GOLD);

// Draw coins
        // Loop to draw multiple coins        
        for(int i =0; i<COIN_COUNT;i++){
            DrawTexturePro(
                coinT,
                frameRecCoin,
                (Rectangle){ coinPositions[i].x, coinPositions[i].y, frameRecCoin.width * coinScale.x, frameRecCoin.height * coinScale.y },
                (Vector2){0.0f, 0.0f},
                0.0f,
                WHITE
            );
        }

// Draw cat frames
           // game ongoing
            if(currentState == RUNNING){
                DrawTexturePro(
                           catRun,
                           frameCatRec,
                           (Rectangle){ catPosition.x , catPosition.y, frameCatRec.width * catScale.x, frameCatRec.height  *catScale.y},
                           (Vector2){0.0f, 0.0f},
                           0.0f,
                           WHITE
                       );
                    }
            else if(currentState == JUMPING){
            DrawTexturePro(
                catJump,
                frameCatJumpRec,
                (Rectangle){ catPosition.x , catPosition.y, frameCatJumpRec.width * catScale.x, frameCatJumpRec.height  *catScale.y},
                (Vector2){0.0f, 0.0f},
                0.0f,
                WHITE
            );}
            else if(currentState == SLIDING){
                DrawTexturePro(
                    catSlide,
                    frameCatSlide,
                    (Rectangle){ catPosition.x , catPosition.y, frameCatSlide.width * catScale.x, frameCatSlide.height  *catScale.y},
                    (Vector2){0.0f, 0.0f},
                    0.0f,
                    WHITE
                );
                 }
        
    else if(currentState == DEAD){ //game over
        DrawTexturePro(
            catDead,
            frameCatDead,
            (Rectangle){ catPosition.x , catPosition.y, frameCatDead.width * catScale.x, frameCatDead.height  *catScale.y},
            (Vector2){0.0f, 0.0f},
            0.0f,
            WHITE
        );
        return 0;
    }
    

        BeginMode2D(camera);
// Draw Platforms

        for (int i = 0; i < MAX_PLATFORMS; i++) {
            DrawPlatform(&pl1[i]);
            DrawPlatform(&pl2[i]);

           }

            EndMode2D();
 // Zombie flip 
        
        if(is_going_right){
        DrawTexturePro(
            zombie,
            frameZombie,
            (Rectangle){ zombiePosition.x , zombiePosition.y, -frameZombie.width * zombieScale.x, -frameZombie.height * zombieScale.y},
            (Vector2){0.0f, 0.0f},
            0.0f,
            WHITE
        );
    }else{
        DrawTexturePro(
            zombieFlipped,
            frameZombieFlipped,
            (Rectangle){ zombiePosition.x, zombiePosition.y, -(frameZombie.width) * zombieScale.x , frameZombie.height * zombieScale.y},
            (Vector2){0.0f, 0.0f},
            0.0f,
            WHITE
        );
    }
    

// Hearts
    for(int i =0;i<heart_count;i++){
    DrawTexturePro(
                heart,
                frameRecHeart,
                (Rectangle){ heartPositions[i].x, heartPositions[i].y, frameRecHeart.width * heartScale.x, frameRecHeart.height * heartScale.y},
                (Vector2){0.0f, 0.0f},
                0.0f,
                WHITE
            );
        }
           // DrawTextureRec(heart,frameRecHeart,heartPosition,WHITE);

            DrawText(TextFormat("X: %.2f", zombiePosition.x), 20, 100, 20, GREEN);
            for(int i =0;i<MAX_PLATFORMS;i++){
            DrawText(TextFormat("X platform: %.2f", pl1[i].positionX), 30, 130, 30, GREEN);
            }
// Colliosion lines: 

    DrawRectangleLines(catRect.x, catRect.y, catRect.width, catRect.height, RED);
        // get_width_height(&pl1[MAX_PLATFORMS]); 

    for (int i = 0; i < ZOMBIE_COUNT; i++) {

        DrawRectangleLines(zombiePosition.x, zombiePosition.y, frameZombie.width * zombieScale.x,frameZombie.height * zombieScale.y,  GREEN);
    }
    for (int i = 0;i<heart_count;i++){
        DrawRectangleLines( heartPositions[i].x, heartPositions[i].y, frameRecHeart.width * heartScale.x, frameRecHeart.height * heartScale.y, BLUE);

    }

            
            DrawText("Follow the Way", 10, 10, 20, RED);
            DrawText("(c) Cyberpunk Street Environment by Luis Zuno (@ansimuz)", screenWidth - 330, screenHeight - 20, 10, RAYWHITE);

        EndDrawing();
        
}

    UnloadTexture(background);  // Unload background texture
    UnloadTexture(midground);   // Unload midground texture
    UnloadTexture(foreground);  // Unload foreground texture

    UnloadTexture(catRun);
    UnloadTexture(catJump);
    UnloadTexture(heart);
    UnloadTexture(zombie);
    UnloadTexture(zombieFlipped);
    UnloadTexture(catDead);
    UnloadTexture(catSlide);


    UnloadSound(slide);
    UnloadSound(footsteps);
    
    CloseAudioDevice();
    CloseWindow();            
    return 0;
}
