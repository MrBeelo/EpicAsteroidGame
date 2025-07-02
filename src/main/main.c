#include "../headers/raylib/raylib.h"
#include "../headers/raylib/resource_dir.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../headers/main/globals.h"
#include "../headers/sprite/star.h"
#include "../headers/sprite/destroyer.h"
#include "../headers/sprite/projectile.h"
#include "../headers/sprite/asteroid.h"
#include "../headers/main/timer.h"
#include "../headers/main/text.h"
#include "../headers/sprite/heart.h"
#include "../headers/screen/main_menu_screen.h"
#include "../headers/screen/dead_screen.h"
#include "../headers/sprite/powerup.h"
#include "../headers/main/sounds.h"

Color SUPERDARKGRAY = {15, 15, 15, 255};
bool shouldExitGame = false;
float simDT;
Vector2 vMouse;
Vector2 windowSize;
float scale;
RenderTexture2D target;
bool f3On = false;
int score = 0;
enum Gamestate gamestate = MAIN_MENU;
Shader shader;
float gameStartTime;
float gamePlayedTime;
int localHighScore;

float min(float a, float b) {
    return a < b ? a : b;
}

float max(float a, float b) {
    return a > b ? a : b;
}

float clamp(float x, float low, float high) {
    return min(max(x, low), high);
}

