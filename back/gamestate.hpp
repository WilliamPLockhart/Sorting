#pragma once
#include "window.hpp"
#include "events.hpp"

class gamestate
{
public:
    gamestate();
    void run();
    void update();
    void generateVect();

private:
    bool m_running;
    std::shared_ptr<std::vector<std::shared_ptr<window::item>>> m_entities;
    std::unique_ptr<window> m_winOBJ;
    std::unique_ptr<events> m_eventOBJ;
};
