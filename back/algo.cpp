#include "algo.hpp"
#include <random>

// shuffle
void algo::shuffle(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list, int width, std::function<void()> renderFunc)
{
    std::cout << "shuffling!..." << std::endl;
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

// bubble sort
void algo::bubbleSort(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list, int width, std::function<void()> renderFunc)
{
    std::cout << "bubble sort" << std::endl;
    for (int i = 0; i < width - 1; i++)
    {
        for (int j = 0; j < width - i - 1; j++)
        {
            auto itOne = list->at(j);
            auto itTwo = list->at(j + 1);
            itOne->red = true;
            itTwo->red = true;
            if (j % 10 == 0)
            {
                if (renderFunc)
                {
                    renderFunc();
                }
            }

            if (itOne->rect.y < itTwo->rect.y)
            {
                // flips list location
                SDL_Rect temp = itOne->rect;
                itOne->rect = itTwo->rect;
                itTwo->rect = temp;

                // flips x cords
                // Set correct x coordinates after swap
                itOne->rect.x = j + 1;
                itTwo->rect.x = j;
                itOne->red = false;
                itTwo->red = false;
            }
            itOne->red = false;
            itTwo->red = false;
        }
    }
}

// merge sort
void algo::mergeSort(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list, int width, std::function<void()> renderFunc, int left, int right)
{
    std::cout << "merge sort" << std::endl;
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        // Sort the first and second halves
        mergeSort(list, width, renderFunc, left, mid);
        mergeSort(list, width, renderFunc, mid + 1, right);
        // Merge the sorted halves
        merge(list, width, renderFunc, left, mid, right);
        if (renderFunc)
        {
            renderFunc();
        }
    }
}

void algo::merge(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list, int width, std::function<void()> renderFunc, int left, int mid, int right)
{
    // Create temporary vectors for the left and right subarrays
    std::vector<std::shared_ptr<item>> leftArr(list->begin() + left, list->begin() + mid + 1);
    std::vector<std::shared_ptr<item>> rightArr(list->begin() + mid + 1, list->begin() + right + 1);

    // Merge the temporary vectors back into the original list
    int i = 0, j = 0, k = left;
    while (i < leftArr.size() && j < rightArr.size())
    {
        if (leftArr[i]->rect.y >= rightArr[j]->rect.y)
        {
            // Move item from leftArr to list
            list->at(k) = leftArr[i++];
        }
        else
        {
            // Move item from rightArr to list
            list->at(k) = rightArr[j++];
        }
        // Update the SDL_Rect
        list->at(k)->rect.x = k;

        list->at(k)->red = true;
        if (renderFunc)
        {
            renderFunc();
        }
        list->at(k)->red = false;
        ++k;
    }

    // Copy the remaining elements of leftArr, if any
    while (i < leftArr.size())
    {
        list->at(k) = leftArr[i++];
        list->at(k)->rect.x = k;

        list->at(k)->red = true;
        if (renderFunc)
        {
            renderFunc();
        }
        list->at(k)->red = false;
        ++k;
    }

    // Copy the remaining elements of rightArr, if any
    while (j < rightArr.size())
    {
        list->at(k) = rightArr[j++];
        list->at(k)->rect.x = k;

        list->at(k)->red = true;
        if (renderFunc)
        {
            renderFunc();
        }
        list->at(k)->red = false;
        ++k;
    }
}

// bogo sort
void algo::bogo(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list, int width, std::function<void()> renderFunc)
{
    std::cout << "bogo sort" << std::endl;
    bool run = true;
    bool order = true;
    uint64_t startTime = SDL_GetTicks64();

    while (run)
    {
        shuffle(list, width, renderFunc);

        order = true;
        for (int i = 0; i < width - 1; i++)
        {
            list->at(i)->red = true;
            list->at(i + 1)->red = true;
            if (list->at(i)->rect.y > list->at(i + 1)->rect.y)
            {
                list->at(i)->red = false;
                list->at(i + 1)->red = false;
                order = false; // List is not sorted
                break;
            }
            list->at(i)->red = false;
            list->at(i + 1)->red = false;
        }

        if (order)
        {
            run = false; // Exit the while loop if list is sorted
        }

        // Check if 10 seconds have elapsed
        uint64_t currentTime = SDL_GetTicks64();
        if (currentTime - startTime >= 10000)
        {
            run = false; // Exit the while loop
        }
    }
}

