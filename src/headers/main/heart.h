#ifndef HEART_H
#define HEART_H

#include "../raylib/raylib.h"

#define MAX_HEARTS 3

static Texture2D heartTexture;

typedef struct Heart
{
	int index;
	bool on;
} Heart;

extern Heart hearts[MAX_HEARTS];

void LoadHeart();
void UnloadHeart();
void InitHeart(Heart *heart);
void UpdateHeart(Heart *heart);
void DrawHeart(Heart *heart);

#endif
