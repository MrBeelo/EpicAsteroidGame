#include "../headers/main/star.h"
#include "../headers/main/globals.h"

void InitStar(Star *star)
{
    star->origin.x = GetRandomValue(0, SIM_WINDOW_SIZE_X);
    star->origin.y = GetRandomValue(0, SIM_WINDOW_SIZE_Y);
    star->rot = GetRandomValue(0, 360);
    star->pos.x = star->origin.x;
    star->pos.y = star->origin.y;
}

void UpdateStar(Star *star, Destroyer *destroyer)
{
    float destroyerDistFromCenterX = destroyer->pos.x - (float)SIM_WINDOW_SIZE_X / 2;
    float destroyerDistFromCenterY = destroyer->pos.y - (float)SIM_WINDOW_SIZE_Y / 2;
    star->pos.x = star->origin.x + destroyerDistFromCenterX / 20;
    star->pos.y = star->origin.y + destroyerDistFromCenterY / 20;
}

void DrawStar(Star *star)
{
    DrawRectanglePro((Rectangle){star->pos.x, star->pos.y, STAR_SIZE, STAR_SIZE}, (Vector2){0, 0}, star->rot, WHITE);
}