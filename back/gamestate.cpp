#include "gamestate.hpp"
#include <unordered_map>
#include <functional>
gamestate::gamestate()
    : m_winOBJ(std::make_shared<window>("Hello SDL", 1080, 720, 0)),
      m_eventOBJ(std::make_unique<events>()),
      m_entities(std::make_shared<std::vector<std::shared_ptr<item>>>()),
      m_algOBJ(std::make_unique<algo>())
{
    setButtons();

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
            break;

        m_winOBJ->render();
    }
}

void gamestate::update()
{
    bool sorted = false;
    if (m_eventOBJ->buttonFlag != events::eventButtonType::end)
    {
        callAlgo(sorted);
    }
    else
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
        std::shared_ptr<item> it = std::make_shared<item>();
        int rectHeight = static_cast<int>(static_cast<float>(i) * perc);

        it->rect = {i, height - rectHeight, 2, static_cast<int>(static_cast<float>(i) * perc)};
        it->red = false;
        m_entities->push_back(it);
    }
}

void gamestate::setButtons()
{
    // adds the shuffle button the clickAble list
    clickAble a;
    a.desc = "shuffle";
    a.rect = {10, 10, 30, 30};
    // sets the vectors with the available sorting functions
    m_listEvents.push_back(a);
    a.desc = "bubble";
    a.rect = {50, 10, 30, 30};
    m_listEvents.push_back(a);

    m_listEvents.push_back(a);
    a.desc = "selection";
    a.rect = {50, 50, 30, 30};
    m_listEvents.push_back(a);

    m_listEvents.push_back(a);
    a.desc = "insertion";
    a.rect = {50, 90, 30, 30};
    m_listEvents.push_back(a);

    a.desc = "merge";
    a.rect = {90, 10, 30, 30};
    m_listEvents.push_back(a);

    a.desc = "quick";
    a.rect = {90, 50, 30, 30};
    m_listEvents.push_back(a);

    a.desc = "bogo";
    a.rect = {130, 10, 30, 30};
    m_listEvents.push_back(a);

    a.desc = "radix";
    a.rect = {130, 50, 30, 30};
    m_listEvents.push_back(a);

    a.desc = "custom";
    a.rect = {200, 50, 30, 30};
    m_listEvents.push_back(a);

    m_winOBJ->listEvents = m_listEvents;
    m_eventOBJ->listEvents = m_listEvents;
}
void gamestate::callAlgo(bool sorted)
{
    if (!m_eventOBJ->buttonFlag)
        return;

    auto handleEventsAndRender = [this]()
    {
        m_eventOBJ->handleEvents();
        if (m_eventOBJ->buttonFlag != events::eventButtonType::end)
        {
            m_winOBJ->render();
        }
    };

    m_winOBJ->addTime("", 0);
    Uint64 startTime = SDL_GetTicks64();
    std::string sortTitle;

    if (m_eventOBJ->buttonFlag == events::eventButtonType::end)
    {
        m_running = false;
        return;
    }

    auto performSorting = [&](events::eventButtonType type)
    {
        switch (type)
        {
        case events::eventButtonType::shuffle:
            sortTitle = "Shuffle";
            m_algOBJ->shuffle(m_entities, m_winOBJ->windowWidth, handleEventsAndRender);
            break;
        case events::eventButtonType::bubble:
            sortTitle = "Bubble";
            m_algOBJ->bubbleSort(m_entities, m_winOBJ->windowWidth, handleEventsAndRender);
            sorted = true;
            break;
        case events::eventButtonType::merge:
            sortTitle = "Merge";
            m_algOBJ->mergeSort(m_entities, m_winOBJ->windowWidth, handleEventsAndRender, 0, m_winOBJ->windowWidth - 1);
            sorted = true;
            break;
        case events::eventButtonType::bogo:
            sortTitle = "Bogo";
            m_algOBJ->bogo(m_entities, m_winOBJ->windowWidth, handleEventsAndRender);
            break;
        case events::eventButtonType::quick:
            sortTitle = "Quick";
            m_algOBJ->quick(m_entities, 0, m_winOBJ->windowWidth - 1, handleEventsAndRender);
            sorted = true;
            break;
        case events::eventButtonType::insertion:
            sortTitle = "Insertion";
            m_algOBJ->insertion(m_entities, m_winOBJ->windowWidth, handleEventsAndRender);
            sorted = true;
            break;
        case events::eventButtonType::selection:
            sortTitle = "Selection";
            m_algOBJ->selection(m_entities, m_winOBJ->windowWidth, handleEventsAndRender);
            sorted = true;
            break;
        case events::eventButtonType::radix:
            sortTitle = "Radix";
            m_algOBJ->radix(m_entities, m_winOBJ->windowWidth, handleEventsAndRender);
            sorted = true;
            break;
        case events::eventButtonType::custom:
            sortTitle = "Quick Merge";
            m_algOBJ->custom(m_entities, 0, m_winOBJ->windowWidth, handleEventsAndRender);
            sorted = true;
            break;
        default:
            std::cout << "m_eventOBJ->buttonFlag value: " << m_eventOBJ->buttonFlag << " not defined" << std::endl;
            break;
        }
    };

    performSorting(m_eventOBJ->buttonFlag);

    if (m_eventOBJ->buttonFlag != events::eventButtonType::end)
    {
        m_eventOBJ->buttonFlag = events::eventButtonType::nothing;
    }

    if (sorted)
    {
        if (!sortTitle.empty())
        {
            sortTitle += " Sort";
        }
        Uint64 endtime = SDL_GetTicks64() - startTime;
        m_winOBJ->addTime(sortTitle, endtime);
        m_winOBJ->render(1, 1);
        SDL_Delay(600);
    }
}
