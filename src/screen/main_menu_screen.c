#include "../headers/screen/main_menu_screen.h"
#include "../headers/main/text.h"
#include "../headers/main/globals.h"
#include "../headers/sprite/destroyer.h"
#include <math.h>

void UpdateMainMenuScreen()
{
    if(IsKeyPressed(KEY_SPACE)) PlayGame();
    if(IsKeyPressed(KEY_ESCAPE)) shouldExitGame = true;
}

void DrawMainMenuScreen()
{
    const char *titleText = "EPIC ASTEROID GAME";
    const int titleTextFontSize = 64;
    DrawAudiowideText(titleText, (Vector2){(float)SIM_WINDOW_SIZE_X / 2 - MeasureAudiowideText(titleText, titleTextFontSize).x / 2, 100}, titleTextFontSize, WHITE);
    
    const char *highScoreText = TextFormat("High Score: %i", localHighScore);
    const int highScoreTextFontSize = 24;
    if(localHighScore > 0) DrawAudiowideText(highScoreText, (Vector2){(float)SIM_WINDOW_SIZE_X / 2 - MeasureAudiowideText(highScoreText, highScoreTextFontSize).x / 2, 170}, highScoreTextFontSize, WHITE);
    
    const char *playText = "Press space to play!";
    const int playTextFontSize = 32;
    Color playTextColor = ColorLerp(WHITE, (Color){255, 255, 255, 0}, (sin(GetTime() * 5) + 1) / 2);
    DrawAudiowideText(playText, (Vector2){(float)SIM_WINDOW_SIZE_X / 2 - MeasureAudiowideText(playText, playTextFontSize).x / 2, SIM_WINDOW_SIZE_Y - 100}, playTextFontSize, playTextColor);
    
    const char *creditsText = "Made with <3 by MrBeelo using Raylib and C";
    const int creditsTextFontSize = 24;
    DrawAudiowideText(creditsText, (Vector2){(float)SIM_WINDOW_SIZE_X - MeasureAudiowideText(creditsText, creditsTextFontSize).x - 10, (float)SIM_WINDOW_SIZE_Y - MeasureAudiowideText(creditsText, creditsTextFontSize).y - 10}, creditsTextFontSize, (Color){255, 255, 255, 150});
    
    const char *versionText = "1.0.1";
    const int versionTextFontSize = 24;
    DrawAudiowideText(versionText, (Vector2){10, 10}, creditsTextFontSize, (Color){255, 255, 255, 150});
    
    const char *musicText1 = "\"Space Fighter Loop\" Kevin MacLeod (incompetech.com)";
    const char *musicText2 = "Licensed under Creative Commons: By Attribution 4.0 License";
    const char *musicText3 = "http://creativecommons.org/licenses/by/4.0/";
    const int musicTextFontSize = 16;
    DrawAudiowideText(musicText1, (Vector2){10, SIM_WINDOW_SIZE_Y - musicTextFontSize * 3 - 10}, musicTextFontSize, (Color){255, 255, 255, 150});
    DrawAudiowideText(musicText2, (Vector2){10, SIM_WINDOW_SIZE_Y - musicTextFontSize * 2 - 10}, musicTextFontSize, (Color){255, 255, 255, 150});
    DrawAudiowideText(musicText3, (Vector2){10, SIM_WINDOW_SIZE_Y - musicTextFontSize - 10}, musicTextFontSize, (Color){255, 255, 255, 150});
    
    DrawDestroyerBase();
}