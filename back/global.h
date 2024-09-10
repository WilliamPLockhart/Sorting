#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct item
{
    SDL_Rect rect;
    bool red;
};