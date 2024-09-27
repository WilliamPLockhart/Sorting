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
    bool green;
};

struct clickAble
{
    SDL_Rect rect;
    std::shared_ptr<SDL_Texture> tex = std::shared_ptr<SDL_Texture>(nullptr, SDL_DestroyTexture);
    std::string desc = "";
    int r = -1, g, b;
};
