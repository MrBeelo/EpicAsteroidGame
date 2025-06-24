#ifndef TEXT_H
#define TEXT_H

#include "../raylib/raylib.h"

static Font audiowide;
void LoadFonts();
void UnloadFonts();
void DrawAudiowideText(const char *text, Vector2 position, float fontSize, Color tint);
void DrawAudiowideTextPro(const char *text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint);
Vector2 MeasureAudiowideText(const char *text, float fontSize);

#endif
