#pragma once
#include "global.h"
#include <functional>
#include <cmath>
#include <chrono>
#include <thread>
class algo
{
public:
    // sorting
    void shuffle(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list, int width, std::function<void()> renderFunc);

private:
};