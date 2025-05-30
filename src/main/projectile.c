#include "../headers/main/projectile.h"
#include "../headers/main/globals.h"
#include <math.h>

int activeProjectiles = 0;        // Define globals here
Projectile projectiles[MAX_PROJECTILES] = { 0 };

void SummonProjectile(Vector2 pos, float rot)
{
    for(int i = 0; i < MAX_PROJECTILES; i++)
    {
        if(!projectiles[i].active)
        {
            projectiles[i].pos = pos;
            projectiles[i].vel = (Vector2){cos((rot * DEG2RAD) - (PI / 2)) * PROJECTILE_SPEED, sin((rot * DEG2RAD) - (PI / 2)) * PROJECTILE_SPEED};
            projectiles[i].rot = rot;
            projectiles[i].active = true;
            
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
    for(int i = 0; i < MAX_PROJECTILES; i++)
    {
        projectiles[i].size = (Vector2){2, 8};
        projectiles[i].active = false;
    }
}

void UpdateProjectile(Projectile *projectile)
{
    if(projectile->active)
    {
        projectile->pos.x += projectile->vel.x * simDT;
        projectile->pos.y += projectile->vel.y * simDT;
        if(projectile->pos.x > SIM_WINDOW_SIZE_X + 10 || projectile->pos.x < 10 || projectile->pos.y > SIM_WINDOW_SIZE_Y + 10 || projectile->pos.y < 10) KillProjectile(projectile);
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