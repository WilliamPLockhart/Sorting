#pragma once
#include "global.h"
#include <SDL2/SDL_ttf.h>
class window
{
public:
    // sdl
    window(const std::string &title, int width, int height, bool fullscreen);
    bool init();
    bool setIcon(const char *fileLocation);
    void render(bool sound = false, bool sorted = false);
    void quit();
    // sdl text
    void addTime(std::string sort, Uint64 finishTime);
    void renderText();
    int findFontSize(std::string &text, SDL_Rect rect);
    //"normal" functions
    void setVect(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list) { m_entities = list; }

    // variables
    int windowHeight;
    int windowWidth;
    int windowY;
    int windowX;
    std::vector<clickAble> listEvents;

private:
    // window stuff
    std::string m_text;
    bool m_running;
    bool m_winScreen = false;
    std::shared_ptr<std::vector<std::shared_ptr<item>>> m_entities;
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_win;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_ren;
    bool m_fullScreen;
    std::string m_title;
    SDL_Surface *m_icon;
    // text stuff
    TTF_Font *m_font;
};
