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

    // bogo sort
    void bogo(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list, int width, std::function<void()> renderFunc);

    // quick sort
    void quick(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list, int low, int high, std::function<void()> renderFunc);
    int partition(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list, std::function<void()> renderFunc, int low, int high);

    // selection sort
    void selection(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list, int width, std::function<void()> renderFunc);

    // insertion sort
    void insertion(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list, int width, std::function<void()> renderFunc);

    // radix sort
    void radix(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list, int width, std::function<void()> renderFunc);
    int getMax(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list);
    void countSort(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list, int width, int exp, std::function<void()> renderFunc);
    void custom(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list, int start, int n, std::function<void()> renderFunc);
    void customHelper(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list, int start, int n, std::function<void()> renderFunc);

private:
};