#include "back\gamestate.hpp"

static gamestate *game = nullptr;
int main(int argc, char **args)
{
    game = new gamestate;
    delete game;
    return 1;
}