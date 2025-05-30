#include "../headers/main/asteroid.h"
#include "../headers/main/globals.h"
#include <math.h>

int activeAsteroids = 0;        // Define globals here
Asteroid asteroids[MAX_ASTEROIDS] = { 0 };

void LoadAsteroid()
{
    asteroidTexture = LoadTexture("sprite/asteroid.png");
}

void SummonAsteroid(void* context)
{
    (void)context;
    for(int i = 0; i < MAX_ASTEROIDS; i++)
    {
        if(!asteroids[i].active)
        {
            asteroids[i].rot = GetRandomValue(0, 360);
            asteroids[i].speed = GetRandomValue(4, 8);
            asteroids[i].rotSpeeed = GetRandomValue(2, 10);
            asteroids[i].size = GetRandomValue(25, 60);
            asteroids[i].vel = (Vector2){cos((asteroids[i].rot * DEG2RAD) - (PI / 2)) * asteroids[i].speed, sin((asteroids[i].rot * DEG2RAD) - (PI / 2)) * asteroids[i].speed};
            asteroids[i].pos = (Vector2){(float)SIM_WINDOW_SIZE_X / 2 - asteroids[i].size / 2 + cos((asteroids[i].rot * DEG2RAD) - (PI / 2)) * -SIM_WINDOW_SIZE_X, (float)SIM_WINDOW_SIZE_Y / 2 - asteroids[i].size / 2 + sin((asteroids[i].rot * DEG2RAD) - (PI / 2)) * -SIM_WINDOW_SIZE_Y};
            asteroids[i].active = true;
            asteroids[i].rect = (Rectangle){asteroids[i].pos.x, asteroids[i].pos.y, asteroids[i].size, asteroids[i].size};
            
            break;
        }
    }
}

void UpdateAsteroid(Asteroid* asteroid)
{
    if(asteroid->active)
    {
        asteroid->pos.x += asteroid->vel.x * simDT;
        asteroid->pos.y += asteroid->vel.y * simDT;
        if(asteroid->pos.x > SIM_WINDOW_SIZE_X + 500 || asteroid->pos.x < -500 || asteroid->pos.y > SIM_WINDOW_SIZE_Y + 500 || asteroid->pos.y < -500) KillAsteroid(asteroid);
        if(asteroid->rot <= 360) asteroid->rot += asteroid->rotSpeeed; else asteroid->rot = 0;
        asteroid->rect = (Rectangle){asteroid->pos.x, asteroid->pos.y, asteroid->size, asteroid->size};
    }
}

void DrawAsteroid(Asteroid* asteroid)
{
    if(asteroid->active)
    {
        DrawTexturePro(asteroidTexture, (Rectangle){0, 0, 32, 32}, asteroid->rect, (Vector2){asteroid->size / 2, asteroid->size / 2}, asteroid->rot, WHITE);
    }
}

void KillAsteroid(Asteroid* asteroid)
{
    asteroid->active = false;
}
