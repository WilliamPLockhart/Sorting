#pragma once
#include "global.h"
#include <functional>
#include <cmath>
#include <chrono>
#include <thread>
class algo
{
public:
    // shuffles the array randomly
    void shuffle(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list, int width, std::function<void()> renderFunc);
    // bubble sort
    void bubbleSort(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list, int width, std::function<void()> renderFunc);

    // merge sort
    void mergeSort(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list, int width, std::function<void()> renderFunc, int left, int right);
    void merge(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list, int width, std::function<void()> renderFunc, int left, int mid, int right);
    void bogo(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list, int width, std::function<void()> renderFunc);

private:
};