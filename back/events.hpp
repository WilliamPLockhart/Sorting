#pragma once
#include "global.h"

class events
{
public:
    enum eventButtonType
    {

        nothing = 0,
        end = 1,
        shuffle = 2,
        bubble = 3,
        merge = 4,
        bogo = 5,
        quick = 6
    };
    events();
    void handleEvents();
    bool getDragging() { return m_dragging; }

    // public vars
    eventButtonType buttonFlag;
    std::vector<clickAble> listEvents;

private:
    std::unique_ptr<SDL_Event> m_event = std::make_unique<SDL_Event>();
    bool m_dragging;
    int m_mouseX, m_mouseY;
    int m_offsetX, m_offsetY;
};