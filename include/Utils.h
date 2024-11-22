#ifndef UTILS_H_
#define UTILS_H_

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int mouseX;
    int mouseY;
} InputManager;

inline float HireTimeInSeconds()
{
    float t = SDL_GetTicks();
    t *= 0.001f;

    return t;
}

inline double rngChooseDouble(double weightA, double a, double b)
{
    double random = (double) (rand() % 1000001 - 1) / 1000000.0;

    if (random < weightA)
    {
        return a;
    }
    
    return b;
}

inline bool rngChooseBool(double weightA, bool a, bool b)
{
    double random = (double) (rand() % 1000001 - 1) / 1000000.0;

    if (random < weightA)
    {
        return a;
    }
    
    return b;
}

#endif
