
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
     int randValuePlatformsY = GetRandomValue(200, 300);
     int randValuePlatformsY2 = GetRandomValue(250, 350);
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

    //Platforms - Initialize off-screen so they don't spawn at game start
    for(int i = 0; i < MAX_PLATFORMS;i++){
        // Initialize pl1 and pl2 off-screen (far to the right, outside visible area)
        pl1[i].positionX = screenWidth + 1000.0f + i * 400.0f; // Start far off-screen
        pl1[i].positionY = randValuePlatformsY; // Use the initialized random Y value
        pl1[i].midCount = GetRandomValue(3, 8); // Limit platform length
        get_width_height(&pl1[i]);
        scale_tile(&pl1[i]);
        
        pl2[i].positionX = screenWidth + 1200.0f + i * 400.0f; // Start far off-screen
        pl2[i].positionY = randValuePlatformsY2; // Use the initialized random Y value
        pl2[i].midCount = GetRandomValue(3, 8); // Limit platform length
        get_width_height(&pl2[i]);
        scale_tile(&pl2[i]);
    }
  

// ----------------------Game loop-------------------------------

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Handle game state transitions
        if(gameState == PLAYING) {
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
    // Spawn zombies further away initially, like platforms
    zombies[i].positions.x = screenWidth + GetRandomValue(800, 1200);
    zombies[i].positions.y = GetRandomValue(280,360);
    zombiePositions[i].x = screenWidth + GetRandomValue(800, 1200);
    zombiePositions[i].y = GetRandomValue(280,360);
    }
 //  Zombie + cat collision - health decrament
    // Make zombie collision box much smaller (60% of size) for accurate collision
    float zombieCollisionWidth = frameZombie.width * zombieScale.x * 0.6f;
    float zombieCollisionHeight = frameZombie.height * zombieScale.y * 0.6f;
    float zombieCollisionOffsetX = frameZombie.width * zombieScale.x * 0.2f; // Center the smaller box
    float zombieCollisionOffsetY = frameZombie.height * zombieScale.y * 0.2f;
    Rectangle zombieRect = {
        zombiePosition.x + zombieCollisionOffsetX,
        zombiePosition.y + zombieCollisionOffsetY,
        zombieCollisionWidth,
        zombieCollisionHeight
    };

    for (int i = 0; i < ZOMBIE_COUNT; i++) {
           

        if(heartDecreaseCooldown <= 0.0f && CheckCollisionRecs(catRect,zombieRect)){
            catPosition.y =  catPosition.y - 9.0f;
            
            heart_count = heart_count - 1;
            heartDecreaseCooldown = 100.0f;
            PlaySound(damage);

            if(heart_count == 0){
                is_dead = true;
                currentState = DEAD;
                gameState = GAME_OVER;
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
        

        // Don't modify platform Y position every frame - only set it when respawning
        // pl1[i].positionY = randValuePlatformsY;
        // pl2[i].positionY = randValuePlatformsY2;

        if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_DOWN)){

        pl1[i].positionX -= 2.0f; 
        pl2[i].positionX -= 2.0f; 

        }
        if(IsKeyDown(KEY_SPACE) && IsKeyDown(KEY_RIGHT)){
            pl1[i].positionX -= 3.0f; 
           pl2[i].positionX -= 3.0f; 

        }
        if (pl1[i].positionX < -150.0f) {
            // Only spawn new platform if game has started (player is moving)
            if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_DOWN)) {
                float newX = screenWidth + pl1[i].Twidth + 150.0f;
                float newY = GetRandomValue(200, 300);
                float minDistance = 50.0f; // Reduced minimum distance to allow connections
                
                // Check if we should create a connected platform (30% chance)
                bool createConnected = (GetRandomValue(0, 100) < 30);
                
                if(createConnected) {
                    // Find the rightmost platform to connect to
                    float rightmostX = -1000.0f;
                    float connectY = newY;
                    
                    for(int j = 0; j < MAX_PLATFORMS; j++) {
                        if(pl1[j].positionX > rightmostX && pl1[j].positionX < screenWidth + 500.0f) {
                            rightmostX = pl1[j].positionX + pl1[j].Twidth;
                            connectY = pl1[j].positionY;
                        }
                        if(pl2[j].positionX > rightmostX && pl2[j].positionX < screenWidth + 500.0f) {
                            rightmostX = pl2[j].positionX + pl2[j].Twidth;
                            connectY = pl2[j].positionY;
                        }
                    }
                    
                    // Place platform directly connected (no gap or very small gap)
                    if(rightmostX > -500.0f) {
                        newX = rightmostX + GetRandomValue(0, 20); // Small gap or connected
                        newY = connectY; // Same Y level for connection
                    }
                }
                
                // Try to find a non-overlapping position (but allow connections)
                int attempts = 0;
                while (attempts < 20) {
                    bool overlapsPl1 = CheckPlatformOverlap(pl1, MAX_PLATFORMS, newX, newY, pl1[i].Twidth, minDistance);
                    bool overlapsPl2 = CheckPlatformOverlap(pl2, MAX_PLATFORMS, newX, newY, pl1[i].Twidth, minDistance);
                    
                    // Allow connection if platforms are at same Y and close
                    bool isConnection = false;
                    for(int j = 0; j < MAX_PLATFORMS; j++) {
                        float yDiff = fabs(newY - pl1[j].positionY);
                        float xDiff = fabs(newX - (pl1[j].positionX + pl1[j].Twidth));
                        if(yDiff < 10.0f && xDiff < 30.0f) {
                            isConnection = true;
                            break;
                        }
                        yDiff = fabs(newY - pl2[j].positionY);
                        xDiff = fabs(newX - (pl2[j].positionX + pl2[j].Twidth));
                        if(yDiff < 10.0f && xDiff < 30.0f) {
                            isConnection = true;
                            break;
                        }
                    }
                    
                    if ((!overlapsPl1 && !overlapsPl2) || isConnection) {
                        break; // Found a good position or connection
                    }
                    // Try a new random position
                    newX = screenWidth + pl1[i].Twidth + 150.0f + GetRandomValue(0, 200);
                    newY = GetRandomValue(200, 300);
                    attempts++;
                }
                
                pl1[i].positionX = newX;
                randValuePlatformsY = newY;
                pl1[i].positionY = newY;
                pl1[i].midCount = GetRandomValue(3, 8); // Limit platform length
                get_width_height(&pl1[i]);
                scale_tile(&pl1[i]);
            } else {
                // Keep platform off-screen if game hasn't started
                pl1[i].positionX = screenWidth + 1000.0f;
            }
        }
        if( pl2[i].positionX < -400.0f){
            // Only spawn new platform if game has started (player is moving)
            if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_DOWN)) {
                float newX = screenWidth + pl2[i].Twidth + 150.0f;
                float newY = GetRandomValue(250, 350);
                float minDistance = 50.0f; // Reduced minimum distance to allow connections
                
                // Check if we should create a connected platform (30% chance)
                bool createConnected = (GetRandomValue(0, 100) < 30);
                
                if(createConnected) {
                    // Find the rightmost platform to connect to
                    float rightmostX = -1000.0f;
                    float connectY = newY;
                    
                    for(int j = 0; j < MAX_PLATFORMS; j++) {
                        if(pl1[j].positionX > rightmostX && pl1[j].positionX < screenWidth + 500.0f) {
                            rightmostX = pl1[j].positionX + pl1[j].Twidth;
                            connectY = pl1[j].positionY;
                        }
                        if(pl2[j].positionX > rightmostX && pl2[j].positionX < screenWidth + 500.0f) {
                            rightmostX = pl2[j].positionX + pl2[j].Twidth;
                            connectY = pl2[j].positionY;
                        }
                    }
                    
                    // Place platform directly connected (no gap or very small gap)
                    if(rightmostX > -500.0f) {
                        newX = rightmostX + GetRandomValue(0, 20); // Small gap or connected
                        newY = connectY; // Same Y level for connection
                    }
                }
                
                // Try to find a non-overlapping position (but allow connections)
                int attempts = 0;
                while (attempts < 20) {
                    bool overlapsPl1 = CheckPlatformOverlap(pl1, MAX_PLATFORMS, newX, newY, pl2[i].Twidth, minDistance);
                    bool overlapsPl2 = CheckPlatformOverlap(pl2, MAX_PLATFORMS, newX, newY, pl2[i].Twidth, minDistance);
                    
                    // Allow connection if platforms are at same Y and close
                    bool isConnection = false;
                    for(int j = 0; j < MAX_PLATFORMS; j++) {
                        float yDiff = fabs(newY - pl1[j].positionY);
                        float xDiff = fabs(newX - (pl1[j].positionX + pl1[j].Twidth));
                        if(yDiff < 10.0f && xDiff < 30.0f) {
                            isConnection = true;
                            break;
                        }
                        yDiff = fabs(newY - pl2[j].positionY);
                        xDiff = fabs(newX - (pl2[j].positionX + pl2[j].Twidth));
                        if(yDiff < 10.0f && xDiff < 30.0f) {
                            isConnection = true;
                            break;
                        }
                    }
                    
                    if ((!overlapsPl1 && !overlapsPl2) || isConnection) {
                        break; // Found a good position or connection
                    }
                    // Try a new random position
                    newX = screenWidth + pl2[i].Twidth + 150.0f + GetRandomValue(0, 200);
                    newY = GetRandomValue(250, 350);
                    attempts++;
                }
                
                pl2[i].positionX = newX;
                randValuePlatformsY2 = newY;
                pl2[i].positionY = newY;
                pl2[i].midCount = GetRandomValue(3, 8); // Limit platform length
                get_width_height(&pl2[i]);
                scale_tile(&pl2[i]);
            } else {
                // Keep platform off-screen if game hasn't started
                pl2[i].positionX = screenWidth + 1200.0f;
            }
        }
      

    }
        // Collision platform + cat
        bool isOnPlatform = false;
        for (int i = 0; i < MAX_PLATFORMS; i++) {
           
            Rectangle platformRect = {pl1[i].positionX,pl1[i].positionY,pl1[i].Twidth,pl1[i].Theight};
            Rectangle platformRect2 = {pl2[i].positionX,pl2[i].positionY,pl2[i].Twidth,pl2[i].Theight};

            // Check platform 1
            float catFeetY = catPosition.y + catRect.height;
            float catRightX = catPosition.x + catRect.width; // Cat's actual right edge
            float platformTopY = pl1[i].positionY;
            float platformBottomY = pl1[i].positionY + pl1[i].Theight;
            float platformLeftX = pl1[i].positionX;
            float platformRightX = pl1[i].positionX + pl1[i].Twidth;
            
            // Cat is on platform ONLY if: 
            // 1. Feet are on platform top (within small tolerance)
            // 2. Cat's RIGHT EDGE is still BEFORE the platform's right edge (strict check)
            // Cat falls immediately when right edge reaches or passes platform edge
            if(catFeetY >= platformTopY - 3.0f && catFeetY <= platformBottomY + 5.0f){
                // Use a small offset (5 pixels) so cat falls slightly before visually passing edge
                // This makes it feel more responsive
                float platformRightEdge = platformRightX - 5.0f;
                // Cat is on platform only if its right edge is strictly before the adjusted edge
                if(catRightX > platformLeftX && catRightX < platformRightEdge){
                    catPlatformCollision = true;
                    isOnPlatform = true;
                    // Set cat position to platform top - don't modify platform position
                    catPosition.y = pl1[i].positionY - catRect.height + 1.0f;
                }
            }
            
            // Check platform 2
            platformTopY = pl2[i].positionY;
            platformBottomY = pl2[i].positionY + pl2[i].Theight;
            platformLeftX = pl2[i].positionX;
            platformRightX = pl2[i].positionX + pl2[i].Twidth;
            
            // Cat is on platform ONLY if: 
            // 1. Feet are on platform top (within small tolerance)
            // 2. Cat's RIGHT EDGE is still BEFORE the platform's right edge (strict check)
            // Cat falls immediately when right edge reaches or passes platform edge
            if(catFeetY >= platformTopY - 3.0f && catFeetY <= platformBottomY + 5.0f){
                // Use a small offset (5 pixels) so cat falls slightly before visually passing edge
                // This makes it feel more responsive
                float platformRightEdge = platformRightX - 5.0f;
                // Cat is on platform only if its right edge is strictly before the adjusted edge
                if(catRightX > platformLeftX && catRightX < platformRightEdge){
                    catPlatformCollision = true;
                    isOnPlatform = true;
                    // Set cat position to platform top - don't modify platform position
                    catPosition.y = pl2[i].positionY - catRect.height + 1.0f;
                }
            }
        }
        
        // If cat is not on any platform and not jumping, make it fall
        if(!isOnPlatform && currentState != JUMPING && gameState == PLAYING){
            if(catPosition.y < screenHeight - 100.0f){
                catPosition.y += ySpeed;
            }
        }
        } // End of PLAYING state



        // NOTE: Texture is scaled twice its size, so it sould be considered on scrolling
        if(gameState == PLAYING) {
            if (scrollingBack <= -background.width*2) scrollingBack = 0;
            if (scrollingMid <= -midground.width*2) scrollingMid = 0;
            if (scrollingFore <= -foreground.width*2) scrollingFore = 0;
        }
       

