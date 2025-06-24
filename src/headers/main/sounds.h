#ifndef SOUNDS_H
#define SOUNDS_H

#include "../raylib/raylib.h"

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

#endif
