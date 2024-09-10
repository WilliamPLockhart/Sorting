#include "global.h"
#include <functional>

class algo
{
public:
    void shuffle(std::shared_ptr<std::vector<std::shared_ptr<item>>> &list, int width, std::function<void()> renderFunc);

private:
};