#include "gamestate.hpp"

gamestate::gamestate()
    : m_winOBJ(std::make_unique<window>("Hello SDL", 1080, 720, 0)),
      m_eventOBJ(std::make_unique<events>()),
      m_entities(std::make_shared<std::vector<std::shared_ptr<window::item>>>())
{
    generateVect();
    m_winOBJ->setVect(m_entities);
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

void gamestate::generateVect()
{
    int size = m_winOBJ->windowWidth;
    int height = m_winOBJ->windowHeight;
    float perc = 1;
    if (height < size)
    {
        int diff = size - height;
        perc = static_cast<float>(diff) / static_cast<float>(size);
    }
    for (int i = 0; i < size; i++)
    {
        std::shared_ptr<window::item> it = std::make_shared<window::item>();
        int rectHeight = static_cast<int>(static_cast<float>(i) * perc);

        it->rect = {i, height - rectHeight, 2, static_cast<int>(static_cast<float>(i) * perc)};
        it->red = false;
        m_entities->push_back(it);
    }
}
