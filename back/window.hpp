#include "global.h"
class window
{
public:
    window(const std::string &title, int width, int height, bool fullscreen);
    bool init();
    bool setIcon(const char *fileLocation);
    int windowHeight;
    int windowWidth;
    int windowY;
    int windowX;

private:
    bool m_running;
    bool m_winScreen = false;
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_win;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_ren;
    bool m_fullScreen;
    std::string m_title;
    SDL_Surface *m_icon;
};
