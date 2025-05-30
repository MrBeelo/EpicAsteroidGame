#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../raylib/raylib.h"

#define PROJECTILE_SPEED 15
#define MAX_PROJECTILES 10

typedef struct Projectile
{
	Vector2 pos;
	Vector2 size;
	Vector2 vel;
	float rot;
	Rectangle rect;
	bool active;
} Projectile;

extern int activeProjectiles;
extern Projectile projectiles[MAX_PROJECTILES];

void SummonProjectile(Vector2 pos, float rot);
void KillProjectile(Projectile *projectile);
void InitProjectile(Projectile *projectile);
void UpdateProjectile(Projectile *projectile);
void DrawProjectile(Projectile *projectile);

#endif
