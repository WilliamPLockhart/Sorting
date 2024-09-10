#include "gamestate.hpp"

gamestate::gamestate()
    : m_winOBJ(std::make_unique<window>("Hello SDL", 1920, 1080, 0))
{
    m_running = true;
}