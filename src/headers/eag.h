#ifndef EAG_H
#define EAG_H

#include "raylib/raylib.h"
#include "raylib/resource_dir.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

// GLOBALS //

#define SIM_WINDOW_SIZE_X 1000
#define SIM_WINDOW_SIZE_Y 1000

#if defined(PLATFORM_WEB)
    #define GLSL_VERSION            100
#else
    #define GLSL_VERSION            330
#endif

enum Gamestate {
    PLAYING,
    MAIN_MENU,
    DEAD
};

extern Color SUPERDARKGRAY;
extern bool shouldExitGame;
extern float simDT;
extern Vector2 vMouse;
extern float scale;
extern RenderTexture2D target;
extern bool f3On;
extern int score;
extern enum Gamestate gamestate;
extern Shader shader;
extern float gameStartTime;
extern float gamePlayedTime;
extern int localHighScore;

extern float min(float a, float b);
extern float max(float a, float b);
extern float clamp(float x, float low, float high);
extern char* concat(const char *s1, const char *s2);

extern void PlayGame();
extern void SaveHighScore(int highscore);
extern int GetHighScore();

// SOUNDS //

extern Sound asteroidHit;
extern Sound destroyerHit;
extern Sound laserShoot;
extern Sound powerupStart;
extern Sound powerupEnd;
extern Music menuMusic;
extern Music gameMusic;
void LoadSounds();
void UnloadSounds();
void ManageMusic();

// FONTS //

static Font audiowide;
void LoadFonts();
void UnloadFonts();
void DrawAudiowideText(const char *text, Vector2 position, float fontSize, Color tint);
void DrawAudiowideTextPro(const char *text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint);
Vector2 MeasureAudiowideText(const char *text, float fontSize);

// TIMERS //

typedef void (*TimerCallback)(void* context);

typedef struct Timer {
    float duration;
    float startTime;
    bool active;
    bool repeat;
    TimerCallback method;
    void *context;
} Timer;

void InitTimer(Timer *timer, float duration, bool repeat, bool autoStart, TimerCallback method, void* context);
void ActivateTimer(Timer *timer);
void ActivateTimerImmediately(Timer *timer);
void DeactivateTimer(Timer *timer);
void ForceDeactivateTimer(Timer *timer);
void UpdateTimer(Timer *timer);

// VECTORS //

typedef struct {
    int len;
    size_t elem_size;
    void* contents;
} Vector;

Vector NewVector(size_t elem_size);
void DeleteVector(Vector* vec);
void ClearVector(Vector* vec);
int VectorLength(Vector* vec);
void VectorPushBackPointer(Vector* vec, void* val);
void VectorRemoveAt(Vector* vec, int index);
void VectorPop(Vector* vec);
void* VectorGet(Vector* vec, int index);
void VectorSetPointer(Vector* vec, int index, void* val);

#define VectorPushBack(vec, value) do {  \
    __typeof__(value) _val = (value);    \
    VectorPushBackPointer((vec), &_val); \
} while (0)

#define VectorSet(vec, index, value) do {  \
    __typeof__(value) _val = (value);      \
    VectorSetPointer((vec), index, &_val); \
} while (0)

// SCREENS //

void UpdateDeadScreen();
void DrawDeadScreen();

void UpdateMainMenuScreen();
void DrawMainMenuScreen();

// ASTEROIDS //

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

// DESTROYER //

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
void ResetDestroyer(Destroyer* destroyer);
void DrawDestroyerBase();

// HEARTS //

#define MAX_HEARTS 5
#define HEART_SIZE 64

static Texture2D heartTexture;

typedef struct Heart
{
	int index;
	bool on;
} Heart;

extern int activeHearts;
extern Vector hearts;

void LoadHeart();
void UnloadHeart();
void SummonHeart(int index);
void DrawHeart(Heart *heart);
void RemoveHeart();
void ObtainHeart();

// POWERUPS //

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
	float startTime;
	float aliveTime;
} Powerup;

extern Vector powerups;
extern float powerupActiveStartTime;
extern float powerupActiveAliveTime;
extern enum PowerupType lastActivatedPowerup;

void LoadPowerup();
void UnloadPowerup();
void SummonPowerup(void* context);
void UpdatePowerup(Powerup* powerup);
void DrawPowerup(Powerup* powerup);
void DrawPowerupMessage();

// PROJECTILES //

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

// STARS //

#define MAX_STARS 100
#define STAR_SIZE 3

typedef struct Star
{
    Vector2 origin;
	Vector2 pos;
	float rot;
} Star;

//static Star stars[MAX_STARS] = { 0 };
extern Vector stars;

void SummonStar();
void UpdateStar(Star* star, Destroyer *destroyer);
void DrawStar(Star* star);

#endif