#include "../headers/sprite/asteroid.h"
#include "../headers/main/globals.h"
#include "../headers/sprite/destroyer.h"
#include <math.h>

int activeAsteroids = 0;
Vector asteroids;


void LoadAsteroid()
{
    asteroidTexture = LoadTexture("sprite/asteroid.png");
    asteroids = NewVector(sizeof(Asteroid));
}

void UnloadAsteroid()
{
    UnloadTexture(asteroidTexture);
    DeleteVector(&asteroids);
}

void SummonAsteroid(void* context)
{
    (void)context;
    Destroyer* destroyer = (Destroyer*)context;
    float asteroidValRot = GetRandomValue(0, 360);
    float asteroidValSpeed = GetRandomValue(2, 6) + gamePlayedTime / 50;
    float asteroidValRotSpeed = GetRandomValue(2, 7);
    float asteroidValSize = GetRandomValue(25, 70);
    Vector2 asteroidValVel = (Vector2){cos((asteroidValRot * DEG2RAD) - (PI / 2)) * asteroidValSpeed, sin((asteroidValRot * DEG2RAD) - (PI / 2)) * asteroidValSpeed};
    Vector2 asteroidValPos = (Vector2){(float)SIM_WINDOW_SIZE_X / 2 - asteroidValSize / 2 + cos((asteroidValRot * DEG2RAD) - (PI / 2)) * -SIM_WINDOW_SIZE_X, (float)SIM_WINDOW_SIZE_Y / 2 - asteroidValSize / 2 + sin((asteroidValRot * DEG2RAD) - (PI / 2)) * -SIM_WINDOW_SIZE_Y};
    Rectangle asteroidValRect = (Rectangle){asteroidValPos.x, asteroidValPos.y, asteroidValSize, asteroidValSize};
    VectorPushBack(&asteroids, ((Asteroid){asteroidValPos, asteroidValSize, asteroidValVel, asteroidValRot, asteroidValRect, asteroidValSpeed, asteroidValRotSpeed}));
}

void UpdateAsteroid(Asteroid* asteroid)
{
    asteroid->pos.x += asteroid->vel.x * simDT;
    asteroid->pos.y += asteroid->vel.y * simDT;
    if(asteroids.len > MAX_ASTEROIDS) VectorRemoveAt(&asteroids, 0);
    if(asteroid->rot <= 360) asteroid->rot += asteroid->rotSpeeed; else asteroid->rot = 0;
    asteroid->rect = (Rectangle){asteroid->pos.x, asteroid->pos.y, asteroid->size, asteroid->size};
}

void DrawAsteroid(Asteroid* asteroid)
{
    DrawTexturePro(asteroidTexture, (Rectangle){0, 0, 32, 32}, 
        (Rectangle){asteroid->pos.x + asteroid->size / 2, asteroid->pos.y + asteroid->size / 2, asteroid->size, asteroid->size}, 
        (Vector2){asteroid->size / 2, asteroid->size / 2}, asteroid->rot, WHITE);
    if(f3On) DrawRectangleLinesEx(asteroid->rect, 4, RED);
}