// quick sort
void algo::quick(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list, int low, int high, std::function<void()> renderFunc)
{
    std::cout << "quick sort" << std::endl;
    if (low < high)
    {
        int pi = partition(list, renderFunc, low, high); // Partitioning index
        quick(list, low, pi - 1, renderFunc);            // Recursively sort elements before partition
        quick(list, pi + 1, high, renderFunc);           // Recursively sort elements after partition
    }
}

int algo::partition(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list, std::function<void()> renderFunc, int low, int high)
{
    // sets pivot and updates
    int pivot = list->at(high)->rect.y;
    int i = low - 1;

    for (int j = low; j < high; ++j)
    {
        if (list->at(j)->rect.y > pivot)
        {
            ++i;

            // Swapping elements at index i and j
            auto itOne = list->at(i);
            auto itTwo = list->at(j);

            // Swap their SDL_Rect values
            SDL_Rect temp = itOne->rect;
            itOne->rect = itTwo->rect;
            itTwo->rect = temp;

            // Update x coordinates after swap
            itOne->rect.x = i;
            itTwo->rect.x = j;

            itOne->red = true;
            itTwo->red = true;

            if (renderFunc)
            {
                renderFunc();
            }
            itOne->red = false;
            itTwo->red = false;
        }
    }

    // Swap the pivot element with the element at i + 1
    auto itOne = list->at(i + 1);
    auto itTwo = list->at(high);

    // Swap their SDL_Rect values
    SDL_Rect temp = itOne->rect;
    itOne->rect = itTwo->rect;
    itTwo->rect = temp;

    // Update x coordinates after swap
    itOne->rect.x = i + 1;
    itTwo->rect.x = high;

    // Set red flag for the swapped elements
    itOne->red = true;
    itTwo->red = true;

    if (renderFunc)
    {
        renderFunc();
    }
    itOne->red = false;
    itTwo->red = false;

    return i + 1;
}

// selection sort
void algo::selection(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list, int width, std::function<void()> renderFunc)
{
    std::cout << "selection sort" << std::endl;
    for (int i = 0; i < width - 1; ++i)
    {
        // Find the minimum element in unsorted part
        int minIndex = i;
        for (int j = i + 1; j < width; ++j)
        {
            if (list->at(j)->rect.y > list->at(minIndex)->rect.y)
            {
                minIndex = j;
                if (renderFunc)
                {
                    renderFunc();
                }
            }
        }

        // Swap the found minimum element with the first element
        if (minIndex != i)
        {

            list->at(i)->red = true;
            list->at(minIndex)->red = true;

            SDL_Rect rectOne = list->at(i)->rect;
            SDL_Rect rectTwo = list->at(minIndex)->rect;

            // Swap the positions of rects

            rectOne.x = minIndex;
            rectTwo.x = i;
            list->at(i)->rect = rectTwo;
            list->at(minIndex)->rect = rectOne;
            if (renderFunc)
            {
                renderFunc();
            }

            list->at(i)->red = false;
            list->at(minIndex)->red = false;
        }
    }
}

// insertion sort
void algo::insertion(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list, int width, std::function<void()> renderFunc)
{
    std::cout << "insertion sort" << std::endl;
    for (int i = 1; i < width; ++i)
    {
        auto keyItem = list->at(i);
        auto keyRect = keyItem->rect;
        int j = i - 1;

        // Shift elements of list[0..i-1], that are greater than keyRect.h,
        // to one position ahead of their current position
        while (j >= 0 && list->at(j)->rect.h > keyRect.h)
        {
            SDL_Rect rectOne = list->at(j + 1)->rect;
            SDL_Rect rectTwo = list->at(j)->rect;
            list->at(j + 1)->red = true;
            list->at(j)->red = true;
            if (renderFunc)
            {
                renderFunc();
            }
            list->at(j + 1)->red = false;
            list->at(j)->red = false;
            rectOne.x = j;
            rectTwo.x = j + 1;
            list->at(j + 1)->rect = rectTwo;
            list->at(j)->rect = rectOne;
            --j;
        }
        // Place keyRect at the correct position
        list->at(j + 1)->rect.h = keyRect.h;
    }
}
