#ifndef TIMER_H
#define TIMER_H

#include "../raylib/raylib.h"

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

#endif