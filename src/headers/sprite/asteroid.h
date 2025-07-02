#ifndef ASTEROID_H
#define ASTEROID_H

#include "../raylib/raylib.h"
#include "../main/vector.h"

#define MAX_ASTEROIDS 20

static Texture2D asteroidTexture;

typedef struct Asteroid
{
	Vector2 pos;
	float size;
	Vector2 vel;
	float rot;
	Rectangle rect;
	float speed;
	float rotSpeeed;
} Asteroid;

extern int activeAsteroids;
extern Vector asteroids;

void LoadAsteroid();
void UnloadAsteroid();
void SummonAsteroid(void* context);
void UpdateAsteroid(Asteroid* Asteroid);
void DrawAsteroid(Asteroid* Asteroid);
void KillAsteroid(Asteroid* Asteroid);

#endif
