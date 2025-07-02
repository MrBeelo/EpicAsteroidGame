#include "../headers/sprite/powerup.h"
#include "../headers/main/globals.h"
#include "../headers/main/text.h"
#include "../headers/main/sounds.h"

Vector powerups;
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
    powerups = NewVector(sizeof(Powerup));
}

void UnloadPowerup()
{
    UnloadTexture(healthPowerupTexture);
    UnloadTexture(scorePowerupTexture);
    UnloadTexture(projSpeedPowerupTexture);
    UnloadTexture(sizePowerupTexture);
    UnloadTexture(nothingPowerupTexture);
    DeleteVector(&powerups);
}

void SummonPowerup(void* context)
{
    (void)context;
    Vector2 powerupPos = (Vector2){(float)GetRandomValue(0, SIM_WINDOW_SIZE_X - POWERUP_SIZE), (float)GetRandomValue(0, SIM_WINDOW_SIZE_Y - POWERUP_SIZE)};
    Rectangle powerupRect = (Rectangle){powerupPos.x, powerupPos.y, POWERUP_SIZE, POWERUP_SIZE};
    enum PowerupType powerupType = (enum PowerupType)(GetRandomValue(0, 3));
    float powerupStartTime = GetTime();
    float powerupAliveTime = 0.0f;
    Powerup powerup = (Powerup){powerupType, powerupPos, powerupRect, powerupStartTime, powerupAliveTime};
    VectorPushBack(&powerups, powerup);
}

void UpdatePowerup(Powerup* powerup)
{
    powerup->aliveTime = GetTime() - powerup->startTime;
    if(powerup->aliveTime > 10.0f) VectorPop(&powerups); //ONLY BECAUSE THERE IS CONSTANTLY ONLY ONE ACTIVE POWERUP
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
    
    DrawTexturePro(texture, (Rectangle){0, 0, 32, 32}, powerup->rect, (Vector2){0, 0}, 0.0f, WHITE);
    if(f3On) DrawRectangleLinesEx(powerup->rect, 4, GREEN);
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
    
    if((lastActivatedPowerup == SCORE || lastActivatedPowerup == PROJ_SPEED || lastActivatedPowerup == SIZE) && powerupActiveAliveTime >= 9.9f && powerupActiveAliveTime < 10.0f) PlaySound(powerupEnd);
}
