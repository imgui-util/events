#pragma once
#include <SDL2/SDL.h>

struct SDLKeyEvent
{
    SDL_Keycode key;
    bool isDown;
};
