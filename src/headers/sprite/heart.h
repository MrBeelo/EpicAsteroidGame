#ifndef HEART_H
#define HEART_H

#include "../raylib/raylib.h"
#include "../main/vector.h"

#define MAX_HEARTS 5
#define HEART_SIZE 64

static Texture2D heartTexture;

typedef struct Heart
{
	int index;
	bool on;
} Heart;

extern int activeHearts;
extern Vector hearts;

void LoadHeart();
void UnloadHeart();
void SummonHeart(int index);
void DrawHeart(Heart *heart);
void RemoveHeart();
void ObtainHeart();

#endif
