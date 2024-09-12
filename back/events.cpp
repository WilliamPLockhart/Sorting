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
                    else if (i.desc == "bubble")
                    {
                        buttonFlag = bubble;
                    }
                    else if (i.desc == "merge")
                    {
                        buttonFlag = merge;
                    }
                    else if (i.desc == "bogo")
                    {
                        buttonFlag = bogo;
                    }
                    else if (i.desc == "quick")
                    {
                        buttonFlag = quick;
                    }
                    else if (i.desc == "selection")
                    {
                        buttonFlag = selection;
                    }
                    else if (i.desc == "insertion")
                    {
                        buttonFlag = insertion;
                    }
                    else if (i.desc == "radix")
                    {
                        buttonFlag = radix;
                    }
                    else if (i.desc == "bitonic")
                    {
                        buttonFlag = bitonic;
                    }
                }
            }
        }
        }
    }
}