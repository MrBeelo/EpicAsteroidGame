#include "../headers/main/text.h"

void LoadFonts()
{
    audiowide = LoadFont("font/audiowide.ttf");
}

void UnloadFonts()
{
    UnloadFont(audiowide);
}

void DrawAudiowideText(const char *text, Vector2 position, float fontSize, Color tint)
{
    DrawTextEx(audiowide, text, position, fontSize, 0, tint);
}

void DrawAudiowideTextPro(const char *text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint)
{
    DrawTextPro(audiowide, text, position, origin, rotation, fontSize, spacing, tint);
}