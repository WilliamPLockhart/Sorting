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
        }
    }
}