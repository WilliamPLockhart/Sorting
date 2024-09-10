#include "back\gamestate.hpp"

static gamestate *game = nullptr;
int main(int argc, char **args)
{
    game = new gamestate;
    game->run();
    delete game;
    return 1;
}