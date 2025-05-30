#include "../headers/main/heart.h"

Heart hearts[MAX_HEARTS] = { 0 };

void LoadHeart()
{
    heartTexture = LoadTexture("sprite/heart.png");
}

void UnloadHeart()
{
    UnloadTexture(heartTexture);
}