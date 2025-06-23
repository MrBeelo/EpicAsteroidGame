#include "../headers/sprite/destroyer.h"
#include "../headers/main/globals.h"
#include "../headers/sprite/projectile.h"
#include "../headers/sprite/asteroid.h"
#include "../headers/sprite/heart.h"
#include "../headers/sprite/powerup.h"
#include <math.h>

void LoadDestroyer()
{
    destroyerTexture = LoadTexture("sprite/destroyer.png");
}

void UnloadDestroyer()
{
    UnloadTexture(destroyerTexture);
}

void InitDestroyer(Destroyer *destroyer)
{
    destroyer->size = (Vector2){128, 128};
    destroyer->pos = (Vector2){(float)SIM_WINDOW_SIZE_X / 2 - (float)destroyer->size.x / 2, (float)SIM_WINDOW_SIZE_Y / 2 - (float)destroyer->size.y / 2};
    destroyer->vel = (Vector2){0, 0};
    destroyer->rot = 0;
    destroyer->rect = (Rectangle){destroyer->pos.x, destroyer->pos.y, destroyer->size.x, destroyer->size.y};
    destroyer->hitbox = (Rectangle){destroyer->pos.x + DESTROYER_HITBOX_BUFFER, destroyer->pos.y + DESTROYER_HITBOX_BUFFER, destroyer->size.x - DESTROYER_HITBOX_BUFFER * 2, destroyer->size.y - DESTROYER_HITBOX_BUFFER * 2};
    destroyer->immunity = 0;
}

void UpdateDestroyer(Destroyer *destroyer)
{
    destroyer->isMoving = false;
    destroyer->size.x = (powerupActiveAliveTime < 10.0f && lastActivatedPowerup == SIZE) ? 96 : 128;
    destroyer->size.y = (powerupActiveAliveTime < 10.0f && lastActivatedPowerup == SIZE) ? 96 : 128;
    if(IsKeyDown(KEY_A))
    {
        if(destroyer->vel.x > -DESTROYER_SPEED) destroyer->vel.x -= DESTROYER_DRIFT * simDT;
        else if(destroyer->vel.x < -DESTROYER_SPEED) destroyer->vel.x += DESTROYER_DRIFT * simDT;
        destroyer->isMoving = true;
    } else if(IsKeyDown(KEY_D))
    {
        if(destroyer->vel.x > DESTROYER_SPEED) destroyer->vel.x -= DESTROYER_DRIFT * simDT;
        else if(destroyer->vel.x < DESTROYER_SPEED) destroyer->vel.x += DESTROYER_DRIFT * simDT;
        destroyer->isMoving = true;
    } else {
        if(destroyer->vel.x > 0) destroyer->vel.x -= DESTROYER_DRIFT * simDT;
        else if(destroyer->vel.x < 0) destroyer->vel.x += DESTROYER_DRIFT * simDT;
    }
    
    if(IsKeyDown(KEY_W))
    {
        if(destroyer->vel.y > -DESTROYER_SPEED) destroyer->vel.y -= DESTROYER_DRIFT * simDT;
        else if(destroyer->vel.y < -DESTROYER_SPEED) destroyer->vel.y += DESTROYER_DRIFT * simDT;
        destroyer->isMoving = true;
    } else if(IsKeyDown(KEY_S))
    {
        if(destroyer->vel.y > DESTROYER_SPEED) destroyer->vel.y -= DESTROYER_DRIFT * simDT;
        else if(destroyer->vel.y < DESTROYER_SPEED) destroyer->vel.y += DESTROYER_DRIFT * simDT;
        destroyer->isMoving = true;
    } else {
        if(destroyer->vel.y > 0) destroyer->vel.y -= DESTROYER_DRIFT * simDT;
        else if(destroyer->vel.y < 0) destroyer->vel.y += DESTROYER_DRIFT * simDT;
    }
    
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) SummonProjectile((Vector2){destroyer->pos.x + destroyer->size.x / 2, destroyer->pos.y + destroyer->size.y / 2}, destroyer->rot);
    
    destroyer->pos.x += destroyer->vel.x * simDT;
    destroyer->pos.y += destroyer->vel.y * simDT;
    
    destroyer->pos.x = clamp(destroyer->pos.x, 0, SIM_WINDOW_SIZE_X - destroyer->size.x);
    destroyer->pos.y = clamp(destroyer->pos.y, 0, SIM_WINDOW_SIZE_Y - destroyer->size.y);
    
    destroyer->rot = (float) atan2(vMouse.y - destroyer->pos.y, vMouse.x - destroyer->pos.x) * RAD2DEG + 90.0f;
    
    destroyer->rect = (Rectangle){destroyer->pos.x, destroyer->pos.y, destroyer->size.x, destroyer->size.y};
    destroyer->hitbox = (Rectangle){destroyer->pos.x + DESTROYER_HITBOX_BUFFER, destroyer->pos.y + DESTROYER_HITBOX_BUFFER, destroyer->size.x - DESTROYER_HITBOX_BUFFER * 2, destroyer->size.y - DESTROYER_HITBOX_BUFFER * 2};
    
    if(destroyer->pos.x <= 0 || destroyer->pos.x >= SIM_WINDOW_SIZE_X - destroyer->size.x) destroyer->vel.x = 0;
    if(destroyer->pos.y <= 0 || destroyer->pos.y >= SIM_WINDOW_SIZE_Y - destroyer->size.y) destroyer->vel.y = 0;
    
    for(int i = 0; i < MAX_ASTEROIDS; i++)
    {
        if(asteroids[i].active && CheckCollisionRecs(destroyer->hitbox, asteroids[i].rect) && destroyer->immunity == 0)
        {
            destroyer->immunity = 300;
            RemoveHeart();
        }
    }
    
    for(int i = 0; i < MAX_POWERUPS; i++)
    {
        if(powerups[i].active && CheckCollisionRecs(destroyer->hitbox, powerups[i].rect))
        {
            lastActivatedPowerup = powerups[i].type;
            powerupActiveStartTime = GetTime();
            powerups[i].active = false;
            if(lastActivatedPowerup == HEALTH) ObtainHeart();
        }
    }
    
    if(destroyer->immunity > 0) destroyer->immunity -= simDT;
    
    if(!hearts[MAX_HEARTS - 1].on)
    {
        gamestate = DEAD;
        ResetDestroyer(destroyer);
    }
}

