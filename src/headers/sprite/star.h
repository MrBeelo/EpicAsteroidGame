#ifndef STAR_H
#define STAR_H

#include "../raylib/raylib.h"
#include "../sprite/destroyer.h"
#include "../main/vector.h"

#define MAX_STARS 100
#define STAR_SIZE 3

typedef struct Star
{
    Vector2 origin;
	Vector2 pos;
	float rot;
} Star;

//static Star stars[MAX_STARS] = { 0 };
extern Vector stars;

void SummonStar();
void UpdateStar(Star* star, Destroyer *destroyer);
void DrawStar(Star* star);

#endif
