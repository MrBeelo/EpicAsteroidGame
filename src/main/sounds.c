#include "../headers/eag.h"

Sound asteroidHit;
Sound destroyerHit;
Sound laserShoot;
Sound powerupStart;
Sound powerupEnd;
Music menuMusic;
Music gameMusic;

void LoadSounds()
{
    asteroidHit = LoadSound("sound/asteroidHit.wav");
    destroyerHit = LoadSound("sound/destroyerHit.wav");
    laserShoot = LoadSound("sound/laserShoot.wav");
    powerupStart = LoadSound("sound/powerupStart.wav");
    powerupEnd = LoadSound("sound/powerupEnd.wav");
    menuMusic = LoadMusicStream("sound/menumusic.mp3");
    gameMusic = LoadMusicStream("sound/gamemusic.mp3");
    SetSoundVolume(asteroidHit, 0.8f);
    SetSoundVolume(destroyerHit, 0.8f);
    SetSoundVolume(laserShoot, 0.8f);
    SetSoundVolume(powerupStart, 0.8f);
    SetSoundVolume(powerupEnd, 0.8f);
    SetMusicVolume(menuMusic, 0.4f);
    SetMusicVolume(gameMusic, 0.4f);
}

void UnloadSounds()
{
    UnloadSound(asteroidHit);
    UnloadSound(destroyerHit);
    UnloadSound(laserShoot);
    UnloadSound(powerupStart);
    UnloadSound(powerupEnd);
    UnloadMusicStream(menuMusic);
    UnloadMusicStream(gameMusic);
}

void ManageMusic()
{
    if(gamestate == PLAYING || gamestate == DEAD)
    {
        UpdateMusicStream(gameMusic);
        if(!IsMusicStreamPlaying(gameMusic)) PlayMusicStream(gameMusic);
        if(IsMusicStreamPlaying(menuMusic)) StopMusicStream(menuMusic);
    } else {
        UpdateMusicStream(menuMusic);
        if(!IsMusicStreamPlaying(menuMusic)) PlayMusicStream(menuMusic);
        if(IsMusicStreamPlaying(gameMusic)) StopMusicStream(gameMusic);
    }
}