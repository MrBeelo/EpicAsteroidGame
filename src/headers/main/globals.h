#pragma once
#include "../raylib/raylib.h"


#define SIM_WINDOW_SIZE_X 1000
#define SIM_WINDOW_SIZE_Y 1000

extern Color SUPERDARKGRAY;
extern bool shouldExitGame;
extern float simDT;
extern Vector2 vMouse;
extern float scale;
extern RenderTexture2D target;
extern bool f3On;
extern int score;

extern float min(float a, float b);
extern float max(float a, float b);
extern float clamp(float x, float low, float high);
extern char* concat(const char *s1, const char *s2);