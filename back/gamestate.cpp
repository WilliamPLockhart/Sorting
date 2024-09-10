#include "gamestate.hpp"

gamestate::gamestate()
    : m_winOBJ(std::make_unique<window>("Hello SDL", 1080, 720, 0)),
      m_eventOBJ(std::make_unique<events>()),
      m_entities(std::make_shared<std::vector<std::shared_ptr<window::item>>>())
{
    m_running = true;
}

void gamestate::run()
{
    while (m_running)
    {
        m_eventOBJ->handleEvents();
        update();
        m_winOBJ->render();
    }
}

void gamestate::update()
{
    if (m_eventOBJ->buttonFlag == events::eventButtonType::end)
    {
        m_running = false;
    }
}
