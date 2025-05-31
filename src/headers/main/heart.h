#ifndef HEART_H
#define HEART_H

#include "../raylib/raylib.h"

#define MAX_HEARTS 3
#define HEART_SIZE 64

static Texture2D heartTexture;

typedef struct Heart
{
	int index;
	bool on;
} Heart;

extern int activeHearts;
extern Heart hearts[MAX_HEARTS];

void LoadHeart();
void UnloadHeart();
void InitHeart(Heart *heart, int index);
void UpdateHeart(Heart *heart);
void DrawHeart(Heart *heart);
void RemoveHeart();
void ObtainHeart();

#endif
