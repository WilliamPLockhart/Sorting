#include "events.hpp"

events::events()
    : m_event(std::make_unique<SDL_Event>())
{
    buttonFlag = nothing;
}

void events::handleEvents()
{
    while (SDL_PollEvent(m_event.get()))
    {
        switch (m_event->type)
        {
        case SDL_QUIT:
        {
            buttonFlag = end;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            SDL_GetMouseState(&m_mouseX, &m_mouseY);
            for (auto i : listEvents)
            {
                int RectX = i.rect.x;
                int RectY = i.rect.y;
                if ((m_mouseX >= RectX && m_mouseX <= RectX + i.rect.w) && (m_mouseY >= RectY && m_mouseY <= RectY + i.rect.h))
                {
                    if (i.desc == "shuffle")
                    {
                        buttonFlag = shuffle;
                    }
                }
            }
        }
        }
    }
}