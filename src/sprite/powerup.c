#include "../headers/sprite/powerup.h"
#include "../headers/main/globals.h"
#include "../headers/main/text.h"

Powerup powerups[MAX_POWERUPS] = { (enum PowerupType)4, 0 };
float powerupActiveStartTime;
float powerupActiveAliveTime;
enum PowerupType lastActivatedPowerup = NOTHING;

void LoadPowerup()
{
    healthPowerupTexture = LoadTexture("sprite/powerup/health_powerup.png");
    scorePowerupTexture = LoadTexture("sprite/powerup/score_powerup.png");
    projSpeedPowerupTexture = LoadTexture("sprite/powerup/projspeed_powerup.png");
    sizePowerupTexture = LoadTexture("sprite/powerup/size_powerup.png");
    nothingPowerupTexture = LoadTexture("sprite/powerup/powerup.png");
}

void UnloadPowerup()
{
    UnloadTexture(healthPowerupTexture);
    UnloadTexture(scorePowerupTexture);
    UnloadTexture(projSpeedPowerupTexture);
    UnloadTexture(sizePowerupTexture);
    UnloadTexture(nothingPowerupTexture);
}

void SummonPowerup(void* context)
{
    (void)context;
    for(int i = 0; i < MAX_POWERUPS; i++)
    {
        if(!powerups[i].active)
        {
            powerups[i].pos = (Vector2){(float)GetRandomValue(0, SIM_WINDOW_SIZE_X - POWERUP_SIZE), (float)GetRandomValue(0, SIM_WINDOW_SIZE_Y - POWERUP_SIZE)};
            powerups[i].rect = (Rectangle){powerups[i].pos.x, powerups[i].pos.y, POWERUP_SIZE, POWERUP_SIZE};
            powerups[i].active = true;
            powerups[i].type = (enum PowerupType)(GetRandomValue(0, 3));
            powerups[i].startTime = GetTime();
            powerups[i].aliveTime = 0.0f;
            break;
        }
    }
}

void UpdatePowerup(Powerup* powerup)
{
    powerupActiveAliveTime = GetTime() - powerupActiveStartTime;
    if(powerup->active)
    {
        powerup->aliveTime = GetTime() - powerup->startTime;
        if(powerup->aliveTime > 10.0f) KillPowerup(powerup);
    }
}

void DrawPowerup(Powerup* powerup)
{
    Texture2D texture;
    
    switch (powerup->type) {
        case HEALTH: texture = healthPowerupTexture; break;
        case SCORE: texture = scorePowerupTexture; break;
        case PROJ_SPEED: texture = projSpeedPowerupTexture; break;
        case SIZE: texture = sizePowerupTexture; break;
        case NOTHING: texture = nothingPowerupTexture; break;
    }
    
    if(powerup->active)
    {
        DrawTexturePro(texture, (Rectangle){0, 0, 32, 32}, powerup->rect, (Vector2){0, 0}, 0.0f, WHITE);
        if(f3On) DrawRectangleLinesEx(powerup->rect, 4, GREEN);
    }
}

void KillPowerup(Powerup* Powerup)
{
    Powerup->active = false;
}

void DrawPowerupMessage()
{
    const char *healthText = "YOU HAVE BEEN GRANTED HEALTH";
    const char *scoreText = "SCORE DOUBLED";
    const char *sizeText = "DESTROYER SIZE SHRUNK";
    const char *projSpeedText = "PROJECTILE SPEED DOUBLED";
    float fontSize = 48;
    
    if(lastActivatedPowerup == HEALTH && powerupActiveAliveTime < 2.0f) DrawAudiowideText(healthText, (Vector2){(float)SIM_WINDOW_SIZE_X / 2 - MeasureAudiowideText(healthText, fontSize).x / 2, 200}, fontSize, RED);
    if(lastActivatedPowerup == SCORE && powerupActiveAliveTime < 10.0f) DrawAudiowideText(scoreText, (Vector2){(float)SIM_WINDOW_SIZE_X / 2 - MeasureAudiowideText(scoreText, fontSize).x / 2, 200}, fontSize, YELLOW);
    if(lastActivatedPowerup == SIZE && powerupActiveAliveTime < 10.0f) DrawAudiowideText(sizeText, (Vector2){(float)SIM_WINDOW_SIZE_X / 2 - MeasureAudiowideText(sizeText, fontSize).x / 2, 200}, fontSize, GREEN);
    if(lastActivatedPowerup == PROJ_SPEED && powerupActiveAliveTime < 10.0f) DrawAudiowideText(projSpeedText, (Vector2){(float)SIM_WINDOW_SIZE_X / 2 - MeasureAudiowideText(projSpeedText, fontSize).x / 2, 200}, fontSize, SKYBLUE);
}
