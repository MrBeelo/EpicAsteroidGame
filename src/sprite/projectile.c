#include "../headers/sprite/projectile.h"
#include "../headers/main/globals.h"
#include "../headers/sprite/asteroid.h"
#include "../headers/sprite/powerup.h"
#include "../headers/main/sounds.h"
#include <math.h>

int activeProjectiles = 0;
Projectile projectiles[MAX_PROJECTILES] = { 0 };

void SummonProjectile(Vector2 pos, float rot)
{
    for(int i = 0; i < MAX_PROJECTILES; i++)
    {
        if(!projectiles[i].active)
        {
            projectiles[i].speed = (powerupActiveAliveTime < 10.0f && lastActivatedPowerup == PROJ_SPEED) ? 30 : 15;
            projectiles[i].pos = pos;
            projectiles[i].vel = (Vector2){cos((rot * DEG2RAD) - (PI / 2)) * projectiles[i].speed, sin((rot * DEG2RAD) - (PI / 2)) * projectiles[i].speed};
            projectiles[i].rot = rot;
            projectiles[i].rect = (Rectangle){projectiles[i].pos.x, projectiles[i].pos.y, projectiles[i].size.x, projectiles[i].size.y};
            projectiles[i].active = true;
            PlaySound(laserShoot);
            break;
        }
    }
}

void KillProjectile(Projectile *projectile)
{
    projectile->active = false;
}

void InitProjectile(Projectile *projectile)
{
    projectile->size = (Vector2){4, 24};
    projectile->active = false;
}

void UpdateProjectile(Projectile *projectile)
{
    if(projectile->active)
    {
        projectile->pos.x += projectile->vel.x * simDT;
        projectile->pos.y += projectile->vel.y * simDT;
        if(projectile->pos.x > SIM_WINDOW_SIZE_X + 10 || projectile->pos.x < -10 || projectile->pos.y > SIM_WINDOW_SIZE_Y + -10 || projectile->pos.y < 10) KillProjectile(projectile);
        projectile->rect = (Rectangle){projectile->pos.x, projectile->pos.y, projectile->size.x, projectile->size.y};
        
        for(int i = 0; i < MAX_ASTEROIDS; i++) if(asteroids[i].active && CheckCollisionRecs(projectile->rect, asteroids[i].rect)) {
            score += (100 - asteroids[i].size) * ((powerupActiveAliveTime < 10.0f && lastActivatedPowerup == SCORE) ? 2 : 1);
            KillAsteroid(&asteroids[i]);
            KillProjectile(projectile);
            PlaySound(asteroidHit);
        }
    }
}

void DrawProjectile(Projectile *projectile)
{
    if(projectile->active)
    {
        DrawRectanglePro((Rectangle){projectile->pos.x, projectile->pos.y, projectile->size.x, projectile->size.y}, 
            (Vector2){projectile->size.x / 2, projectile->size.y / 2}, projectile->rot, BLUE);
    }
}