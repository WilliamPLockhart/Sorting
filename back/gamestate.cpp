#include "gamestate.hpp"

gamestate::gamestate()
    : m_winOBJ(std::make_shared<window>("Hello SDL", 1080, 720, 0)),
      m_eventOBJ(std::make_unique<events>()),
      m_entities(std::make_shared<std::vector<std::shared_ptr<item>>>()),
      m_algOBJ(std::make_unique<algo>())
{
    // adds the shuffle button the clickAble list
    clickAble a;
    a.desc = "shuffle";
    a.rect = {10, 10, 30, 30};
    // sets the vectors
    m_listEvents.push_back(a);
    a.desc = "bubble sort";
    a.rect = {50, 10, 30, 30};
    m_listEvents.push_back(a);
    m_winOBJ->listEvents = m_listEvents;
    m_eventOBJ->listEvents = m_listEvents;

    // creates the list of values in ascending order
    generateVect();

    // gives the window object the list of values and positions
    m_winOBJ->setVect(m_entities);

    m_running = true;
}

void gamestate::run()
{
    while (m_running)
    {
        m_eventOBJ->handleEvents();
        update();
        if (!m_running)
        {
            break;
        }
        m_winOBJ->render();
    }
}

void gamestate::update()
{
    if (m_eventOBJ->buttonFlag)
    {
        // end app
        if (m_eventOBJ->buttonFlag == events::eventButtonType::end)
        {
            m_running = false;
        }
        // shuffle array
        else if (m_eventOBJ->buttonFlag == events::eventButtonType::shuffle)
        {
            m_algOBJ->shuffle(m_entities, m_winOBJ->windowWidth, [this]()
                              {
                                  m_eventOBJ->handleEvents();
                                  if (m_eventOBJ->buttonFlag != events::eventButtonType::end)
                                  {
                                      m_winOBJ->render(); // Call the window's render method
                                  } });
        }
        // if buttonFlag is not blank and the condition is not listed
        else
        {
            std::cout << "m_eventOBJ->buttonFlag value: " << m_eventOBJ->buttonFlag << " not defined" << std::endl;
        }
        if (m_eventOBJ->buttonFlag != events::eventButtonType::end)
        {
            m_eventOBJ->buttonFlag = events::eventButtonType::nothing;
        }
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
        std::shared_ptr<item> it = std::make_shared<item>();
        int rectHeight = static_cast<int>(static_cast<float>(i) * perc);

        it->rect = {i, height - rectHeight, 2, static_cast<int>(static_cast<float>(i) * perc)};
        it->red = false;
        m_entities->push_back(it);
    }
}
