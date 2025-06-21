#include "../headers/screen/dead_screen.h"
#include "../headers/main/text.h"
#include "../headers/main/globals.h"
#include <math.h>

void UpdateDeadScreen()
{
    if(IsKeyPressed(KEY_SPACE)) {
        gamestate = PLAYING; 
        score = 0;
    }
    
    if(IsKeyPressed(KEY_ESCAPE)) {
        gamestate = MAIN_MENU;
        score = 0;
    }
}

void DrawDeadScreen()
{
    const char *titleText = "YOU DIED";
    const int titleTextFontSize = 64;
    DrawAudiowideText(titleText, (Vector2){(float)SIM_WINDOW_SIZE_X / 2 - MeasureAudiowideText(titleText, titleTextFontSize).x / 2, 100}, titleTextFontSize, WHITE);
    
    const char *scoreText = TextFormat("Score: %i", score);
    const int scoreTextFontSize = 24;
    DrawAudiowideText(scoreText, (Vector2){(float)SIM_WINDOW_SIZE_X / 2 - MeasureAudiowideText(scoreText, scoreTextFontSize).x / 2, 200}, scoreTextFontSize, WHITE);
    
    const char *playText = "Press space to play again.";
    const char *playText2 = "Press escape to go back to main menu.";
    const int playTextFontSize = 32;
    Color playTextColor = ColorLerp(WHITE, (Color){255, 255, 255, 0}, (sin(GetTime() * 5) + 1) / 2);
    DrawAudiowideText(playText, (Vector2){(float)SIM_WINDOW_SIZE_X / 2 - MeasureAudiowideText(playText, playTextFontSize).x / 2, SIM_WINDOW_SIZE_Y - 100}, playTextFontSize, playTextColor);
    DrawAudiowideText(playText2, (Vector2){(float)SIM_WINDOW_SIZE_X / 2 - MeasureAudiowideText(playText2, playTextFontSize).x / 2, SIM_WINDOW_SIZE_Y - 50}, playTextFontSize, playTextColor);
}