#ifndef DESTROYER_H
#define DESTROYER_H

#include "../raylib/raylib.h"

#define DESTROYER_SPEED 5
#define DESTROYER_DRIFT 0.2

static Texture2D destroyerTexture;

typedef struct Destroyer
{
	Vector2 pos;
	Vector2 size;
	Vector2 vel;
	float rot;
	Rectangle rect;
	bool isMoving;
} Destroyer;

void LoadDestroyer();
void InitDestroyer(Destroyer* destroyer);
void UpdateDestroyer(Destroyer* destroyer);
void DrawDestroyer(Destroyer* destroyer);

#endif