char* concat(const char *s1, const char *s2)
{
    char *result = (char *) malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void PlayGame()
{
    gamestate = PLAYING;
    gameStartTime = GetTime();
}

void SaveHighScore(int highscore)
{
    FILE *file = fopen("data.eag", "w");
    if (file == NULL) TraceLog(LOG_ERROR, "Error opening savefile");
    fprintf(file, "%d\n", highscore);
    fclose(file);
}

int GetHighScore()
{
    int highscore;
    FILE *file = fopen("data.eag", "r");
    if (file == NULL) TraceLog(LOG_ERROR, "Error opening savefile");
    fscanf(file, "%d", &highscore);
    fclose(file);
    return highscore;
}


int main(void)
{
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(SIM_WINDOW_SIZE_X, SIM_WINDOW_SIZE_Y, "Beelo's Raylib Template");
    InitAudioDevice();
    SearchAndSetResourceDir("res");
    SetExitKey(KEY_NULL);
    
    target = LoadRenderTexture(SIM_WINDOW_SIZE_X, SIM_WINDOW_SIZE_Y);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);
    
    LoadFonts();
    LoadDestroyer();
    LoadAsteroid();
    LoadHeart();
    LoadPowerup();
    LoadSounds();
    shader = LoadShader(0, TextFormat("shader/glsl%i/crt_faded.fs", GLSL_VERSION));
    
    if(!FileExists("data.eag")) SaveHighScore(0);
    localHighScore = GetHighScore();
    
    int centerLoc = GetShaderLocation(shader, "screenCenter");
    int radiusLoc = GetShaderLocation(shader, "radius");
    int intensityLoc = GetShaderLocation(shader, "intensity");
    
    stars = NewVector(sizeof(Star));

    for(int i = 0; i < MAX_STARS; i++)
    {
        SummonStar();
    }
    
    for(int i = 0; i < MAX_PROJECTILES; i++)
    {
        InitProjectile(&projectiles[i]);   
    }
    
    for(int i = 0; i < MAX_HEARTS; i++)
    {
        InitHeart(&hearts[i], i);   
    }
    
    Destroyer destroyer;
    InitDestroyer(&destroyer);
    
    Timer asteroidSpawnTimer;
    InitTimer(&asteroidSpawnTimer, 0.5f, true, true, SummonAsteroid, &destroyer);
    
    Timer powerupSpawnTimer;
    InitTimer(&powerupSpawnTimer, 20.0f, true, true, SummonPowerup, NULL);
    
    while (!WindowShouldClose() && !shouldExitGame)
    {
        gamePlayedTime = GetTime() - gameStartTime;
        
        windowSize = (Vector2){(float) GetScreenWidth(), (float) GetScreenHeight()};
        simDT = GetFrameTime() * 60;
        
        scale = min(windowSize.x / SIM_WINDOW_SIZE_X, windowSize.y / SIM_WINDOW_SIZE_Y);
        vMouse.x = (GetMouseX() - (windowSize.x - (SIM_WINDOW_SIZE_X * scale)) * 0.5f) / scale;
        vMouse.y = (GetMouseY() - (windowSize.y - (SIM_WINDOW_SIZE_Y * scale)) * 0.5f) / scale;
        vMouse = (Vector2){clamp(vMouse.x, 0.0f, SIM_WINDOW_SIZE_X), clamp(vMouse.y, 0.0f, SIM_WINDOW_SIZE_Y)};
        
        if(IsKeyPressed(KEY_F3)) f3On = !f3On;
        
        Vector2 screenCenter;
        float radius;
        float intensity;
            
        if(gamestate == PLAYING)
        {
            screenCenter.x = (destroyer.pos.x + destroyer.size.x / 2) / SIM_WINDOW_SIZE_X;
            screenCenter.y = 1.0f - ((destroyer.pos.y + destroyer.size.y / 2) / SIM_WINDOW_SIZE_Y);
        } else {
            screenCenter.x = 0.5f;
            screenCenter.y = 0.5f;
        }
        
        radius = 2.5f;
        intensity = 1.4f;
            
        SetShaderValue(shader, centerLoc, &screenCenter, SHADER_UNIFORM_VEC2);
        SetShaderValue(shader, radiusLoc, &radius, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, intensityLoc, &intensity, SHADER_UNIFORM_FLOAT);
        
        switch (gamestate) {
            case PLAYING:
            UpdateDestroyer(&destroyer);
            
            for(int i = 0; i < stars.len; i++) UpdateStar((Star*)VectorGet(&stars, i), &destroyer);
            
            activeProjectiles = 0;
            
            for(int i = 0; i < MAX_PROJECTILES; i++)
            {
                if(projectiles[i].active) activeProjectiles++;
                UpdateProjectile(&projectiles[i]);
            }
            
            activeAsteroids = asteroids.len;
            for(int i = 0; i < asteroids.len; i++) UpdateAsteroid((Asteroid*)VectorGet(&asteroids, i));
            
            activeHearts = 0;
            
            for(int i = 0; i < MAX_HEARTS; i++) if(hearts[i].on) activeHearts++;  
            for(int i = 0; i < MAX_POWERUPS; i++) UpdatePowerup(&powerups[i]);   
            
            UpdateTimer(&asteroidSpawnTimer);
            UpdateTimer(&powerupSpawnTimer);
            break;
            
            case MAIN_MENU:
            UpdateMainMenuScreen();
            break;
            
            case DEAD:
            UpdateDeadScreen();
            break;
            
            case EXIT:
            break;
        }
        
        ManageMusic();
        
        if(target.texture.id != 0) BeginTextureMode(target);
        
        ClearBackground(SUPERDARKGRAY);
        
        switch (gamestate) {
            case PLAYING:
            for(int i = 0; i < MAX_STARS; i++) DrawStar((Star*)VectorGet(&stars, i));
            for(int i = 0; i < MAX_PROJECTILES; i++) DrawProjectile(&projectiles[i]);
            for(int i = 0; i < asteroids.len; i++) DrawAsteroid((Asteroid*)VectorGet(&asteroids, i));
            for(int i = 0; i < MAX_HEARTS; i++) DrawHeart(&hearts[i]); 
            for(int i = 0; i < MAX_POWERUPS; i++) DrawPowerup(&powerups[i]); 
            DrawDestroyer(&destroyer);
            DrawAudiowideText(TextFormat("Score: %i", score), (Vector2){10, 10}, 32, WHITE);
            DrawPowerupMessage();
            break;
            
            case MAIN_MENU:
            DrawMainMenuScreen();
            break;
            
            case DEAD:
            DrawDeadScreen();
            break;
            
            case EXIT:
            break;
        }
        
        if(f3On)
        {
            DrawAudiowideText(TextFormat("Active Projectiles: %i", activeProjectiles), (Vector2){10, 50}, 16, LIGHTGRAY);
            DrawAudiowideText(TextFormat("Active Asteroids: %i", activeAsteroids), (Vector2){10, 70}, 16, LIGHTGRAY);
            DrawAudiowideText(TextFormat("Active Hearts: %i", activeHearts), (Vector2){10, 90}, 16, LIGHTGRAY);
            DrawAudiowideText(concat(TextFormat("Destroyer Position: %.1f", destroyer.pos.x), TextFormat(", %.1f", destroyer.pos.y)), (Vector2){10, 110}, 16, LIGHTGRAY);
            DrawAudiowideText(TextFormat("Immunity: %i", destroyer.immunity), (Vector2){10, 130}, 16, LIGHTGRAY);
            DrawAudiowideText(TextFormat("Last Activated Powerup: %i", (int)lastActivatedPowerup), (Vector2){10, 150}, 16, LIGHTGRAY);
            DrawAudiowideText(TextFormat("Asteroid Bonus Speed: %.2f", gamePlayedTime / 50), (Vector2){10, 170}, 16, LIGHTGRAY);
            DrawAudiowideText(TextFormat("Time Played: %.1f", gamePlayedTime), (Vector2){10, 190}, 16, LIGHTGRAY);
        }
        
        if(target.texture.id != 0) EndTextureMode();
        
        BeginDrawing();
        
        ClearBackground((Color){30, 30, 30, 255});
            
        BeginShaderMode(shader);
        DrawTexturePro(target.texture, (Rectangle){0, 0, (float)target.texture.width, -(float)target.texture.height}, 
            (Rectangle){(windowSize.x - SIM_WINDOW_SIZE_X * scale) * 0.5f, (windowSize.y - SIM_WINDOW_SIZE_Y * scale) * 0.5f, SIM_WINDOW_SIZE_X * scale, SIM_WINDOW_SIZE_Y * scale}, 
            (Vector2){0, 0}, 0.0f, WHITE);
        EndShaderMode();
            
        EndDrawing();
    }

    UnloadFonts();
    UnloadDestroyer();
    UnloadAsteroid();
    UnloadHeart();
    UnloadPowerup();
    UnloadSounds();
    UnloadShader(shader);
    
    DeleteVector(&stars);
    
    CloseAudioDevice();
    CloseWindow();

    return 0;
}