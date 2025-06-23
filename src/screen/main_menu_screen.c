#include "../headers/screen/main_menu_screen.h"
#include "../headers/main/text.h"
#include "../headers/main/globals.h"
#include "../headers/sprite/destroyer.h"
#include <math.h>

void UpdateMainMenuScreen()
{
    if(IsKeyPressed(KEY_SPACE)) gamestate = PLAYING;
    if(IsKeyPressed(KEY_ESCAPE)) shouldExitGame = true;
}

void DrawMainMenuScreen()
{
    const char *titleText = "EPIC ASTEROID GAME";
    const int titleTextFontSize = 64;
    DrawAudiowideText(titleText, (Vector2){(float)SIM_WINDOW_SIZE_X / 2 - MeasureAudiowideText(titleText, titleTextFontSize).x / 2, 100}, titleTextFontSize, WHITE);
    
    const char *playText = "Press space to play!";
    const int playTextFontSize = 32;
    Color playTextColor = ColorLerp(WHITE, (Color){255, 255, 255, 0}, (sin(GetTime() * 5) + 1) / 2);
    DrawAudiowideText(playText, (Vector2){(float)SIM_WINDOW_SIZE_X / 2 - MeasureAudiowideText(playText, playTextFontSize).x / 2, SIM_WINDOW_SIZE_Y - 100}, playTextFontSize, playTextColor);
    
    const char *creditsText = "Made with <3 by MrBeelo using Raylib and C";
    const int creditsTextFontSize = 24;
    DrawAudiowideText(creditsText, (Vector2){(float)SIM_WINDOW_SIZE_X - MeasureAudiowideText(creditsText, creditsTextFontSize).x - 10, (float)SIM_WINDOW_SIZE_Y - MeasureAudiowideText(creditsText, creditsTextFontSize).y - 10}, creditsTextFontSize, (Color){255, 255, 255, 150});
    
    DrawDestroyerBase();
}