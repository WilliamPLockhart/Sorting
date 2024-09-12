#include "window.hpp"
#include <fstream>

window::window(const std::string &title, int width, int height, bool fullscreen)
    : m_win(nullptr, SDL_DestroyWindow),
      m_ren(nullptr, SDL_DestroyRenderer),
      m_entities(std::make_shared<std::vector<std::shared_ptr<item>>>())
{
    m_title = title;
    windowWidth = width;
    windowHeight = height;
    m_fullScreen = fullscreen;
    m_icon = nullptr;
    if (init())
    {
        m_running = TTF_Init();
        m_font = TTF_OpenFont("assets/fonts/videoHome.ttf", 24);
        if (!m_font)
        {
            std::cout << "failed font" << std::endl;
        }
    }
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

void window::render(bool sound, bool sorted)
{
    SDL_SetRenderDrawColor(m_ren.get(), 10, 10, 100, 255); // Set background color
    SDL_RenderClear(m_ren.get());

    SDL_SetRenderDrawColor(m_ren.get(), 255, 255, 255, 255); // Set default color to white
    if (sorted)
    {
        // Render each rectangle one by one in green with a delay
        SDL_SetRenderDrawColor(m_ren.get(), 0, 255, 0, 255); // Set color to green

        for (const auto &i : *m_entities)
        {
            SDL_RenderFillRect(m_ren.get(), &i->rect);
            SDL_RenderPresent(m_ren.get());

            // Delay to create the effect of rendering rectangles one by one
            SDL_Delay(.1);
        }
    }
    else
    {
        for (const auto &i : *m_entities)
        {

            if (i->red)
            {
                SDL_SetRenderDrawColor(m_ren.get(), 255, 0, 0, 255); // Set color to red
            }
            else
            {
                SDL_SetRenderDrawColor(m_ren.get(), 255, 255, 255, 255); // Set color to white
            }

            if (sound)
            {
            }
            SDL_RenderFillRect(m_ren.get(), &i->rect);
        }
        for (auto i : listEvents)
        {
            if (i.tex)
            {
                // to do render the texture
            }
            else
            {
                SDL_SetRenderDrawColor(m_ren.get(), 255, 0, 0, 255); // Set color to red
                SDL_RenderFillRect(m_ren.get(), &i.rect);
            }
        }
    }
    renderText();
    SDL_RenderPresent(m_ren.get());
}

void window::quit()
{
    SDL_Quit();
    TTF_Quit();
}

void window::renderText()
{

    // creates and frees textSurface
    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Surface *textSurface = TTF_RenderText_Solid(m_font, "Hello, SDL2_ttf!", textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(m_ren.get(), textSurface);
    SDL_FreeSurface(textSurface);
    // text itself
    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);
    SDL_Rect textRect = {320 - textWidth / 2, 240 - textHeight / 2, textWidth, textHeight};

    // Render the text
    SDL_RenderCopy(m_ren.get(), textTexture, NULL, &textRect);
}

int window::findFontSize(std::string &text, SDL_Rect rect)
{
    int fontSize = 30;
    TTF_CloseFont(m_font);
    while (fontSize > 0)
    {
        m_font = TTF_OpenFont("assets/fonts/videoHome.ttf", fontSize);
        if (!m_font)
        {
            std::cout << "failed to open font!... findFontSize " << TTF_GetError() << std::endl;
            return -1;
        }
        SDL_Color color = {0, 0, 0, 255};
        }
}