#pragma once
#include "window.hpp"
#include "events.hpp"
#include "algo.hpp"

class gamestate
{
public:
    gamestate();
    void run();
    void update();
    void generateVect();

private:
    bool m_running;
    std::unique_ptr<algo> m_algOBJ;
    std::shared_ptr<std::vector<std::shared_ptr<item>>> m_entities;
    std::unique_ptr<window> m_winOBJ;
    std::unique_ptr<events> m_eventOBJ;
};