// ------------------------DRAW---------------------
        BeginDrawing();

            ClearBackground(GetColor(0x052c46ff));

        // Draw game elements only when playing
        if(gameState == PLAYING) {
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


            
            DrawText("Follow the Way", 10, 10, 20, RED);
            DrawText("(c) Cyberpunk Street Environment by Luis Zuno (@ansimuz)", screenWidth - 330, screenHeight - 20, 10, RAYWHITE);
        } // End of PLAYING state drawing
        
        // Draw menu screen
        if(gameState == MENU) {
            // Draw background (static)
            DrawTextureEx(background, (Vector2){ 0, 20 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(midground, (Vector2){ 0, 20 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(foreground, (Vector2){ 0, 70 }, 0.0f, 2.0f, WHITE);
            
            // Blur effect (semi-transparent overlay)
            DrawRectangle(0, 0, screenWidth, screenHeight, (Color){0, 0, 0, 180});
            
            // Title
            const char* title = "CyberCity Cat";
            int titleFontSize = 60;
            int titleWidth = MeasureText(title, titleFontSize);
            DrawText(title, screenWidth/2 - titleWidth/2, screenHeight/2 - 120, titleFontSize, GOLD);
            
            // Start button
            Rectangle startButton = {screenWidth/2 - 100, screenHeight/2 - 20, 200, 50};
            bool mouseOnStartButton = CheckCollisionPointRec(GetMousePosition(), startButton);
            Color buttonColor = mouseOnStartButton ? YELLOW : WHITE;
            
            DrawRectangleRec(startButton, buttonColor);
            DrawRectangleLinesEx(startButton, 3, DARKGRAY);
            const char* startText = "START GAME";
            int startTextWidth = MeasureText(startText, 24);
            DrawText(startText, screenWidth/2 - startTextWidth/2, screenHeight/2 - 10, 24, DARKGRAY);
            
            // Check for button click
            if(mouseOnStartButton && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                gameState = PLAYING;
                is_started = true;
            }
        }
        
        // Draw game over screen
        if(gameState == GAME_OVER) {
            // Blur effect (semi-transparent overlay)
            DrawRectangle(0, 0, screenWidth, screenHeight, (Color){0, 0, 0, 200});
            
            // Game Over text
            const char* gameOverText = "GAME OVER";
            int gameOverFontSize = 60;
            int gameOverWidth = MeasureText(gameOverText, gameOverFontSize);
            DrawText(gameOverText, screenWidth/2 - gameOverWidth/2, screenHeight/2 - 100, gameOverFontSize, RED);
            
            // Final score
            const char* finalScoreText = TextFormat("Final Score: %d", score);
            int scoreFontSize = 30;
            int scoreWidth = MeasureText(finalScoreText, scoreFontSize);
            DrawText(finalScoreText, screenWidth/2 - scoreWidth/2, screenHeight/2 - 30, scoreFontSize, WHITE);
            
            // Replay button
            Rectangle replayButton = {screenWidth/2 - 100, screenHeight/2 + 30, 200, 50};
            bool mouseOnReplayButton = CheckCollisionPointRec(GetMousePosition(), replayButton);
            Color replayButtonColor = mouseOnReplayButton ? YELLOW : WHITE;
            
            DrawRectangleRec(replayButton, replayButtonColor);
            DrawRectangleLinesEx(replayButton, 3, DARKGRAY);
            const char* replayText = "REPLAY";
            int replayTextWidth = MeasureText(replayText, 24);
            DrawText(replayText, screenWidth/2 - replayTextWidth/2, screenHeight/2 + 40, 24, DARKGRAY);
            
            // Check for replay button click
            if(mouseOnReplayButton && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                // Reset game state
                gameState = PLAYING;
                is_dead = false;
                currentState = RUNNING;
                heart_count = MAX_LIVES;
                score = 0;
                catPosition = (Vector2){0.0f, 0.0f};
                scrollingBack = 0.0f;
                scrollingMid = 0.0f;
                scrollingFore = 0.0f;
                
                // Reset platforms
                for(int i = 0; i < MAX_PLATFORMS; i++){
                    pl1[i].positionX = screenWidth + 1000.0f + i * 400.0f;
                    pl2[i].positionX = screenWidth + 1200.0f + i * 400.0f;
                }
                
                // Reset coins
                for(int i = 0; i < COIN_COUNT; i++){
                    coinPositions[i].x = GetRandomValue(150, 800);
                    coinPositions[i].y = GetRandomValue(300, 400);
                }
            }
        }

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
