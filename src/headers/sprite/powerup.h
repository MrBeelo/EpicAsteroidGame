#ifndef POWERUP_H
#define POWERUP_H

#include "../raylib/raylib.h"

#define MAX_POWERUPS 3
#define POWERUP_SIZE 64

static Texture2D healthPowerupTexture;
static Texture2D scorePowerupTexture;
static Texture2D projSpeedPowerupTexture;
static Texture2D sizePowerupTexture;
static Texture2D nothingPowerupTexture;

enum PowerupType {
    HEALTH,
    SCORE,
    PROJ_SPEED,
    SIZE,
    NOTHING
};

typedef struct Powerup
{
    enum PowerupType type;
	Vector2 pos;
	Rectangle rect;
	bool active;
	float startTime;
	float aliveTime;
} Powerup;

extern Powerup powerups[MAX_POWERUPS];
extern float powerupActiveStartTime;
extern float powerupActiveAliveTime;
extern enum PowerupType lastActivatedPowerup;

void LoadPowerup();
void UnloadPowerup();
void SummonPowerup(void* context);
void UpdatePowerup(Powerup* powerup);
void DrawPowerup(Powerup* powerup);
void KillPowerup(Powerup* powerup);
void DrawPowerupMessage();

#endif
