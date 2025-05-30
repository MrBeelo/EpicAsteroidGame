#include "../headers/main/timer.h"
#include <stddef.h>

void InitTimer(Timer *timer, float duration, bool repeat, bool autoStart, TimerCallback method, void* context)
{
    timer->duration = duration;
    timer->startTime = 0;
    timer->active = false;
    timer->repeat = repeat;
    timer->method = method;
    timer->context = context;
    if(autoStart) ActivateTimer(timer);
}

void ActivateTimer(Timer *timer)
{
    timer->active = true;
    timer->startTime = GetTime();
}

void ActivateTimerImmediately(Timer *timer)
{
    timer->active = true;
    timer->startTime = GetTime() - timer->duration;
}

void DeactivateTimer(Timer *timer)
{
    ForceDeactivateTimer(timer);
    if(timer->repeat) ActivateTimer(timer);
}

void ForceDeactivateTimer(Timer *timer)
{
    timer->active = false;
    timer->startTime = 0;
}

void UpdateTimer(Timer *timer)
{
    if(timer->active)
    {
        if(GetTime() - timer->startTime >= timer->duration)
        {
            if(timer->method != NULL)
            {
                timer->method(timer->context);
            }
            
            DeactivateTimer(timer);
        }
    }
}