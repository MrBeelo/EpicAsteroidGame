#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../raylib/raylib.h"
#include "../main/vector.h"

#define MAX_PROJECTILES 5
#define PROJECTILE_SIZE_X 4
#define PROJECTILE_SIZE_Y 24

typedef struct Projectile
{
	Vector2 pos;
	Vector2 vel;
	float rot;
	Rectangle rect;
	float speed;
} Projectile;

extern int activeProjectiles;
extern Vector projectiles;

void SummonProjectile(Vector2 pos, float rot);
void UpdateProjectile(Projectile *projectile);
void DrawProjectile(Projectile *projectile);

#endif
