#include "../headers/main/heart.h"
#include "../headers/main/globals.h"

int activeHearts;
Heart hearts[MAX_HEARTS] = { 0 };

void LoadHeart()
{
    heartTexture = LoadTexture("sprite/heart.png");
}

void UnloadHeart()
{
    UnloadTexture(heartTexture);
}

void InitHeart(Heart *heart, int index)
{
    heart->on = true;
    heart->index = index;
}

void UpdateHeart(Heart *heart)
{
    //if(heart->index == MAX_HEARTS - 1 && !heart->on)
}

void DrawHeart(Heart *heart)
{
    DrawTexturePro(heartTexture, (Rectangle){0, 0, 16, 16}, (Rectangle){SIM_WINDOW_SIZE_X - 10 * (heart->index + 1) - HEART_SIZE * (heart->index + 1), 10, HEART_SIZE, HEART_SIZE}, (Vector2){0, 0}, 0.0f, heart->on ? WHITE : (Color){255, 255, 255, 50});
}

void RemoveHeart()
{
    for(int i = 0; i < MAX_HEARTS; i++)
    {
        if(hearts[i].on)
        {
            hearts[i].on = false;
            break;
        }
    }
}

void ObtainHeart()
{
    for(int i = 0; i < MAX_HEARTS; i++)
    {
        if(!hearts[i].on)
        {
            hearts[i].on = true;
            break;
        }
    }
}