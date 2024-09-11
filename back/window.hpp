#pragma once
#include "global.h"
class window
{
public:
    // sdl
    window(const std::string &title, int width, int height, bool fullscreen);
    bool init();
    bool setIcon(const char *fileLocation);
    void render(bool sound = false, bool sorted = false);

    //"normal" functions
    void
    setVect(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list)
    {
        m_entities = list;
    }

    // variables
    int windowHeight;
    int windowWidth;
    int windowY;
    int windowX;
    std::vector<clickAble> listEvents;

private:
    // window stuff
    bool m_running;
    bool m_winScreen = false;
    std::shared_ptr<std::vector<std::shared_ptr<item>>> m_entities;
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_win;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_ren;
    bool m_fullScreen;
    std::string m_title;
    SDL_Surface *m_icon;
};
