#include "../headers/sprite/heart.h"
#include "../headers/main/globals.h"

int activeHearts;
Vector hearts;

void LoadHeart()
{
    heartTexture = LoadTexture("sprite/heart.png");
    hearts = NewVector(sizeof(Heart));
}

void UnloadHeart()
{
    UnloadTexture(heartTexture);
    DeleteVector(&hearts);
}

void SummonHeart(int index)
{
    Heart heart = (Heart){index, true};
    VectorPushBack(&hearts, heart);
}

void DrawHeart(Heart *heart)
{
    DrawTexturePro(heartTexture, (Rectangle){0, 0, 16, 16}, (Rectangle){SIM_WINDOW_SIZE_X - 10 * (heart->index + 1) - HEART_SIZE * (heart->index + 1), 10, HEART_SIZE, HEART_SIZE}, (Vector2){0, 0}, 0.0f, heart->on ? WHITE : (Color){255, 255, 255, 50});
}

void RemoveHeart()
{
    for(int i = 0; i < hearts.len; i++)
    {
        Heart* heartVal = (Heart*)VectorGet(&hearts, i);
        
        if(heartVal->on) {
            heartVal->on = false; 
            break;
        }
    }
}

void ObtainHeart()
{
    for(int i = 0; i < hearts.len; i++)
    {
        Heart* heartVal = (Heart*)VectorGet(&hearts, i);
        Heart* prevHeartVal = (Heart*)VectorGet(&hearts, i - 1);
        
        if(heartVal->on && i - 1 >= 0) 
        {
            prevHeartVal->on = true; 
            break;
        }
    }
}