void DrawDestroyer(Destroyer *destroyer)
{
    Color destroyerColor = WHITE;
    if(destroyer->immunity > 0) destroyerColor =  ColorLerp(WHITE, RED, (sin(GetTime() * 5) + 1) / 2);
    
    DrawTexturePro(destroyerTexture, (Rectangle){destroyer->isMoving * 32, 0, 32, 32},
        (Rectangle){destroyer->pos.x + destroyer->size.x / 2, destroyer->pos.y + destroyer->size.y / 2, destroyer->size.x, destroyer->size.y}, 
        (Vector2){destroyer->size.x / 2, destroyer->size.y / 2}, destroyer->rot, destroyerColor);
    if(f3On) DrawRectangleLinesEx(destroyer->rect, 4, ORANGE);
    if(f3On) DrawRectangleLinesEx(destroyer->hitbox, 4, YELLOW);
}

void ResetDestroyer(Destroyer* destroyer)
{
    destroyer->pos = (Vector2){(float)SIM_WINDOW_SIZE_X / 2 - (float)destroyer->size.x / 2, (float)SIM_WINDOW_SIZE_Y / 2 - (float)destroyer->size.y / 2};
    destroyer->vel = (Vector2){0, 0};
    destroyer->rot = 0;
    
    destroyer->rect = (Rectangle){destroyer->pos.x, destroyer->pos.y, destroyer->size.x, destroyer->size.y};
    destroyer->hitbox = (Rectangle){destroyer->pos.x + DESTROYER_HITBOX_BUFFER, destroyer->pos.y + DESTROYER_HITBOX_BUFFER, destroyer->size.x - DESTROYER_HITBOX_BUFFER * 2, destroyer->size.y - DESTROYER_HITBOX_BUFFER * 2};
    
    for(int i = 0; i < MAX_HEARTS; i++) hearts[i].on = true;
    
    powerupActiveStartTime = GetTime();
    lastActivatedPowerup = NOTHING;
}

void DrawDestroyerBase()
{
    Vector2 destroyerBasePos = (Vector2){(float)SIM_WINDOW_SIZE_X / 2 - 64, (float)SIM_WINDOW_SIZE_Y / 2 - 64};
    float destroyerBaseRot = (float) atan2(vMouse.y - destroyerBasePos.y, vMouse.x - destroyerBasePos.x) * RAD2DEG + 90.0f;
    DrawTexturePro(destroyerTexture, (Rectangle){0, 0, 32, 32},
        (Rectangle){destroyerBasePos.x + 64, destroyerBasePos.y + 64, 128, 128}, 
        (Vector2){64, 64}, destroyerBaseRot, WHITE);
}