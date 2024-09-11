#include "algo.hpp"
#include <random>

void algo::shuffle(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list, int width, std::function<void()> renderFunc)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, width - 1);
    for (int i = 0; i < width; i++)
    {
        int randomNumber = dis(gen);

        if (randomNumber == i)
        {
            continue;
        }
        auto itOne = list->at(i);
        auto itTwo = list->at(randomNumber);
        itOne->red = true;
        itTwo->red = true;

        //  pause and render here
        if (renderFunc)
        {
            renderFunc();
        }
        SDL_Delay(1);

        // flips list location
        SDL_Rect temp = itOne->rect;
        itOne->rect = itTwo->rect;
        itTwo->rect = temp;

        // flips x cords
        // Set correct x coordinates after swap
        itOne->rect.x = i;
        itTwo->rect.x = randomNumber;
        itOne->red = false;
        itTwo->red = false;
    }
}