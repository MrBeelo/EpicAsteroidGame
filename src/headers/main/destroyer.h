#ifndef DESTROYER_H
#define DESTROYER_H

#include "../raylib/raylib.h"

#define DESTROYER_SPEED 15
#define DESTROYER_DRIFT 0.2
#define DESTROYER_HITBOX_BUFFER 30

static Texture2D destroyerTexture;

typedef struct Destroyer
{
	Vector2 pos;
	Vector2 size;
	Vector2 vel;
	float rot;
	Rectangle rect;
	Rectangle hitbox;
	bool isMoving;
	int immunity;
} Destroyer;

void LoadDestroyer();
void UnloadDestroyer();
void InitDestroyer(Destroyer* destroyer);
void UpdateDestroyer(Destroyer* destroyer);
void DrawDestroyer(Destroyer* destroyer);

#endif
