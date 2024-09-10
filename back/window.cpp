#include "window.hpp"

window::window(const std::string &title, int width, int height, bool fullscreen)
    : m_win(nullptr, SDL_DestroyWindow),
      m_ren(nullptr, SDL_DestroyRenderer),
      m_title(title),
      windowWidth(width),
      windowHeight(height),
      m_fullScreen(fullscreen),
      m_icon(nullptr)
{
    m_running = init();
}

bool window::init()
{
    // defines window, renderer, audio, and icon
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsytems Initialized!.." << std::endl;

        // defines window
        m_win = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>(SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, m_fullScreen), SDL_DestroyWindow);
        int x, y;
        SDL_GetWindowPosition(m_win.get(), &x, &y);
        windowY = y, windowX = x;
        if (m_win)
        {
            std::cout << "Window Created!..." << std::endl;
        }
        // defines renderer
        m_ren = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>(SDL_CreateRenderer(m_win.get(), -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer);
        if (m_ren)
        {
            std::cout << "Renderer Created!..." << std::endl;
        }
        // returns error if m_ren or m_win did no initialize
        if (!m_ren || !m_win)
        {
            std::cout << "Error!.." << SDL_GetError() << std::endl;
            return false;
        }
    }
    // ensures mixer is working
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == 0)
    {
        std::cout << "Failed to initialize SDL2_mixer: " << Mix_GetError() << std::endl;
        return false;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cout << "Failed to open audio: " << Mix_GetError() << std::endl;
        return false;
    }

    // sets icon
    const char *file = "assets/logo.bmp";
    if (!setIcon(file))
    {
        return false;
    }
    return true;
}

bool window::setIcon(const char *fileLocation)
{
    m_icon = SDL_LoadBMP(fileLocation);
    if (!m_icon)
    {
        std::cout << "icon failed to load!..." << std::endl;
        return false;
    }
    else
    {
        SDL_SetWindowIcon(m_win.get(), m_icon);
        return true;
    }
}