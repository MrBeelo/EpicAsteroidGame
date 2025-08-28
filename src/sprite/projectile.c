#include "../headers/eag.h"

int activeProjectiles = 0;
Vector projectiles;

void SummonProjectile(Vector2 pos, float rot)
{
    float projectileSpeed = (powerupActiveAliveTime < 10.0f && lastActivatedPowerup == PROJ_SPEED) ? 30 : 15;
    Vector2 projectilePos = pos;
    Vector2 projectileVel = (Vector2){cos((rot * DEG2RAD) - (PI / 2)) * projectileSpeed, sin((rot * DEG2RAD) - (PI / 2)) * projectileSpeed};
    float projectileRot = rot;
    Rectangle projectileRect = (Rectangle){projectilePos.x, projectilePos.y, PROJECTILE_SIZE_X, PROJECTILE_SIZE_Y};
    PlaySound(laserShoot);
    VectorPushBack(&projectiles, ((Projectile){projectilePos, projectileVel, projectileRot, projectileRect, projectileSpeed}));
}

void UpdateProjectile(Projectile *projectile)
{
    projectile->pos.x += projectile->vel.x * simDT;
    projectile->pos.y += projectile->vel.y * simDT;
    if(projectiles.len > MAX_PROJECTILES) VectorRemoveAt(&projectiles, 0);
    projectile->rect = (Rectangle){projectile->pos.x, projectile->pos.y, PROJECTILE_SIZE_X, PROJECTILE_SIZE_Y};
    
    for(int i = 0; i < asteroids.len; i++) 
    {
        if(CheckCollisionRecs(projectile->rect, ((Asteroid*)VectorGet(&asteroids, i))->rect)) {
            score += (100 - ((Asteroid*)VectorGet(&asteroids, i))->size) * ((powerupActiveAliveTime < 10.0f && lastActivatedPowerup == SCORE) ? 2 : 1);
            VectorRemoveAt(&asteroids, i);
            PlaySound(asteroidHit);
        }
    }
}

void DrawProjectile(Projectile *projectile)
{
    DrawRectanglePro((Rectangle){projectile->pos.x, projectile->pos.y, PROJECTILE_SIZE_X, PROJECTILE_SIZE_Y}, 
        (Vector2){(float)PROJECTILE_SIZE_X / 2, (float)PROJECTILE_SIZE_Y / 2}, projectile->rot, BLUE);
}