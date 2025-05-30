#include "../headers/raylib/raylib.h"
#include "../headers/raylib/resource_dir.h"

#include "../headers/main/globals.h"
#include "../headers/main/star.h"
#include "../headers/main/destroyer.h"
#include "../headers/main/projectile.h"

Color SUPERDARKGRAY = {15, 15, 15, 255};
float simDT;
Vector2 vMouse;
Vector2 windowSize;
float scale;
RenderTexture2D target;
bool f3On;

float min(float a, float b) {
    return a < b ? a : b;
}

float max(float a, float b) {
    return a > b ? a : b;
}

float clamp(float x, float low, float high) {
    return min(max(x, low), high);
}


int main(void)
{
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(SIM_WINDOW_SIZE_X, SIM_WINDOW_SIZE_Y, "Beelo's Raylib Template");
    SearchAndSetResourceDir("res");
    
    target = LoadRenderTexture(SIM_WINDOW_SIZE_X, SIM_WINDOW_SIZE_Y);
        SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);
    
    LoadDestroyer();

    for(int i = 0; i < MAX_STARS; i++)
    {
        InitStar(&stars[i]);
    }
    
    for(int i = 0; i < MAX_PROJECTILES; i++)
    {
        InitProjectile(&projectiles[i]);   
    }
    
    Destroyer destroyer;
    InitDestroyer(&destroyer);
    
    while (!WindowShouldClose())
    {
        windowSize = (Vector2){(float) GetScreenWidth(), (float) GetScreenHeight()};
        simDT = GetFrameTime() * 60;
        
        scale = min(windowSize.x / SIM_WINDOW_SIZE_X, windowSize.y / SIM_WINDOW_SIZE_Y);
        vMouse.x = (GetMouseX() - (windowSize.x - (SIM_WINDOW_SIZE_X * scale)) * 0.5f) / scale;
        vMouse.y = (GetMouseY() - (windowSize.y - (SIM_WINDOW_SIZE_Y * scale)) * 0.5f) / scale;
        vMouse = (Vector2){clamp(vMouse.x, 0.0f, SIM_WINDOW_SIZE_X), clamp(vMouse.y, 0.0f, SIM_WINDOW_SIZE_Y)};
        
        if(IsKeyPressed(KEY_F3)) f3On = !f3On;
        
        UpdateDestroyer(&destroyer);
        
        for(int i = 0; i < MAX_STARS; i++)
        {
            UpdateStar(&stars[i], &destroyer);
        }
        
        activeProjectiles = 0;
        
        for(int i = 0; i < MAX_PROJECTILES; i++)
        {
            if(projectiles[i].active) activeProjectiles++;
            UpdateProjectile(&projectiles[i]);
        }
        
        if(target.texture.id != 0) BeginTextureMode(target);
        
        ClearBackground(SUPERDARKGRAY);
        
        for(int i = 0; i < MAX_STARS; i++)
        {
            DrawStar(&stars[i]);
        }
        
        for(int i = 0; i < MAX_PROJECTILES; i++)
        {
            DrawProjectile(&projectiles[i]);
        }
        
        DrawDestroyer(&destroyer);
        if(f3On) DrawText(TextFormat("Active Projectiles: %i", activeProjectiles), 10, 10, 32, WHITE);
        
        if(target.texture.id != 0) EndTextureMode();
        
        BeginDrawing();
        
        ClearBackground(DARKGRAY);
            
        DrawTexturePro(target.texture, (Rectangle){0, 0, (float)target.texture.width, -(float)target.texture.height}, 
            (Rectangle){(windowSize.x - SIM_WINDOW_SIZE_X * scale) * 0.5f, (windowSize.y - SIM_WINDOW_SIZE_Y * scale) * 0.5f, SIM_WINDOW_SIZE_X * scale, SIM_WINDOW_SIZE_Y * scale}, 
            (Vector2){0, 0}, 0.0f, WHITE);
            
        EndDrawing();
    }

    CloseWindow();

    return 0;
}